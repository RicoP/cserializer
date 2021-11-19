#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <stdarg.h>
#include <stdio.h>
#include "parser.h"

#include <rose/hash.h>
#include <serializer/serializer.h>
#include <serializer/jsonserializer.h>

#define IMPL_SERIALIZER
#include "parser_serializer.h"

#define WHITESPACE " \n\r\t"

bool is_empty(const char * c) {
  return *c == 0;
}

bool is_whitespace(char c) {
  return c == ' ' || c == '\t' || c == '\n' || c == '\r';
}

bool contains(char c, const char * characters) {
  if (c == 0) return true;
  for (;;) {
    if (*characters == 0) return false;
    if (*characters == c) return true;
    ++characters;
  }
}

bool is_c_identifier(char c) {
  if (c >= '0' && c <= '9') return true;
  if (c >= 'A' && c <= 'A') return true;
  if (c >= 'a' && c <= 'z') return true;
  if (c == '_') return true;
  if (c == '$') return true;
  return false;
}

bool is_valid_operator(const char * op) {
  //https://www.ibm.com/docs/en/zos/2.1.0?topic=only-overloading-operators
  switch (rose::hash(op)) {
  case rose::hash("operator!"):
  case rose::hash("operator!="):
  case rose::hash("operator%"):
  case rose::hash("operator%="):
  case rose::hash("operator&"):
  case rose::hash("operator&&"):
  case rose::hash("operator&="):
  case rose::hash("operator*"):
  case rose::hash("operator*="):
  case rose::hash("operator+"):
  case rose::hash("operator++"):
  case rose::hash("operator+="):
  case rose::hash("operator,"):
  case rose::hash("operator-"):
  case rose::hash("operator--"):
  case rose::hash("operator-="):
  case rose::hash("operator->"):
  case rose::hash("operator->*"):
  case rose::hash("operator<"):
  case rose::hash("operator<<"):
  case rose::hash("operator<<="):
  case rose::hash("operator<="):
  case rose::hash("operator="):
  case rose::hash("operator=="):
  case rose::hash("operator>"):
  case rose::hash("operator>="):
  case rose::hash("operator>>"):
  case rose::hash("operator>>="):
  case rose::hash("operator|"):
  case rose::hash("operator|="):
  case rose::hash("operator||"):
  case rose::hash("operator~"):
  case rose::hash("operator/"):
  case rose::hash("operator/="):
    return true;
  default: 
    return false;
  }
}

template<size_t N>
void copy(char(&dst)[N], const char * src) {
  for (size_t i = 0; i != N; ++i) {
    dst[i] = src[i];
    if (dst[i] == 0) break;
  }
}

struct StreamBuffer {
  static constexpr size_t buffer_size_max_default = 1024;
  size_t buffer_size_max = buffer_size_max_default;

  int cursor_line = 1;
  size_t buffer_head = 0;
  size_t buffer_size = 0;

  char buffer_internal[2 * buffer_size_max_default] = "";
  char * buffer = buffer_internal;

  const char * path = nullptr;
  FILE * file = nullptr;

  bool eof = false;

  ~StreamBuffer() {
    assert(file == nullptr);
  }

  void load(const char * path_) {
    file = fopen(path_, "rb");
    path = path_;
    assert(file);
  }

  void load_mem(char * buf, size_t len) {
    assert(file == nullptr);
    buffer_size_max = len;
    buffer_size = len;
    buffer = buf;
    path = "<MEMORY>";
  }

  template<size_t N>
  void load_mem(char(&str)[N]) {
    load_mem(str, N);
  }

  void unload() {
    assert(file);
    fclose(file);
    file = nullptr;
  }

  char * begin() {
    return buffer + buffer_head;
  }
  char * end() {
    return buffer + buffer_head + buffer_size;
  }

  void shift_buffer() {
    if (buffer_head == 0) return;
    for (size_t i = 0; i != buffer_size; ++i) {
      buffer[i] = buffer[buffer_head + i];
    }
    buffer_head = 0;
  }

