#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cassert>
#include "parser.h"

#define WHITESPACE " \t\n\r"

bool is_empty(const char * c) {
  return *c == 0;
}

bool is_whitespace(char c) {
  return c == ' ' || c == '\t' || c == '\n' || c == '\r';
}

bool contains(char c, const char* characters) {
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

template<size_t N>
void copy(char(&dst)[N], const char* src) {
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

  const char* path = nullptr;
  FILE* file = nullptr;

  bool eof = false;

  ~StreamBuffer() {
    assert(file == nullptr);
  }

  void load(const char* path_) {
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

  char* begin() {
    return buffer + buffer_head;
  }
  char* end() {
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
    char* current = end();
    assert(current < buffer + buffer_size_max);
    size_t count = fread(current, 1, buffer_size_max, file);
    assert(count <= buffer_size_max);
    buffer_size += count;
    eof = count == 0;
    //replace tabs with spaces
    for (char* p = current; p != current + count; ++p)
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

  bool test_and_skip(const char* str, size_t len) {
    skip_ws();
    assert(len < buffer_size_max);

    if (buffer_size < len) fetch();
    if (buffer_size < len) return false;

    const char* buf = begin();
    for (size_t i = 0; i != len; ++i) {
      if (buf[i] != str[i]) return false;
    }
    buffer_head += len;
    buffer_size -= len;
    return true;
  }

  template<size_t N>
  bool test_and_skip(const char(&str)[N]) {
    return test_and_skip(str, N - 1);
  }

  void read_till(char* dst, size_t len, const char* terminator) {
    char* p = dst;
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

  void skip_till(const char* terminator) {
    for (;;) {
      char c = peek();
      if (contains(c, terminator)) {
        break;
      }
      skip(1);
    }
  }

  void read_c_identifier(char* dst, size_t len) {
    char* p = dst;
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

  void sws_read_c_identifier(char* dst, size_t len) {
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

  void sws_read_till(char* dst, size_t len, const char* terminator) {
    skip_ws();
    read_till(dst, len, terminator);;
  }

  template<size_t N>
  void read_till(char(&dst)[N], const char* terminator) {
    read_till(dst, N, terminator);
  }

  template<size_t N>
  void sws_read_till(char(&dst)[N], const char* terminator) {
    sws_read_till(dst, N, terminator);
  }
};

std::vector<const char*> input_files;

//TODO: use roselib
typedef unsigned long long hash_value;

constexpr hash_value xor64(hash_value h) {
  h ^= 88172645463325252ULL;  // xor with a constant so a seed of 0 will not result in a infinite loop
  h ^= h >> 12;
  h ^= h << 25;
  h ^= h >> 27;
  return h * 0x2545F4914F6CDD1DULL;
}

// https://de.wikipedia.org/wiki/FNV_(Informatik)
constexpr hash_value hash_fnv(const char* string) {
  hash_value MagicPrime = 0x00000100000001b3ULL;
  hash_value Hash = 0xcbf29ce484222325ULL;

  for (; *string; string++) Hash = (Hash ^ *string) * MagicPrime;

  return Hash;
}

constexpr hash_value hash(char const* input) { return hash_fnv(input); }

void printhelp() {
  puts("TODO: Implement help");
}

void error(const char* msg, StreamBuffer& buffer) {
  char tmp[20] = "";
  buffer.sws_read_till(tmp, WHITESPACE);
  fprintf(stderr, "%s: %s(%i) [found '%s']\n", msg, buffer.path, buffer.cursor_line, tmp);
  exit(1);
}

void parse(ParseContext& ctx, StreamBuffer& buffer) {
  char tmp[64] = "";
  while (!buffer.eof)
  {
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
    }
    if (buffer.test_and_skip("enum ")) {
      if (buffer.test_and_skip("class ") || buffer.test_and_skip("struct ")) {
        enum_class_info& enumci = ctx.enum_classes.emplace_back();
        buffer.sws_read_till(enumci.name, "{:" WHITESPACE);
        char c = buffer.sws_get();

        if (c == ':') {
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
      }
      else {
        error("expected 'class' after 'enum'.", buffer);
      }
    }

    if (buffer.test_and_skip("struct ")) {
      struct_info& structi = ctx.structs.emplace_back();

      buffer.sws_read_till(structi.name, ";{" WHITESPACE);

      buffer.skip_ws();

      char c = buffer.get();
      if (c == '{') {
        for (;;) {
          member_info& memberi = structi.members.emplace_back();
          buffer.sws_read_till(memberi.type, WHITESPACE);
          buffer.sws_read_till(memberi.name, "[;," WHITESPACE);
          c = buffer.sws_get();

          memberi.count = 1;

          if (c == '[') {
            buffer.sws_read_till(tmp, "]");
            memberi.count = atoi(tmp);
            buffer.skip(1);
            c = buffer.sws_get();
          }

          if (c == ',') error("Can't handle multi variable names", buffer);
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
    }
    
    if (buffer.test_and_skip("void ")) {
      char name[64];
      buffer.sws_read_c_identifier(name);
      if (buffer.test_and_skip("(")) {
        function_info& funci = ctx.functions.emplace_back();
        copy(funci.name, name);

        while(buffer.sws_peek() != ')')
        {
          buffer.sws_read_till(tmp, ",)");
          if (!is_empty(tmp)) {
            function_parameter_info& para = funci.parameters.emplace_back();

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
 
    //TODO: we need a more flexible way to check for comments
    if (buffer.test_and_skip("//")) buffer.skip_line();
 }
}

void dump_cpp(ParseContext& c) {
  printf("#pragma once\n");
  printf("\n");
  printf("///////////////////////////////////////////////////////////////////\n");
  printf("//  AUTOGEN                                                      //\n");
  printf("///////////////////////////////////////////////////////////////////\n");


  //dump declaration
  for (auto& enumci : c.enum_classes) {
    printf("enum class                   %s;\n", enumci.name);
    printf("const char * to_string(const %s &);\n", enumci.name);
  }

  for (auto& structi : c.structs) {
    const char* sname = structi.name;

    puts("");
    printf("struct                %s;\n", structi.name);
    printf("bool operator==(const %s &lhs, const %s &rhs);\n", structi.name, structi.name);
    printf("bool operator!=(const %s &lhs, const %s &rhs);\n", structi.name, structi.name);
    printf("void      deserialize(%s &o, IDeserializer &s);\n", sname);
    printf("void        serialize(%s &o, ISerializer &s);\n", sname);
    printf("hash_value       hash(%s &o);\n", sname);
    puts("");
  }

  printf("\n#ifdef IMPL_SERIALIZER\n\n");
  //dump implementation
  for (auto& enumci : c.enum_classes) {
    printf("const char * to_string(const %s & e) {\n", enumci.name);
    printf("    switch(e) {\n");
    for (auto& enumi : enumci.enums) {
      printf("        case %s::%s: return \"%s\";\n", enumci.name, enumi.name, enumi.name);
    }
    printf("        default: retrun \"<UNKNOWN>\";\n");
    printf("    }\n");
    printf("}\n\n");
  }

  for (auto& structi : c.structs) {
    const char* sname = structi.name;

    printf("///////////////////////////////////////////////////////////////////\n");
    printf("//  struct %s\n", sname);
    printf("///////////////////////////////////////////////////////////////////\n");

    ///////////////////////////////////////////////////////////////////
    // == and != operator                                            //
    ///////////////////////////////////////////////////////////////////
    printf("bool operator==(const %s &lhs, const %s &rhs) { \n", structi.name, structi.name);
    printf("  return \n");
    int left = structi.members.size() - 1;
    for (auto& member : structi.members) {
      printf("    lhs.%s == rhs.%s%s\n", member.name, member.name, left ? " &&" : ";");
      --left;
    }
    printf("} \n\n");

    printf("bool operator!=(const %s &lhs, const %s &rhs) { \n", structi.name, structi.name);
    printf("  return \n");
    left = structi.members.size() - 1;
    for (auto& member : structi.members) {
      printf("    lhs.%s != rhs.%s%s\n", member.name, member.name, left ? " ||" : ";");
      --left;
    }
    printf("} \n\n");
  
    ///////////////////////////////////////////////////////////////////
    // serializer                                                    //
    // TODO: skip functions that are already declared
    ///////////////////////////////////////////////////////////////////
    printf("void serialize(%s &o, ISerializer &s) {                      \n", sname);
    printf("  if(s.node_begin(\"%s\", rose::hash(\"%s\"), &o)) {                \n", sname, sname);

    for (auto& member : structi.members) {
      const char* mname = member.name;
      printf("    s.key(\"%s\");                                                \n", mname);
      printf("    serialize(o.%s, s);                                           \n", mname);
    }
    printf("    s.node_end();                                                   \n");
    printf("  }                                                                 \n");
    printf("  s.end();                                                          \n");
    printf("}                                                                   \n\n");

    ///////////////////////////////////////////////////////////////////
    // deserializer                                                  //
    // TODO: skip functions that are already declared
    ///////////////////////////////////////////////////////////////////
    printf("void deserialize(%s &o, IDeserializer &s) {              \n", sname);
    printf("  construct_defaults(o);                                 \n");
    printf("                                                         \n");
    printf("  while (s.next_key()) {                                 \n");
    printf("    switch (s.hash_key()) {                              \n");

    for (auto& member : structi.members) {
      const char* mname = member.name;
      printf("      case rose::hash(\"%s\"):                         \n", mname);
      printf("        deserialize(o.%s, s);                          \n", mname);
      printf("        break;                                         \n");
    }
    printf("      default: s.skip_key(); break;                      \n");
    printf("    }                                                    \n");
    printf("  }                                                      \n");
    printf("}                                                        \n\n");

    ///////////////////////////////////////////////////////////////////
    // hashing                                                       //
    ///////////////////////////////////////////////////////////////////
    printf("hash_value hash(%s &o) {              \n", sname);
    printf("  hash_value h = 0;                   \n");

    for (auto& member : structi.members) {
      const char* mname = member.name;
      printf("  h ^= hash(o.%s);                  \n", mname);
      printf("  h = xor64(h);                     \n");
    }

    printf("  return h;                           \n");
    printf("}                                     \n");


  }



  //end
  printf("\n#endif\n");

}

int main(int argc, char** argv) {
  if (argc < 2) {
    printhelp();
    exit(1);
  }

  hash_value state = hash("NONE");

  const char* output_path = "stdout";
  
  for (int i = 1; i < argc; ++i) {
    const char* arg = argv[i];
    hash_value h = hash(arg);
    if (h == hash("--help") || h == hash("-H")) {
      printhelp();
      continue;
    }
    if (h == hash("--include") || h == hash("-I")) {
      state = hash("INCLUDE");
      continue;
    }
    if (h == hash("--output") || h == hash("-O")) {
      ++i;
      assert(i != argc);
      const char* path = argv[i];
      output_path = path;
      (void)freopen(output_path, "wb", stdout);
      continue;
    }

    switch (state) {
    case hash("INCLUDE"): input_files.push_back(arg); break;
    default: printf("Unknown argument %s. \n", arg); exit(1); break;
    }
  }

  ParseContext c;

  for (auto path : input_files) {
    StreamBuffer buffer;
    buffer.load(path);
    parse(c, buffer);
    buffer.unload();
  }
  
  dump_cpp(c);

  if (hash(output_path) != hash("stdout")) {
    fclose(stdout);
  }

  return 0;
}
