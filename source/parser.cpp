#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <stdarg.h>
#include <stdio.h>
#include "parser.h"

#include <rose/hash.h>
#include <rose/unused.h>
#include <rose/streambuffer.h>
#include <serializer/serializer.h>
#include <serializer/jsonserializer.h>

#include <windows.h>

#define IMPL_SERIALIZER
#include "parser_serializer.h"

#define ENDL "\n"
#define WHITESPACE " \n\r\t"

bool is_empty(const char * c) { return *c == 0; }

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

std::vector<const char *> input_files;

void error(const char * msg, rose::StreamBuffer & buffer) {
  char tmp[20] = "";
  buffer.sws_read_till(tmp, WHITESPACE);
  fprintf(stderr, "%s: %s(%i) [found '%s']\n", msg, buffer.path, buffer.cursor_line, tmp);
  exit(1);
}

//str -> "str"
void quotify(char * str, size_t len, rose::StreamBuffer & buffer) {
  size_t l = std::strlen(str);
  if (l >= len - 2) error("string to long", buffer);
  str[l + 2] = 0;
  str[l + 1] = '\"';
  for (size_t i = l; i != 0; --i) {
    str[i] = str[i - 1];
  }
  str[0] = '\"';
}

template<size_t N>
void quotify(char(&str)[N], rose::StreamBuffer & buffer) {
  quotify(str, N, buffer);
}

int read_in_namespaces(char * buffer, int N, const std::vector<namespace_path> & namespaces, rose::StreamBuffer & sb) {
  char * p = buffer;
  int size = N;
  int len = 0;
  for (auto & ns : namespaces) {
    int s = std::snprintf(p, size, "%s::", ns.path);
    size -= s;
    len += s;
    if (size < 0) error("out of space.", sb);
    p += s;
  }
  return len;
}

template<size_t N>
int read_in_namespaces(char (&buffer)[N], const std::vector<namespace_path> & namespaces, rose::StreamBuffer & sb) {
  return read_in_namespaces(buffer, N, namespaces, sb);
}