  void fetch() {
    if (buffer_head >= buffer_size_max) {
      shift_buffer();
    }
    char * current = end();
    assert(current < buffer + buffer_size_max);
    size_t count = fread(current, 1, buffer_size_max, file);
    assert(count <= buffer_size_max);
    buffer_size += count;
    eof = count == 0;
    //replace tabs with spaces
    for (char * p = current; p != current + count; ++p)
      if (*p == '\t') *p = ' ';
  }

  char peek() {
    if (buffer_size == 0) {
      fetch();
    }
    if (eof) return 0;
    return buffer[buffer_head];
  }

  char get() {
    char c = peek();
    if (c == 0) return 0;
    if (c == '\n') {
      cursor_line++;
    }
    ++buffer_head;
    --buffer_size;

    return c;
  }

  void skip(size_t num) {
    if (buffer_size < num) {
      fetch();
    }
    assert(buffer_size >= num);
    for (size_t i = 0; i != num; ++i) {
      if (buffer[buffer_head] == '\n') cursor_line++;
      ++buffer_head;
    }
    buffer_size -= num;
  }

  void skip_ws() {
    while (is_whitespace(peek()))
      skip(1);
  }

  char sws_get() {
    skip_ws();
    return get();
  }

  char sws_peek() {
    skip_ws();
    return peek();
  }

  void skip_line() {
    for (;;) {
      char c = get();
      if (c == '\n' || eof) return;
    }
  }

  bool test(const char * str, size_t len) {
    skip_ws();
    assert(len < buffer_size_max);

    if (buffer_size < len) fetch();
    if (buffer_size < len) return false;

    const char * buf = begin();
    for (size_t i = 0; i != len; ++i) {
      if (buf[i] != str[i]) return false;
    }
    return true;
  }

  template<size_t N>
  bool test(const char(&str)[N]) {
    return test(str, N - 1);
  }

  bool test_and_skip(const char * str, size_t len) {
    if (test(str, len)) {
      assert(buffer_size >= len);
      buffer_head += len;
      buffer_size -= len;
      return true;
    }
    return false;
  }

  template<size_t N>
  bool test_and_skip(const char(&str)[N]) {
    return test_and_skip(str, N - 1);
  }

  void read_till(char * dst, size_t len, const char * terminator) {
    char * p = dst;
    for (;;) {
      char c = peek();
      if (contains(c, terminator)) {
        *p = 0;
        break;
      }
      skip(1);
      if (p != dst + len - 1)
        *(p++) = c;
    }
  }

  void skip_till(const char * terminator) {
    for (;;) {
      char c = peek();
      if (contains(c, terminator)) {
        break;
      }
      skip(1);
    }
  }

  bool skip_comment() {
    bool has_multi_comment = test_and_skip("/*");
    if (has_multi_comment) {
      skip_till("*/");
      skip(2);
      return true;
    }

    bool has_annotation = test("//@");
    if (has_annotation) return false;

    bool has_single_comment = test_and_skip("//");
    if (has_single_comment) { skip_line(); }
    return has_single_comment;
  }

  bool test_annotation(char * dst, size_t len) {
    if (test_and_skip("//@")) {
      read_till(dst, len, WHITESPACE);
      skip_line();
      return true;
    }
    return false;
  }

  template<size_t N>
  bool test_annotation(char(&dst)[N]) {
    return test_annotation(dst, N);
  }

  void read_c_identifier(char * dst, size_t len) {
    char * p = dst;
    for (;;) {
      char c = peek();
      if (!is_c_identifier(c)) {
        *p = 0;
        break;
      }
      skip(1);
      if (p != dst + len - 1)
        *(p++) = c;
    }
  }

  void sws_read_c_identifier(char * dst, size_t len) {
    skip_ws();
    read_c_identifier(dst, len);
  }

  template<size_t N>
  void read_c_identifier(char(&dst)[N]) {
    read_c_identifier(dst, N);
  }

  template<size_t N>
  void sws_read_c_identifier(char(&dst)[N]) {
    sws_read_c_identifier(dst, N);
  }

  void sws_read_till(char * dst, size_t len, const char * terminator) {
    skip_ws();
    read_till(dst, len, terminator);;
  }

