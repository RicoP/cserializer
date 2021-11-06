#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <vector>

struct StreamBuffer {
  static constexpr size_t buffer_size_max = 1024;

  size_t buffer_head = 0;
  size_t buffer_size = 0;
  int cursor_column = 0;
  int cursor_line = 1;

  char buffer[2 * buffer_size_max] = "";

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
    assert(end() < buffer + buffer_size_max);
    size_t count = fread(end(), 1, buffer_size_max, file);
    assert(count <= buffer_size_max);
    buffer_size += count;
    eof = count == 0;
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
    cursor_column++;
    if (c == '\n') {
      cursor_column = 0;
      cursor_line++;
    }
    ++buffer_head;
    --buffer_size;

    return c;
  }

  void skip_ws() {
    for (;;) {
      switch (peek()) {
      case ' ': case '\n': case '\r': case '\t':
        get();
        break;
      default: return;
      }
    }
  }

  void skip_line() {
    for (;;) {
      char c = get();
      if (c == '\n' || eof) return;
    }
  }

  bool test_and_skip(const char * str, size_t len) {
    skip_ws();
    assert(len < buffer_size_max);

    if (buffer_size < len) fetch();
    if (buffer_size < len) return false;

    for (size_t i = 0; i != len; ++i) {
      if (begin()[i] != str[i]) return false;
    }
    buffer_head += len;
    buffer_size -= len;
    return true;
  }

  template<size_t N>
  bool test_and_skip(const char (& str)[N]) {
    return test_and_skip(str, N-1);
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
  fprintf(stderr, "%s: %s(%i:%i)\n", msg, buffer.path, buffer.cursor_line, buffer.cursor_column);
  exit(1);
}

void parse(StreamBuffer & buffer) {
  char tmp[64];
  while (!buffer.eof)
  {
    if (buffer.test_and_skip("#")) {
      //Macro
      if (buffer.test_and_skip("include")) {
        buffer.skip_line();
      }
      else {
        error("unknown PP macro.", buffer);
      }
    }
    if (buffer.test_and_skip("struct ")) {
      buffer.skip_ws();
      char* p = tmp;
      char c;
      for (;;) {
        assert(p != tmp + sizeof(tmp));
        c = buffer.peek();
        
        if (c == ';' || c == '{' || c == ' ' || c == '\t' || c == '\n' || c == '\r') {
          *p = 0;
          break;
        }
        *p = buffer.get();
        ++p;
      }
      printf("struct %s", tmp);
      buffer.skip_ws();

    }
  }
}

int main(int argc, char ** argv) {
	if (argc < 2) {
		printhelp();
		exit(1);
	}

  hash_value state = hash("NONE");

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

    switch (state) {
    case hash("INCLUDE"): input_files.push_back(arg); break;
    default: printf("Unknown argument %s. \n", arg); exit(1); break;
    }
	}

  for (auto path : input_files) {
    StreamBuffer buffer;
    buffer.load(path);

    parse(buffer);

    buffer.unload();

  }


	return 0;
}