void parse(ParseContext & ctx, rose::StreamBuffer & buffer) {
  char tmp[64] = "";
  global_annotations_t global_annotation = global_annotations_t::NONE;
  bool is_in_imposter_comment = false;
  std::vector<namespace_path> namespaces;
  while (!buffer.eof) {
    ////////////////////////////////////////////////////////
    // COMMENTS                                           //
    ////////////////////////////////////////////////////////
    while (buffer.skip_comment()) {
      // TODO: we need a more flexible way to check for comments
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
        is_in_imposter_comment = true;
      }
    }

    if (is_in_imposter_comment) {
      if (buffer.test_and_skip("*/")) {
        global_annotation = global_annotations_t::NONE;
        is_in_imposter_comment = false;
        continue;
      }
    }

    ////////////////////////////////////////////////////////
    // MACROS                                             //
    ////////////////////////////////////////////////////////
    if (buffer.test_and_skip("#")) {
      //Macro
      buffer.read_till(tmp, WHITESPACE);
      switch (rose::hash(tmp)) { 
      case rose::hash("include"):
      case rose::hash("pragma"):
      case rose::hash("define"):
        buffer.skip_line();
        break;
      case rose::hash("ifdef"):
      case rose::hash("ifndef"):
      case rose::hash("if"):
        //skip all ifXXX macros.
        buffer.skip_line();
        for (;;) {
          if (buffer.sws_peek() == '#') {
            if (buffer.test("#endif")) {
              buffer.skip_line();
              break;
            }
          }
          buffer.skip_line();
        }

        break;
      default:
        error("unknown PP macro.", buffer);
        break;
      }
      continue;
    }

    ////////////////////////////////////////////////////////
    // NAMESPACE                                          //
    ////////////////////////////////////////////////////////
    if (buffer.test_and_skip("namespace ")) {
      namespace_path path;
      buffer.sws_read_till(path.path, "{" WHITESPACE);
      namespaces.push_back(path);
      buffer.test_and_skip("{");
      continue;
    }

    if (buffer.test_and_skip("}")) {
      if (namespaces.size() == 0)
        error("unexpected '}'", buffer);

      namespaces.pop_back();
      continue;
    }

    ////////////////////////////////////////////////////////
    // ENUMS                                              //
    ////////////////////////////////////////////////////////
    if (buffer.test_and_skip("enum ")) {
      if (buffer.test_and_skip("class ") || buffer.test_and_skip("struct ")) {
        if (global_annotation != global_annotations_t::NONE && global_annotation != global_annotations_t::Flag) {
          error("enum class annotation can't be anything other than 'Flag'", buffer);
        }
        enum_class_info & enumci = ctx.enum_classes.emplace_back();
        enumci.enum_annotations = global_annotation;
        global_annotation = global_annotations_t::NONE;

        enumci.namespaces = namespaces;
        int s = read_in_namespaces(enumci.name_withns, namespaces, buffer);
        buffer.sws_read_till(enumci.name_withoutns, "{:" WHITESPACE);
        std::strcpy(enumci.name_withns + s, enumci.name_withoutns); //append name to namespaces part
        char c = buffer.sws_get();

        if (c == ':') {
          enumci.custom_type = true;
          buffer.sws_read_till(enumci.type, "{");
          c = buffer.sws_get();
        }

        if (c != '{') error("Expected '{'", buffer);

        for (;;) {
          while (buffer.skip_comment())
          {
            //Skip the comments
          }

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

      structi.global_annotations = global_annotation;
      global_annotation = global_annotations_t::NONE;

      structi.namespaces = namespaces;
      int s = read_in_namespaces(structi.name_withns, namespaces, buffer);
      buffer.sws_read_till(structi.name_withoutns, ";{" WHITESPACE);
      std::strcpy(structi.name_withns + s, structi.name_withoutns);

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

          memberi.count = 1;
          memberi.kind = Member_info_kind::Field;
          memberi.annotations = annotation;
          copy(memberi.type, type);
          buffer.sws_read_till(memberi.name, "([;," WHITESPACE);
          c = buffer.sws_get();

          if (c == '(') {
            //function
            memberi.kind = Member_info_kind::Function;
            //skip for now. we don't really care.
            buffer.skip_till_any(")");
            buffer.skip(1);
            if (buffer.sws_peek() == '{') {
              error("can't deal with inline functions right now.", buffer);
            }
            c = buffer.sws_get();
          }

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

          if (memberi.kind == Member_info_kind::Function) {
            //get rid of function member because we don't want to deal with it right now.
            structi.members.pop_back();
          }

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
    if (!buffer.eof) {
      buffer.test_and_skip("inline ");

      char type[64];
      buffer.sws_read_c_identifier(type);

      char name[128];
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

            rose::StreamBuffer para_buffer;
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
            buffer.skip_till_any("{}");
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

//printf trim trailing whitespaces
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

void has_compare_ops(bool & has_eqop, bool & has_neqop, bool & has_serialize, bool & has_deserialize, ParseContext & c, const char * sname) {
  rose::hash_value shash = rose::hash(sname);
  has_eqop = false;
  has_neqop = false;
  has_serialize = false;
  has_deserialize = false;

  for (auto & inf : c.functions) {
    if (inf.parameters.size() == 2 &&
      rose::hash(inf.name) == rose::hash("operator==") &&
      rose::hash(inf.parameters[0].type) == shash &&
      rose::hash(inf.parameters[1].type) == shash)
      has_eqop = true;

    if (inf.parameters.size() == 2 &&
      rose::hash(inf.name) == rose::hash("operator!=") &&
      rose::hash(inf.parameters[0].type) == shash &&
      rose::hash(inf.parameters[1].type) == shash)
      has_neqop = true;

    if (inf.parameters.size() == 2 &&
      rose::hash(inf.name) == rose::hash("serialize") &&
      rose::hash(inf.parameters[0].type) == shash)
      has_serialize = true;

    if (inf.parameters.size() == 2 &&
      rose::hash(inf.name) == rose::hash("deserialize") &&
      rose::hash(inf.parameters[0].type) == shash)
      has_deserialize = true;
  }
}

void dump_cpp(ParseContext & c, int argc = 0, char ** argv = nullptr) {
  printf_ttws("#pragma once\n");
  printf_ttws("\n");
  printf_ttws("#include <rose/hash.h>\n");
  printf_ttws("#include <rose/typetraits.h>\n");
  printf_ttws("#include <rose/serializer.h>\n");
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
    const char * name = enumci.name_withns;
    const char * type = enumci.type;

    puts("");
    for (auto & ns : enumci.namespaces) {
        printf_ttws("namespace %s {\n", ns.path);
    }
    if (enumci.custom_type) {
        printf_ttws("enum class                   %s : %s;\n", enumci.name_withoutns, type);
    } else {
        printf_ttws("enum class                   %s;\n", enumci.name_withns);
    }
    for (auto & ns : enumci.namespaces) {
        (void)ns;
        printf_ttws("}\n");
    }
    printf_ttws("const char * to_string(const %s &);\n", name);

    printf_ttws("namespace rose {\n");
    printf_ttws("  namespace ecs {\n");
    printf_ttws("    void      deserialize(%s &o, IDeserializer &s);\n", name);
    printf_ttws("    void        serialize(%s &o, ISerializer &s);\n", name);
    printf_ttws("  }\n");

    printf_ttws("  template<>                       " ENDL);
    printf_ttws("  struct type_id<%s> {             " ENDL, name);
    printf_ttws("    inline static hash_value VALUE = %lluULL;    " ENDL, (unsigned long long)rose::hash(enumci));
    printf_ttws("  };                               " ENDL);

    printf_ttws("  hash_value         hash(const %s &o);\n", name);
    printf_ttws("  void construct_defaults(      %s &o); //implement me\n", name);

    printf_ttws("}\n");

    if (enumci.enum_annotations == global_annotations_t::Flag) {
        puts("");
        printf_ttws("inline BoolConvertible<%s, %s> operator|(const %s &a, const %s &b) { return { static_cast<%s>(static_cast<%s>(a) | static_cast<%s>(b)) }; }" ENDL, name, type, name, name, name, type, type);
        printf_ttws("inline BoolConvertible<%s, %s> operator&(const %s &a, const %s &b) { return { static_cast<%s>(static_cast<%s>(a) & static_cast<%s>(b)) }; }" ENDL, name, type, name, name, name, type, type);
        printf_ttws("inline BoolConvertible<%s, %s> operator^(const %s &a, const %s &b) { return { static_cast<%s>(static_cast<%s>(a) ^ static_cast<%s>(b)) }; }" ENDL, name, type, name, name, name, type, type);
        printf_ttws("inline %s operator|=(%s &a, %s b) { return a = a | b; }                                                    " ENDL, name, name, name);
        printf_ttws("inline %s operator&=(%s &a, %s b) { return a = a & b; }                                                    " ENDL, name, name, name);
        printf_ttws("inline %s operator^=(%s &a, %s b) { return a = a ^ b; }                                                    " ENDL, name, name, name);
    }

    puts("");
  }

  for (auto & structi : c.structs) {
    const char * sname = structi.name_withns;

    bool has_eqop = false;
    bool has_neqop = false;
    bool has_serialize = false;
    bool has_deserialize = false;
    has_compare_ops(has_eqop, has_neqop, has_serialize, has_deserialize, c, sname);

    puts("");
    for (auto & ns : structi.namespaces) {
        printf_ttws("namespace %s {\n", ns.path);
    }
    if (structi.global_annotations != global_annotations_t::Imposter) {
      printf_ttws("struct                %s;\n", structi.name_withoutns);
    }
    for (auto & ns : structi.namespaces) {
        (void)ns;
        printf_ttws("}\n");
    }

    printf_ttws("namespace rose {\n");
    printf_ttws("  namespace ecs {\n");
    if (!has_serialize)   printf_ttws("    void        serialize(%s &o, ISerializer &s);\n", sname);
    if (!has_deserialize) printf_ttws("    void      deserialize(%s &o, IDeserializer &s);\n", sname);
    printf_ttws("  }\n");
    printf_ttws("  hash_value         hash(const %s &o);\n", sname);

    printf_ttws("  template<>                       " ENDL);
    printf_ttws("  struct type_id<%s> {             " ENDL, sname);
    printf_ttws("    inline static hash_value VALUE = %lluULL;    " ENDL, (unsigned long long)rose::hash(structi));
    printf_ttws("  };                               " ENDL);

    printf_ttws("  void construct_defaults(      %s &o); // implement me\n", sname);
    printf_ttws("}\n");
    if (!has_eqop) printf_ttws("bool operator==(const %s &lhs, const %s &rhs);\n", structi.name_withns, structi.name_withns);
    if (!has_neqop) printf_ttws("bool operator!=(const %s &lhs, const %s &rhs);\n", structi.name_withns, structi.name_withns);
    puts("");
  }

  printf_ttws("\n#ifdef IMPL_SERIALIZER\n");

  puts(R"MLS(
    #ifndef IMPL_SERIALIZER_UTIL
    #define IMPL_SERIALIZER_UTIL
    #include <cstring>

    namespace {
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
    }
    #endif
  )MLS");


  //dump implementation
  for (auto & enumci : c.enum_classes) {
    const char * ename = enumci.name_withns;
    printf_ttws("const char * to_string(const %s & e) {\n", ename);
    printf_ttws("    switch(e) {\n");
    for (auto & enumi : enumci.enums) {
      const char * eval = enumi.name;
      printf_ttws("        case %s::%s: return \"%s\";\n", ename, eval, eval);
    }
    printf_ttws("        default: return \"<UNKNOWN>\";\n");
    printf_ttws("    }\n");
    printf_ttws("}\n");


    printf_ttws("void rose::ecs::serialize(%s& o, ISerializer& s) {                  " ENDL, ename);
    printf_ttws("  switch (o) {                                                      " ENDL);

    for (auto & enumi : enumci.enums) {
      const char * eval = enumi.name;
      printf_ttws("    case %s::%s: {                                                " ENDL, ename, eval);
      printf_ttws("      char str[] = \"%s\";                                        " ENDL, eval);
      printf_ttws("      serialize(str, s);                                          " ENDL);
      printf_ttws("      break;                                                      " ENDL);
      printf_ttws("    }                                                             " ENDL);
    }

    printf_ttws("    default: /* unknown */ break;                                   " ENDL);
    printf_ttws("  }                                                                 " ENDL);
    printf_ttws("}                                                                   " ENDL);

    printf_ttws("void rose::ecs::deserialize(%s& o, IDeserializer& s) {              " ENDL, ename);
    printf_ttws("  char str[64];                                                     " ENDL);
    printf_ttws("  deserialize(str, s);                                              " ENDL);
    printf_ttws("  rose::hash_value h = rose::hash(str);                             " ENDL);
    printf_ttws("  switch (h) {                                                      " ENDL);
    for (auto & enumi : enumci.enums) {
      const char * eval = enumi.name;
      printf_ttws("  case rose::hash(\"%s\"): o = %s::%s; break;                     " ENDL, eval, ename, eval);
    }
    printf_ttws("  default: /*unknown value*/ break;                                 " ENDL);
    printf_ttws("  }                                                                 " ENDL);
    printf_ttws("}                                                                   " ENDL);

    printf_ttws("rose::hash_value       rose::hash(const %s& o) {           " ENDL, ename);
    printf_ttws("  return static_cast<rose::hash_value>(o);                 " ENDL);
    printf_ttws("}                                                           \n\n");

  }

  for (auto & structi : c.structs) {
    const char * sname = structi.name_withns;

    printf_ttws("///////////////////////////////////////////////////////////////////\n");
    printf_ttws("//  struct %s\n", sname);
    printf_ttws("///////////////////////////////////////////////////////////////////\n");

    ///////////////////////////////////////////////////////////////////
    // == and != operator                                            //
    ///////////////////////////////////////////////////////////////////

    bool has_eqop = false;
    bool has_neqop = false;
    bool has_serialize = false;
    bool has_deserialize = false;
    has_compare_ops(has_eqop, has_neqop, has_serialize, has_deserialize, c, sname);

    if (!has_eqop) {
      printf_ttws("bool operator==(const %s &lhs, const %s &rhs) {" ENDL, sname, sname);
      printf_ttws("  return" ENDL);
      int left = structi.members.size() - 1;
      for (auto & member : structi.members) {
        printf_ttws("    rose_parser_equals(lhs.%s, rhs.%s) %s\n", member.name, member.name, left ? "&&" : ";");
        --left;
      }
      printf_ttws("} \n\n");
    }

    if (!has_neqop) {
      printf_ttws("bool operator!=(const %s &lhs, const %s &rhs) {" ENDL, sname, sname);
      printf_ttws("  return" ENDL);
      int left = structi.members.size() - 1;
      for (auto & member : structi.members) {
        printf_ttws("    !rose_parser_equals(lhs.%s, rhs.%s) %s\n", member.name, member.name, left ? "||" : ";");
        --left;
      }
      printf_ttws("} \n\n");
    }

    if (!has_serialize) {
      ///////////////////////////////////////////////////////////////////
      // serializer                                                    //
      // TODO: skip functions that are already declared
      ///////////////////////////////////////////////////////////////////
      printf_ttws("void rose::ecs::serialize(%s &o, ISerializer &s) {                     " ENDL, sname);
      printf_ttws("  if(s.node_begin(\"%s\", rose::hash(\"%s\"), &o)) {               " ENDL, sname, sname);

      for (auto & member : structi.members) {
        const char * mname = member.name;
        printf_ttws("    s.key(\"%s\");                                               " ENDL, mname);
        if (member.count > 1 && rose::hash(member.type) == rose::hash("char")) {
          //when type is char[n] then treat is as a string.
          int bit = 0;
          bit |= member.annotations == member_annotations_t::Data ? 1 << 0 : 0;
          bit |= member.annotations == member_annotations_t::String ? 1 << 1 : 0;
          switch (bit)
          {
          case 1 << 0: //DATA
            printf_ttws("    serialize(o.%s, s);                                        " ENDL, mname);
            break;
          case 1 << 1: //STRING
            printf_ttws("    serialize(o.%s, s, std::strlen(o.%s));                     " ENDL, mname, mname);
            break;
          case 0: //NONE
            fprintf(stderr, "Member '%s::%s' must have either annotations @String or @Data.", sname, member.name);
            exit(1);
            break;
          case 1 << 0 | 1 << 1: //BOTH
            fprintf(stderr, "Member '%s::%s' can't have both annotations @String and @Data.", sname, member.name);
            exit(1);
            break;
          default:
            //Shoyuld be unreachable
            assert(false);
            break;
          }
        }
        else {
          printf_ttws("    serialize(o.%s, s);                                        " ENDL, mname);
        }
      }
      printf_ttws("    s.node_end();                                                  " ENDL);
      printf_ttws("  }                                                                " ENDL);
      printf_ttws("  s.end();                                                         " ENDL);
      printf_ttws("}                                                                   \n\n");
    }

    if (!has_deserialize) {
      ///////////////////////////////////////////////////////////////////
      // deserializer                                                  //
      ///////////////////////////////////////////////////////////////////
      printf_ttws("void rose::ecs::deserialize(%s &o, IDeserializer &s) {  " ENDL, sname);
      printf_ttws("  //implement me                                        " ENDL);
      printf_ttws("  //construct_defaults(o);                              " ENDL);
      printf_ttws("                                                        " ENDL);
      printf_ttws("  while (s.next_key()) {                                " ENDL);
      printf_ttws("    switch (s.hash_key()) {                             " ENDL);

      for (auto & member : structi.members) {
        const char * mname = member.name;
        printf_ttws("      case rose::hash(\"%s\"):                        " ENDL, mname);
        printf_ttws("        deserialize(o.%s, s);                         " ENDL, mname);
        printf_ttws("        break;                                        " ENDL);
      }
      printf_ttws("      default: s.skip_key(); break;                     " ENDL);
      printf_ttws("    }                                                   " ENDL);
      printf_ttws("  }                                                     " ENDL);
      printf_ttws("}                                                        \n\n");
    }

    ///////////////////////////////////////////////////////////////////
    // hashing                                                       //
    ///////////////////////////////////////////////////////////////////
    printf_ttws("rose::hash_value rose::hash(const %s &o) {             " ENDL, sname);
    //TODO: compatify, remove von xor64
    //for (auto & member : structi.members) {
    for (size_t i = 0; i != structi.members.size(); ++i) {
      auto & member = structi.members[i];
      if (i == 0) {
        printf_ttws("  rose::hash_value h = rose::hash(o.%s); " ENDL, member.name);
      }
      else {
        printf_ttws("  h = rose::xor64(h);                    " ENDL);
        printf_ttws("  h ^= rose::hash(o.%s);                 " ENDL, member.name);
      }
    }
    printf_ttws("  return h;                          " ENDL);
    printf_ttws("}                                    " ENDL);

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
    "NAME" ENDL
    "       rose.parser - generate serialization code for simple c headers." ENDL
    ENDL
    "SYNOPSIS" ENDL
    "       rose.parser [OPTION]" ENDL
    ENDL
    "BUILDDATE" ENDL
    "       " __DATE__ ", " __TIME__ ENDL
    ENDL

    "DESCRIPTION" ENDL
    "       -H, --help" ENDL
    "              show this help." ENDL
    ENDL
    "       -I, --includes" ENDL
    "              followed by a list of headers files, that should be parsed." ENDL
    ENDL
    "       -O, --output" ENDL
    "              The output file. [default: stdout]" ENDL
    ENDL
    "       -J, --json" ENDL
    "              A optional JSON file containing meta info of the header files." ENDL
    ENDL
    "       -V, --verbose" ENDL
    "              Verbose output.\n"
    ENDL
    "       -E, --error" ENDL
    "              Force Error.\n"
    ENDL
    "AUTHOR" ENDL
    "       Written by Rico Possienka." ENDL
  );
}

int main(int argc, char ** argv) {
  if (argc < 2) {
    printhelp();
    exit(1);
  }

  rose::hash_value state = rose::hash("NONE");

  char tmp_path[260];
  char dst_path[260];

  bool write_to_file = false; //in case we redirect stdout to something else
  bool verbose = false;

  const char * json_path = nullptr;

  for (int i = 1; i < argc; ++i) {
    const char * arg = argv[i];
    rose::hash_value h = rose::hash(arg);
    if (h == rose::hash("--datetime")) {
      fprintf(stderr, "Build Time: %s" ENDL, __DATE__ " " __TIME__);
      continue;
    }
    if (h == rose::hash("--help") || h == rose::hash("-H")) {
      state = rose::hash("NONE");
      printhelp();
      continue;
    }
    if (h == rose::hash("--error") || h == rose::hash("-E")) {
      exit(1);
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
      sprintf(dst_path, "%s", argv[i]);
      sprintf(tmp_path, "%s.bak", argv[i]);
      (void)freopen(tmp_path, "wb", stdout);
      write_to_file = true;
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
    if (h == rose::hash("--watch") || h == rose::hash("-W")) {
      //TODO: use filewatch option https://github.com/ThomasMonkman/filewatch
      continue;
    }

    switch (state) {
    case rose::hash("INCLUDE"): input_files.push_back(arg); break;
    default: printf("Unknown argument %s." ENDL, arg); exit(1); break;
    }
  }

  ParseContext c;

  for (auto path : input_files) {
    rose::StreamBuffer buffer;
    if (verbose) fprintf(stderr, "Parsing File %s\n", path);
    buffer.load(path);
    parse(c, buffer);
    buffer.unload();
  }

  dump_cpp(c, argc, argv);

  if (write_to_file) {
    fclose(stdout);
    auto ok = MoveFileExA(tmp_path, dst_path, MOVEFILE_REPLACE_EXISTING);
    rose::unused(ok);
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