  template<size_t N>
  void read_till(char(&dst)[N], const char * terminator) {
    read_till(dst, N, terminator);
  }

  template<size_t N>
  void sws_read_till(char(&dst)[N], const char * terminator) {
    sws_read_till(dst, N, terminator);
  }
};

std::vector<const char *> input_files;

void error(const char * msg, StreamBuffer & buffer) {
  char tmp[20] = "";
  buffer.sws_read_till(tmp, WHITESPACE);
  fprintf(stderr, "%s: %s(%i) [found '%s']\n", msg, buffer.path, buffer.cursor_line, tmp);
  exit(1);
}

//str -> "str"
void quotify(char * str, size_t len, StreamBuffer & buffer) {
  size_t l = std::strlen(str);
  if (l >= len - 2) error("string to long", buffer);
  str[l+2] = 0;
  str[l+1] = '\"';
  for (size_t i = l; i != 0; --i) {
    str[i] = str[i - 1];
  }
  str[0] = '\"';
}

template<size_t N>
void quotify(char(&str)[N], StreamBuffer & buffer) {
  quotify(str, N, buffer);
}

void parse(ParseContext & ctx, StreamBuffer & buffer) {

  char tmp[64] = "";
  global_annotations_t global_annotation = global_annotations_t::NONE;
  while (!buffer.eof)
  {
    ////////////////////////////////////////////////////////
    // COMMENTS                                           //
    ////////////////////////////////////////////////////////
    while (buffer.skip_comment()) {
      //TODO: we need a more flexible way to check for comments
    }

    ////////////////////////////////////////////////////////
    // GLOBAL ANNOTATION                                  //
    ////////////////////////////////////////////////////////
    char annotation_s[64];
    bool has_annotation = buffer.test_annotation(annotation_s);
    bool has_second_annotation = buffer.test_annotation(annotation_s);

    if (has_second_annotation) error("No support for more than one global annotations yet.", buffer);

    if (has_annotation) {
      quotify(annotation_s, buffer);
      JsonDeserializer jsond(annotation_s);
      rose::ecs::deserialize(global_annotation, jsond);

      if (global_annotation == global_annotations_t::Imposter) {
        bool ok = buffer.test_and_skip("/*");
        if (!ok) error("expects '/*' with Imposter annotation.", buffer);
      }
    }

    if (global_annotation == global_annotations_t::Imposter) {
      if (buffer.test_and_skip("*/")) {
        global_annotation = global_annotations_t::NONE;
      }
    }

    ////////////////////////////////////////////////////////
    // MACROS                                             //
    ////////////////////////////////////////////////////////
    if (buffer.test_and_skip("#")) {
      //Macro
      if (buffer.test_and_skip("include")) {
        buffer.skip_line();
      }
      else if (buffer.test_and_skip("pragma")) {
        buffer.skip_line();
      }
      else {
        error("unknown PP macro.", buffer);
      }
      continue;
    }

    ////////////////////////////////////////////////////////
    // ENUMS                                              //
    ////////////////////////////////////////////////////////
    if (buffer.test_and_skip("enum ")) {
      if (buffer.test_and_skip("class ") || buffer.test_and_skip("struct ")) {
        if (global_annotation != global_annotations_t::NONE && global_annotation != global_annotations_t::Flag) {
          error("enum class annotation cn't be anything other than 'Flag'", buffer);
        }
        enum_class_info & enumci = ctx.enum_classes.emplace_back();
        enumci.enum_annotations = global_annotation;
        global_annotation = global_annotations_t::NONE;

        buffer.sws_read_till(enumci.name, "{:" WHITESPACE);
        char c = buffer.sws_get();

        if (c == ':') {
          enumci.custom_type = true;
          buffer.sws_read_till(enumci.type, "{");
          c = buffer.sws_get();
        }

        if (c != '{') error("Expected '{'", buffer);
        for (;;) {
          c = buffer.sws_peek();
          if (c == '}') {
            buffer.skip(1);
            c = buffer.sws_get();
            if (c != ';') error("expect ';'", buffer);
            break;
          }

          enum_info & enumi = enumci.enums.emplace_back();
          buffer.sws_read_till(enumi.name, ",=}" WHITESPACE);
          c = buffer.sws_peek();
          if (c == '=') {
            buffer.skip(1);
            enumi.value_type = value_type_t::Set;
            buffer.sws_read_till(enumi.value, ",}");
            c = buffer.sws_peek();
          }
          if (c == ',') buffer.skip(1);
        }

        if (enumci.enums.size() > 0) {
          enumci.enums[0].value_type = value_type_t::Set;
        }

        assert(enumci.enums.size() != 0);
        enumci.default_value = enumci.enums[0];
      }
      else {
        error("expected 'class' after 'enum'.", buffer);
      }
      continue;
    }

    ////////////////////////////////////////////////////////
    // STRUCTS                                            //
    ////////////////////////////////////////////////////////
    if (buffer.test_and_skip("struct ")) {
      struct_info & structi = ctx.structs.emplace_back();

      buffer.sws_read_till(structi.name, ";{" WHITESPACE);

      buffer.skip_ws();

      char c = buffer.get();
      if (c == '{') {
        for (;;) {
          member_annotations_t annotation = member_annotations_t::NONE;
          member_info ignored_member; //in case we want to ignore the member
          
          char annotation_s[64];
          if (buffer.test_annotation(annotation_s)) {
            quotify(annotation_s, buffer);
            JsonDeserializer jsond(annotation_s);
            rose::ecs::deserialize(annotation, jsond);
          }

          char type[64];
          buffer.sws_read_till(type, WHITESPACE);

        new_member:
          member_info & memberi = annotation == member_annotations_t::Ignore 
            ? ignored_member //fake member we just write to but immediately discard
            : structi.members.emplace_back(); //otherwise create new member

          memberi.annotations = annotation;
          copy(memberi.type, type);
          buffer.sws_read_till(memberi.name, "[;," WHITESPACE);
          c = buffer.sws_get();

          memberi.count = 1;

          if (c == '[') {
            buffer.sws_read_till(tmp, "]");
            memberi.count = atoi(tmp);
            buffer.skip(1);
            c = buffer.sws_get();
          }

          if (c == ',') goto new_member; //new member, same type and annotation
          if (c == '=') {
            buffer.sws_read_till(memberi.default_value, ";");
            c = buffer.get();
          }

          if (c != ';') error("Expected ';'", buffer);
          if (buffer.sws_peek() == '}') {
            buffer.skip(1);
            if (buffer.sws_get() != ';') error("Expected ';'", buffer);
            break;
          }
        }
      }
      c = buffer.peek();
      if (c == '\r' || c == '\n') buffer.skip_line();
      continue;
    }

    ////////////////////////////////////////////////////////
    // Assume: GLOBAL FUNCTIONS                           //
    ////////////////////////////////////////////////////////
    buffer.skip_ws();
    if (!buffer.eof)
    {
      char type[64];
      buffer.sws_read_c_identifier(type);

      char name[64];
      buffer.sws_read_c_identifier(name);

      if (rose::hash(name) == rose::hash("operator")) {
        size_t len = strlen("operator");
        size_t size = sizeof(name) - len;
        char * p = name + len;

        buffer.read_till(p, size, "(" WHITESPACE);

        if (!is_valid_operator(name)) {
          error("Unknown operator", buffer);
        }
      }

      if (buffer.test_and_skip("(")) {
        function_info & funci = ctx.functions.emplace_back();
        copy(funci.type, type);
        copy(funci.name, name);

        while (buffer.sws_peek() != ')')
        {
          buffer.sws_read_till(tmp, ",)");
          if (!is_empty(tmp)) {
            function_parameter_info & para = funci.parameters.emplace_back();

            StreamBuffer para_buffer;
            para_buffer.load_mem(tmp);

            para.is_const = para_buffer.test_and_skip("const ");

            para_buffer.sws_read_till(para.type, "*&" WHITESPACE);
            char c = para_buffer.sws_peek();
            if (c == '&' || c == '*')
            {
              para.modifier = para_buffer.get();
            }
            para_buffer.sws_read_till(para.name, WHITESPACE);
          }
          buffer.test_and_skip(",");
        }
        assert(buffer.peek() == ')');
        buffer.skip(1);
        if (buffer.test_and_skip(";")) { /* empty function body */ }
        else if (buffer.test_and_skip("{")) {
          //skip body
          int depth = 1;
          while (depth) {
            //TODO: deal with {} in comments
            buffer.skip_till("{}");
            char c = buffer.get();
            depth += c == '{' ? 1 : -1;
            if (c == 0) break;
          }
        }
        else error("expected either ';' or '{'.", buffer);
      }
      else error("Expected '('", buffer);
    }
  }
}

//printf trim trailing hitespaces
template<typename... Args>
void printf_ttws(const char * f, Args... args) {
  char buffer[1024];

  sprintf(buffer, f, args...);

  char * pto = buffer;
  char * pfrom = buffer;

  size_t spaces = 0;

  rose::hash_value state = rose::hash("COPY");

  for (size_t i = 0; i != sizeof(buffer); ++i) {
    char c = *pfrom;
    if (c == 0) {
      *pto = 0;
      break;
    }

    if (c != ' ' && state == rose::hash("COPY")) {
      *pto = *pfrom;
      ++pto;
      ++pfrom;
      continue;
    }
    if (c == ' ' && state == rose::hash("COPY")) {
      spaces = 1;
      ++pfrom;
      state = rose::hash("SPACE");
      continue;
    }
    if (c == '\n' && state == rose::hash("SPACE")) {
      *pto = '\n';
      ++pto;
      ++pfrom;
      state = rose::hash("COPY");
      continue;
    }
    if (c == ' ' && state == rose::hash("SPACE")) {
      ++pfrom;
      ++spaces;
      continue;
    }
    if (state == rose::hash("SPACE")) {
      for (size_t s = 0; s != spaces; ++s) {
        *(pto++) = ' ';
      }
      *(pto++) = c;

      ++pfrom;
      state = rose::hash("COPY");
      continue;
    }
  }
  fputs(buffer, stdout);
}

void dump_cpp(ParseContext & c, int argc = 0, char ** argv = nullptr) {
  printf_ttws("#pragma once\n");
  printf_ttws("\n");
  printf_ttws("#include <rose/hash.h>\n");
  printf_ttws("#include <serializer/serializer.h>\n");
  printf_ttws("\n");
  printf_ttws("///////////////////////////////////////////////////////////////////\n");
  printf_ttws("//  AUTOGEN                                                      //\n");
  if (argc && argv) {
    printf_ttws("//  command:\n");
    printf_ttws("//    rose.parser");
    for (int i = 1; i < argc; ++i) {
      printf_ttws(" %s", argv[i]);
    }
    printf_ttws("\n");
  }
  printf_ttws("///////////////////////////////////////////////////////////////////\n");

  //dump declaration
  for (auto & enumci : c.enum_classes) {
    puts("");
    char type[64] = "";
    if (enumci.custom_type) {
      sprintf(type, " : %s", enumci.type);
    }
    printf_ttws("enum class                   %s%s;\n", enumci.name, type);
    printf_ttws("const char * to_string(const %s &);\n", enumci.name);

    printf_ttws("namespace rose {\n");
    printf_ttws("  namespace ecs {\n");
    printf_ttws("    void      deserialize(%s &o, IDeserializer &s);\n", enumci.name);
    printf_ttws("    void        serialize(%s &o, ISerializer &s);\n", enumci.name);
    printf_ttws("  }\n");
    printf_ttws("  hash_value         hash(const %s &o);\n", enumci.name);
    printf_ttws("  void construct_defaults(      %s &o); //TODO: implement me\n", enumci.name);

    printf_ttws("}\n");
    puts("");
  }

  for (auto & structi : c.structs) {
    const char * sname = structi.name;

    puts("");
    printf_ttws("struct                %s;\n", structi.name);
    printf_ttws("namespace rose {\n");
    printf_ttws("  namespace ecs {\n");
    printf_ttws("    bool operator==(const %s &lhs, const %s &rhs);\n", structi.name, structi.name);
    printf_ttws("    bool operator!=(const %s &lhs, const %s &rhs);\n", structi.name, structi.name);
    printf_ttws("    void      deserialize(%s &o, IDeserializer &s);\n", sname);
    printf_ttws("    void        serialize(%s &o, ISerializer &s);\n", sname);
    printf_ttws("  }\n");
    printf_ttws("  hash_value         hash(const %s &o);\n", sname);
    printf_ttws("  void construct_defaults(      %s &o); //TODO: implement me\n", sname);
    printf_ttws("}\n");
    puts("");
  }

  printf_ttws("\n#ifdef IMPL_SERIALIZER\n");

  puts(R"MLS(
    #include <cstring>

    //internal helper methods
    template<class T>
    bool rose_parser_equals(const T& lhs, const T& rhs) {
      return lhs == rhs;
    }

    template<class T, size_t N>
    bool rose_parser_equals(const T(&lhs)[N], const T(&rhs)[N]) {
      for (size_t i = 0; i != N; ++i) {
        if (lhs[i] != rhs[i]) return false;
      }
      return true;
    }

    template<size_t N>
    bool rose_parser_equals(const char(&lhs)[N], const char(&rhs)[N]) {
      for (size_t i = 0; i != N; ++i) {
        if (lhs[i] != rhs[i]) return false;
        if (lhs[i] == 0) return true;
      }
      return true;
    }

    template<class T>
    bool rose_parser_equals(const std::vector<T> &lhs, const std::vector<T> &rhs) {
      if (lhs.size() != rhs.size()) return false;
      for (size_t i = 0; i != lhs.size(); ++i) {
        if (lhs[i] != rhs[i]) return false;
      }
      return true;
    }

    template<class TL, class TR>
    void assign(TL& lhs, TR&& rhs) {
      lhs = rhs;
    }

    template<class T>
    void construct_default(std::vector<T> & v) {
      c.clear();
    }
  )MLS");


  //dump implementation
  for (auto & enumci : c.enum_classes) {
    const char * ename = enumci.name;
    printf_ttws("const char * to_string(const %s & e) {\n", enumci.name);
    printf_ttws("    switch(e) {\n");
    for (auto & enumi : enumci.enums) {
      const char * eval = enumi.name;
      printf_ttws("        case %s::%s: return \"%s\";\n", enumci.name, eval, eval);
    }
    printf_ttws("        default: return \"<UNKNOWN>\";\n");
    printf_ttws("    }\n");
    printf_ttws("}\n");


    printf_ttws("void rose::ecs::serialize(%s& o, ISerializer& s) {                   \n", ename);
    printf_ttws("  switch (o) {                                                       \n");

    for (auto & enumi : enumci.enums) {
      const char * eval = enumi.name;
      printf_ttws("    case %s::%s: {                                                 \n", ename, eval);
      printf_ttws("      char str[] = \"%s\";                                         \n", eval);
      printf_ttws("      serialize(str, s);                                           \n");
      printf_ttws("      break;                                                       \n");
      printf_ttws("    }                                                              \n");
    }

    printf_ttws("    default: /* unknown */ break;                                    \n");
    printf_ttws("  }                                                                  \n");
    printf_ttws("}                                                                    \n");

    printf_ttws("void rose::ecs::deserialize(%s& o, IDeserializer& s) {               \n", ename);
    printf_ttws("  char str[64];                                                      \n");
    printf_ttws("  deserialize(str, s);                                               \n");
    printf_ttws("  rose::hash_value h = rose::hash(str);                              \n");
    printf_ttws("  switch (h) {                                                       \n");
    for (auto & enumi : enumci.enums) {
      const char * eval = enumi.name;
      printf_ttws("  case rose::hash(\"%s\"): o = %s::%s; break;                      \n", eval, ename, eval);
    }
    printf_ttws("  default: /*unknown value*/ break;                                  \n");
    printf_ttws("  }                                                                  \n");
    printf_ttws("}                                                                    \n");

    printf_ttws("rose::hash_value       rose::hash(const %s& o) {            \n", ename);
    printf_ttws("  return static_cast<rose::hash_value>(o);                  \n");
    printf_ttws("}                                                           \n\n");

  }

  for (auto & structi : c.structs) {
    const char * sname = structi.name;

    printf_ttws("///////////////////////////////////////////////////////////////////\n");
    printf_ttws("//  struct %s\n", sname);
    printf_ttws("///////////////////////////////////////////////////////////////////\n");

    ///////////////////////////////////////////////////////////////////
    // == and != operator                                            //
    ///////////////////////////////////////////////////////////////////
    printf_ttws("bool operator==(const %s &lhs, const %s &rhs) { \n", structi.name, structi.name);
    printf_ttws("  return \n");
    int left = structi.members.size() - 1;
    for (auto & member : structi.members) {
      printf_ttws("    rose_parser_equals(lhs.%s, rhs.%s) %s\n", member.name, member.name, left ? "&&" : ";");
      --left;
    }
    printf_ttws("} \n\n");

    printf_ttws("bool operator!=(const %s &lhs, const %s &rhs) { \n", structi.name, structi.name);
    printf_ttws("  return \n");
    left = structi.members.size() - 1;
    for (auto & member : structi.members) {
      printf_ttws("    !rose_parser_equals(lhs.%s, rhs.%s) %s\n", member.name, member.name, left ? "||" : ";");
      --left;
    }
    printf_ttws("} \n\n");

    ///////////////////////////////////////////////////////////////////
    // serializer                                                    //
    // TODO: skip functions that are already declared
    ///////////////////////////////////////////////////////////////////
    printf_ttws("void rose::ecs::serialize(%s &o, ISerializer &s) {                      \n", sname);
    printf_ttws("  if(s.node_begin(\"%s\", rose::hash(\"%s\"), &o)) {                \n", sname, sname);

    for (auto & member : structi.members) {
      const char * mname = member.name;
      printf_ttws("    s.key(\"%s\");                                                \n", mname);
      if (member.count > 1 && rose::hash(member.type) == rose::hash("char")) {
        //when type is char[n] then treat is as a string.
        int bit = 0;
        bit |= member.annotations == member_annotations_t::Data ? 1 << 0 : 0;
        bit |= member.annotations == member_annotations_t::String ? 1 << 1 : 0;
        switch (bit)
        {
        case 1 << 0: //DATA
          printf_ttws("    serialize(o.%s, s);                                         \n", mname);
          break;
        case 1 << 1: //STRING
          printf_ttws("    serialize(o.%s, s, std::strlen(o.%s));                      \n", mname, mname);
          break;
        case 0: //NONE
          fprintf(stderr, "Member '%s::%s' must have either annotations @String or @Data.", structi.name, member.name);
          exit(1);
          break;
        case 1 << 0 | 1 << 1: //BOTH
          fprintf(stderr, "Member '%s::%s' can't have both annotations @String and @Data.", structi.name, member.name);
          exit(1);
          break;
        default:
          //Shoyuld be unreachable
          assert(false);
          break;
        }
      }
      else {
        printf_ttws("    serialize(o.%s, s);                                         \n", mname);
      }
    }
    printf_ttws("    s.node_end();                                                   \n");
    printf_ttws("  }                                                                 \n");
    printf_ttws("  s.end();                                                          \n");
    printf_ttws("}                                                                   \n\n");

    ///////////////////////////////////////////////////////////////////
    // deserializer                                                  //
    // TODO: skip functions that are already declared
    ///////////////////////////////////////////////////////////////////
    printf_ttws("void rose::ecs::deserialize(%s &o, IDeserializer &s) {              \n", sname);
    printf_ttws("  //TODO: implement me                                   \n");
    printf_ttws("  //construct_defaults(o);                                 \n");
    printf_ttws("                                                         \n");
    printf_ttws("  while (s.next_key()) {                                 \n");
    printf_ttws("    switch (s.hash_key()) {                              \n");

    for (auto & member : structi.members) {
      const char * mname = member.name;
      printf_ttws("      case rose::hash(\"%s\"):                         \n", mname);
      printf_ttws("        deserialize(o.%s, s);                          \n", mname);
      printf_ttws("        break;                                         \n");
    }
    printf_ttws("      default: s.skip_key(); break;                      \n");
    printf_ttws("    }                                                    \n");
    printf_ttws("  }                                                      \n");
    printf_ttws("}                                                        \n\n");

    ///////////////////////////////////////////////////////////////////
    // hashing                                                       //
    ///////////////////////////////////////////////////////////////////
    printf_ttws("rose::hash_value rose::hash(const %s &o) {              \n", sname);
    printf_ttws("  rose::hash_value h = 0;                   \n");

    for (auto & member : structi.members) {
      const char * mname = member.name;
      printf_ttws("  h ^= rose::hash(o.%s);                  \n", mname);
      printf_ttws("  h = rose::xor64(h);                     \n");
    }

    printf_ttws("  return h;                           \n");
    printf_ttws("}                                     \n");

    ///////////////////////////////////////////////////////////////////
    // Construct Defaults                                            //
    ///////////////////////////////////////////////////////////////////
    /*
      TODO:
        void construct_defaults(Camera & o) {
          assign(o.far_plane, 1000);
          assign(o.fov, 70);
          assign(o.lookat, identity4());
          assign(o.near_plane, 0.1f);
          assign(o.projection, identity4());
          //Defaults
          construct_defaults(o.light_list);
        }
    */
  }

  //end
  printf_ttws("\n#endif\n");
}

void printhelp() {
  puts(
    "NAME \n"
    "       rose.parser - generate serialization code for simple c headers. \n"
    " \n"
    "SYNOPSIS \n"
    "       rose.parser [OPTION] \n"
    " \n"
    "DESCRIPTION \n"
    "       -H, --help \n"
    "              show this help. \n"
    " \n"
    "       -I, --includes \n"
    "              followed by a list of headers files, that should be parsed. \n"
    " \n"
    "       -O, --output \n"
    "              The output file. [default: stdout] \n"
    " \n"
    "       -J, --json \n"
    "              A optional JSON file containing meta info of the header files. \n"
    " \n"
    "       -V, --verbose \n"
    "              Verbose output.\n"
    " \n"
    "AUTHOR \n"
    "       Written by Rico Possienka. \n"
  );
}

int main(int argc, char ** argv) {
  if (argc < 2) {
    printhelp();
    exit(1);
  }

  rose::hash_value state = rose::hash("NONE");

  bool close_stdout = false; //in case we redirect stdout to something else
  bool verbose = false;

  const char * json_path = nullptr;

  for (int i = 1; i < argc; ++i) {
    const char * arg = argv[i];
    rose::hash_value h = rose::hash(arg);
    if (h == rose::hash("--help") || h == rose::hash("-H")) {
      state = rose::hash("NONE");
      printhelp();
      continue;
    }
    if (h == rose::hash("--include") || h == rose::hash("-I")) {
      state = rose::hash("INCLUDE");
      continue;
    }
    if (h == rose::hash("--verbose") || h == rose::hash("-V")) {
      verbose = true;
      continue;
    }
    if (h == rose::hash("--output") || h == rose::hash("-O")) {
      state = rose::hash("NONE");
      ++i;
      assert(i != argc);
      const char * path = argv[i];
      (void)freopen(path, "wb", stdout);
      close_stdout = true;
      continue;
    }
    if (h == rose::hash("--json") || h == rose::hash("-J")) {
      state = rose::hash("NONE");
      ++i;
      assert(i != argc);
      const char * path = argv[i];
      json_path = path;
      continue;
    }

    switch (state) {
    case rose::hash("INCLUDE"): input_files.push_back(arg); break;
    default: printf("Unknown argument %s. \n", arg); exit(1); break;
    }
  }

  ParseContext c;

  for (auto path : input_files) {
    StreamBuffer buffer;
    if (verbose) fprintf(stderr, "Parsing File %s\n", path);
    buffer.load(path);
    parse(c, buffer);
    buffer.unload();
  }

  dump_cpp(c, argc, argv);

  if (close_stdout) {
    fclose(stdout);
  }

  if (json_path) {
    FILE * f = fopen(json_path, "w");
    assert(f);
    JsonSerializer jsons(f);
    rose::ecs::serialize(c, jsons);
    fclose(f);
  }

  return 0;
}
