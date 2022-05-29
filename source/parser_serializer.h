#pragma once

#include <rose/hash.h>
#include <rose/typetraits.h>
#include <serializer/serializer.h>

///////////////////////////////////////////////////////////////////
//  AUTOGEN                                                      //
//  command:
//    rose.parser --include parser.h -O parser_serializer.h
///////////////////////////////////////////////////////////////////

enum class                   member_annotations_t;
const char * to_string(const member_annotations_t &);
namespace rose {
  namespace ecs {
    void      deserialize(member_annotations_t &o, IDeserializer &s);
    void        serialize(member_annotations_t &o, ISerializer &s);
  }
  template<>
  struct type_id<member_annotations_t> {
    inline static hash_value VALUE = 17628469563951837410ULL;
  };
  hash_value         hash(const member_annotations_t &o);
  void construct_defaults(      member_annotations_t &o); //implement me
}

inline member_annotations_t operator|(const member_annotations_t &a, const member_annotations_t &b) { return static_cast<member_annotations_t>(static_cast<int>(a) | static_cast<int>(b)); }
inline member_annotations_t operator|=(member_annotations_t &a, const member_annotations_t &b) { return a = a | b; }
inline member_annotations_t operator&(const member_annotations_t &a, const member_annotations_t &b) { return static_cast<member_annotations_t>(static_cast<int>(a) & static_cast<int>(b)); }
inline member_annotations_t operator&=(member_annotations_t &a, const member_annotations_t &b) { return a = a & b; }
inline member_annotations_t operator^(const member_annotations_t &a, const member_annotations_t &b) { return static_cast<member_annotations_t>(static_cast<int>(a) ^ static_cast<int>(b)); }
inline member_annotations_t operator^=(member_annotations_t &a, const member_annotations_t &b) { return a = a ^ b; }
inline bool operator!(const member_annotations_t &e) { return static_cast<int>(e) == 0; }


enum class                   value_type_t;
const char * to_string(const value_type_t &);
namespace rose {
  namespace ecs {
    void      deserialize(value_type_t &o, IDeserializer &s);
    void        serialize(value_type_t &o, ISerializer &s);
  }
  template<>
  struct type_id<value_type_t> {
    inline static hash_value VALUE = 16616308554880477217ULL;
  };
  hash_value         hash(const value_type_t &o);
  void construct_defaults(      value_type_t &o); //implement me
}


enum class                   global_annotations_t;
const char * to_string(const global_annotations_t &);
namespace rose {
  namespace ecs {
    void      deserialize(global_annotations_t &o, IDeserializer &s);
    void        serialize(global_annotations_t &o, ISerializer &s);
  }
  template<>
  struct type_id<global_annotations_t> {
    inline static hash_value VALUE = 11019223828604062051ULL;
  };
  hash_value         hash(const global_annotations_t &o);
  void construct_defaults(      global_annotations_t &o); //implement me
}


enum class                   Member_info_kind;
const char * to_string(const Member_info_kind &);
namespace rose {
  namespace ecs {
    void      deserialize(Member_info_kind &o, IDeserializer &s);
    void        serialize(Member_info_kind &o, ISerializer &s);
  }
  template<>
  struct type_id<Member_info_kind> {
    inline static hash_value VALUE = 15943902494292007213ULL;
  };
  hash_value         hash(const Member_info_kind &o);
  void construct_defaults(      Member_info_kind &o); //implement me
}


struct                member_info;
namespace rose {
  namespace ecs {
    void        serialize(member_info &o, ISerializer &s);
    void      deserialize(member_info &o, IDeserializer &s);
  }
  hash_value         hash(const member_info &o);
  template<>
  struct type_id<member_info> {
    inline static hash_value VALUE = 7925914296115135804ULL;
  };
  void construct_defaults(      member_info &o); // implement me
}
bool operator==(const member_info &lhs, const member_info &rhs);
bool operator!=(const member_info &lhs, const member_info &rhs);


struct                struct_info;
namespace rose {
  namespace ecs {
    void        serialize(struct_info &o, ISerializer &s);
    void      deserialize(struct_info &o, IDeserializer &s);
  }
  hash_value         hash(const struct_info &o);
  template<>
  struct type_id<struct_info> {
    inline static hash_value VALUE = 9250458120049481396ULL;
  };
  void construct_defaults(      struct_info &o); // implement me
}
bool operator==(const struct_info &lhs, const struct_info &rhs);
bool operator!=(const struct_info &lhs, const struct_info &rhs);


struct                enum_info;
namespace rose {
  namespace ecs {
    void        serialize(enum_info &o, ISerializer &s);
    void      deserialize(enum_info &o, IDeserializer &s);
  }
  hash_value         hash(const enum_info &o);
  template<>
  struct type_id<enum_info> {
    inline static hash_value VALUE = 588653192025808279ULL;
  };
  void construct_defaults(      enum_info &o); // implement me
}
bool operator==(const enum_info &lhs, const enum_info &rhs);
bool operator!=(const enum_info &lhs, const enum_info &rhs);


struct                namespace_path;
namespace rose {
  namespace ecs {
    void        serialize(namespace_path &o, ISerializer &s);
    void      deserialize(namespace_path &o, IDeserializer &s);
  }
  hash_value         hash(const namespace_path &o);
  template<>
  struct type_id<namespace_path> {
    inline static hash_value VALUE = 18093028248585243773ULL;
  };
  void construct_defaults(      namespace_path &o); // implement me
}
bool operator==(const namespace_path &lhs, const namespace_path &rhs);
bool operator!=(const namespace_path &lhs, const namespace_path &rhs);


struct                enum_class_info;
namespace rose {
  namespace ecs {
    void        serialize(enum_class_info &o, ISerializer &s);
    void      deserialize(enum_class_info &o, IDeserializer &s);
  }
  hash_value         hash(const enum_class_info &o);
  template<>
  struct type_id<enum_class_info> {
    inline static hash_value VALUE = 3370360874422677731ULL;
  };
  void construct_defaults(      enum_class_info &o); // implement me
}
bool operator==(const enum_class_info &lhs, const enum_class_info &rhs);
bool operator!=(const enum_class_info &lhs, const enum_class_info &rhs);


struct                function_parameter_info;
namespace rose {
  namespace ecs {
    void        serialize(function_parameter_info &o, ISerializer &s);
    void      deserialize(function_parameter_info &o, IDeserializer &s);
  }
  hash_value         hash(const function_parameter_info &o);
  template<>
  struct type_id<function_parameter_info> {
    inline static hash_value VALUE = 12916637819691711945ULL;
  };
  void construct_defaults(      function_parameter_info &o); // implement me
}
bool operator==(const function_parameter_info &lhs, const function_parameter_info &rhs);
bool operator!=(const function_parameter_info &lhs, const function_parameter_info &rhs);


struct                function_info;
namespace rose {
  namespace ecs {
    void        serialize(function_info &o, ISerializer &s);
    void      deserialize(function_info &o, IDeserializer &s);
  }
  hash_value         hash(const function_info &o);
  template<>
  struct type_id<function_info> {
    inline static hash_value VALUE = 1111435755889198206ULL;
  };
  void construct_defaults(      function_info &o); // implement me
}
bool operator==(const function_info &lhs, const function_info &rhs);
bool operator!=(const function_info &lhs, const function_info &rhs);


struct                ParseContext;
namespace rose {
  namespace ecs {
    void        serialize(ParseContext &o, ISerializer &s);
    void      deserialize(ParseContext &o, IDeserializer &s);
  }
  hash_value         hash(const ParseContext &o);
  template<>
  struct type_id<ParseContext> {
    inline static hash_value VALUE = 12980077085926260329ULL;
  };
  void construct_defaults(      ParseContext &o); // implement me
}
bool operator==(const ParseContext &lhs, const ParseContext &rhs);
bool operator!=(const ParseContext &lhs, const ParseContext &rhs);


#ifdef IMPL_SERIALIZER

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
  
const char * to_string(const member_annotations_t & e) {
    switch(e) {
        case member_annotations_t::NONE: return "NONE";
        case member_annotations_t::Ignore: return "Ignore";
        case member_annotations_t::String: return "String";
        case member_annotations_t::Data: return "Data";
        default: return "<UNKNOWN>";
    }
}
void rose::ecs::serialize(member_annotations_t& o, ISerializer& s) {
  switch (o) {
    case member_annotations_t::NONE: {
      char str[] = "NONE";
      serialize(str, s);
      break;
    }
    case member_annotations_t::Ignore: {
      char str[] = "Ignore";
      serialize(str, s);
      break;
    }
    case member_annotations_t::String: {
      char str[] = "String";
      serialize(str, s);
      break;
    }
    case member_annotations_t::Data: {
      char str[] = "Data";
      serialize(str, s);
      break;
    }
    default: /* unknown */ break;
  }
}
void rose::ecs::deserialize(member_annotations_t& o, IDeserializer& s) {
  char str[64];
  deserialize(str, s);
  rose::hash_value h = rose::hash(str);
  switch (h) {
  case rose::hash("NONE"): o = member_annotations_t::NONE; break;
  case rose::hash("Ignore"): o = member_annotations_t::Ignore; break;
  case rose::hash("String"): o = member_annotations_t::String; break;
  case rose::hash("Data"): o = member_annotations_t::Data; break;
  default: /*unknown value*/ break;
  }
}
rose::hash_value       rose::hash(const member_annotations_t& o) {
  return static_cast<rose::hash_value>(o);
}

const char * to_string(const value_type_t & e) {
    switch(e) {
        case value_type_t::Increment: return "Increment";
        case value_type_t::Set: return "Set";
        default: return "<UNKNOWN>";
    }
}
void rose::ecs::serialize(value_type_t& o, ISerializer& s) {
  switch (o) {
    case value_type_t::Increment: {
      char str[] = "Increment";
      serialize(str, s);
      break;
    }
    case value_type_t::Set: {
      char str[] = "Set";
      serialize(str, s);
      break;
    }
    default: /* unknown */ break;
  }
}
void rose::ecs::deserialize(value_type_t& o, IDeserializer& s) {
  char str[64];
  deserialize(str, s);
  rose::hash_value h = rose::hash(str);
  switch (h) {
  case rose::hash("Increment"): o = value_type_t::Increment; break;
  case rose::hash("Set"): o = value_type_t::Set; break;
  default: /*unknown value*/ break;
  }
}
rose::hash_value       rose::hash(const value_type_t& o) {
  return static_cast<rose::hash_value>(o);
}

const char * to_string(const global_annotations_t & e) {
    switch(e) {
        case global_annotations_t::NONE: return "NONE";
        case global_annotations_t::Flag: return "Flag";
        case global_annotations_t::Imposter: return "Imposter";
        default: return "<UNKNOWN>";
    }
}
void rose::ecs::serialize(global_annotations_t& o, ISerializer& s) {
  switch (o) {
    case global_annotations_t::NONE: {
      char str[] = "NONE";
      serialize(str, s);
      break;
    }
    case global_annotations_t::Flag: {
      char str[] = "Flag";
      serialize(str, s);
      break;
    }
    case global_annotations_t::Imposter: {
      char str[] = "Imposter";
      serialize(str, s);
      break;
    }
    default: /* unknown */ break;
  }
}
void rose::ecs::deserialize(global_annotations_t& o, IDeserializer& s) {
  char str[64];
  deserialize(str, s);
  rose::hash_value h = rose::hash(str);
  switch (h) {
  case rose::hash("NONE"): o = global_annotations_t::NONE; break;
  case rose::hash("Flag"): o = global_annotations_t::Flag; break;
  case rose::hash("Imposter"): o = global_annotations_t::Imposter; break;
  default: /*unknown value*/ break;
  }
}
rose::hash_value       rose::hash(const global_annotations_t& o) {
  return static_cast<rose::hash_value>(o);
}

const char * to_string(const Member_info_kind & e) {
    switch(e) {
        case Member_info_kind::NONE: return "NONE";
        case Member_info_kind::Field: return "Field";
        case Member_info_kind::Function: return "Function";
        default: return "<UNKNOWN>";
    }
}
void rose::ecs::serialize(Member_info_kind& o, ISerializer& s) {
  switch (o) {
    case Member_info_kind::NONE: {
      char str[] = "NONE";
      serialize(str, s);
      break;
    }
    case Member_info_kind::Field: {
      char str[] = "Field";
      serialize(str, s);
      break;
    }
    case Member_info_kind::Function: {
      char str[] = "Function";
      serialize(str, s);
      break;
    }
    default: /* unknown */ break;
  }
}
void rose::ecs::deserialize(Member_info_kind& o, IDeserializer& s) {
  char str[64];
  deserialize(str, s);
  rose::hash_value h = rose::hash(str);
  switch (h) {
  case rose::hash("NONE"): o = Member_info_kind::NONE; break;
  case rose::hash("Field"): o = Member_info_kind::Field; break;
  case rose::hash("Function"): o = Member_info_kind::Function; break;
  default: /*unknown value*/ break;
  }
}
rose::hash_value       rose::hash(const Member_info_kind& o) {
  return static_cast<rose::hash_value>(o);
}

///////////////////////////////////////////////////////////////////
//  struct member_info
///////////////////////////////////////////////////////////////////
bool operator==(const member_info &lhs, const member_info &rhs) {
  return
    rose_parser_equals(lhs.kind, rhs.kind) &&
    rose_parser_equals(lhs.type, rhs.type) &&
    rose_parser_equals(lhs.name, rhs.name) &&
    rose_parser_equals(lhs.default_value, rhs.default_value) &&
    rose_parser_equals(lhs.count, rhs.count) &&
    rose_parser_equals(lhs.annotations, rhs.annotations) ;
}

bool operator!=(const member_info &lhs, const member_info &rhs) {
  return
    !rose_parser_equals(lhs.kind, rhs.kind) ||
    !rose_parser_equals(lhs.type, rhs.type) ||
    !rose_parser_equals(lhs.name, rhs.name) ||
    !rose_parser_equals(lhs.default_value, rhs.default_value) ||
    !rose_parser_equals(lhs.count, rhs.count) ||
    !rose_parser_equals(lhs.annotations, rhs.annotations) ;
}

void rose::ecs::serialize(member_info &o, ISerializer &s) {
  if(s.node_begin("member_info", rose::hash("member_info"), &o)) {
    s.key("kind");
    serialize(o.kind, s);
    s.key("type");
    serialize(o.type, s, std::strlen(o.type));
    s.key("name");
    serialize(o.name, s, std::strlen(o.name));
    s.key("default_value");
    serialize(o.default_value, s, std::strlen(o.default_value));
    s.key("count");
    serialize(o.count, s);
    s.key("annotations");
    serialize(o.annotations, s);
    s.node_end();
  }
  s.end();
}

void rose::ecs::deserialize(member_info &o, IDeserializer &s) {
  //implement me
  //construct_defaults(o);

  while (s.next_key()) {
    switch (s.hash_key()) {
      case rose::hash("kind"):
        deserialize(o.kind, s);
        break;
      case rose::hash("type"):
        deserialize(o.type, s);
        break;
      case rose::hash("name"):
        deserialize(o.name, s);
        break;
      case rose::hash("default_value"):
        deserialize(o.default_value, s);
        break;
      case rose::hash("count"):
        deserialize(o.count, s);
        break;
      case rose::hash("annotations"):
        deserialize(o.annotations, s);
        break;
      default: s.skip_key(); break;
    }
  }
}

rose::hash_value rose::hash(const member_info &o) {
  rose::hash_value h = rose::hash(o.kind);
  h = rose::xor64(h);
  h ^= rose::hash(o.type);
  h = rose::xor64(h);
  h ^= rose::hash(o.name);
  h = rose::xor64(h);
  h ^= rose::hash(o.default_value);
  h = rose::xor64(h);
  h ^= rose::hash(o.count);
  h = rose::xor64(h);
  h ^= rose::hash(o.annotations);
  return h;
}
///////////////////////////////////////////////////////////////////
//  struct struct_info
///////////////////////////////////////////////////////////////////
bool operator==(const struct_info &lhs, const struct_info &rhs) {
  return
    rose_parser_equals(lhs.name, rhs.name) &&
    rose_parser_equals(lhs.global_annotations, rhs.global_annotations) &&
    rose_parser_equals(lhs.members, rhs.members) ;
}

bool operator!=(const struct_info &lhs, const struct_info &rhs) {
  return
    !rose_parser_equals(lhs.name, rhs.name) ||
    !rose_parser_equals(lhs.global_annotations, rhs.global_annotations) ||
    !rose_parser_equals(lhs.members, rhs.members) ;
}

void rose::ecs::serialize(struct_info &o, ISerializer &s) {
  if(s.node_begin("struct_info", rose::hash("struct_info"), &o)) {
    s.key("name");
    serialize(o.name, s, std::strlen(o.name));
    s.key("global_annotations");
    serialize(o.global_annotations, s);
    s.key("members");
    serialize(o.members, s);
    s.node_end();
  }
  s.end();
}

void rose::ecs::deserialize(struct_info &o, IDeserializer &s) {
  //implement me
  //construct_defaults(o);

  while (s.next_key()) {
    switch (s.hash_key()) {
      case rose::hash("name"):
        deserialize(o.name, s);
        break;
      case rose::hash("global_annotations"):
        deserialize(o.global_annotations, s);
        break;
      case rose::hash("members"):
        deserialize(o.members, s);
        break;
      default: s.skip_key(); break;
    }
  }
}

rose::hash_value rose::hash(const struct_info &o) {
  rose::hash_value h = rose::hash(o.name);
  h = rose::xor64(h);
  h ^= rose::hash(o.global_annotations);
  h = rose::xor64(h);
  h ^= rose::hash(o.members);
  return h;
}
///////////////////////////////////////////////////////////////////
//  struct enum_info
///////////////////////////////////////////////////////////////////
bool operator==(const enum_info &lhs, const enum_info &rhs) {
  return
    rose_parser_equals(lhs.name, rhs.name) &&
    rose_parser_equals(lhs.value, rhs.value) &&
    rose_parser_equals(lhs.value_type, rhs.value_type) ;
}

bool operator!=(const enum_info &lhs, const enum_info &rhs) {
  return
    !rose_parser_equals(lhs.name, rhs.name) ||
    !rose_parser_equals(lhs.value, rhs.value) ||
    !rose_parser_equals(lhs.value_type, rhs.value_type) ;
}

void rose::ecs::serialize(enum_info &o, ISerializer &s) {
  if(s.node_begin("enum_info", rose::hash("enum_info"), &o)) {
    s.key("name");
    serialize(o.name, s, std::strlen(o.name));
    s.key("value");
    serialize(o.value, s, std::strlen(o.value));
    s.key("value_type");
    serialize(o.value_type, s);
    s.node_end();
  }
  s.end();
}

void rose::ecs::deserialize(enum_info &o, IDeserializer &s) {
  //implement me
  //construct_defaults(o);

  while (s.next_key()) {
    switch (s.hash_key()) {
      case rose::hash("name"):
        deserialize(o.name, s);
        break;
      case rose::hash("value"):
        deserialize(o.value, s);
        break;
      case rose::hash("value_type"):
        deserialize(o.value_type, s);
        break;
      default: s.skip_key(); break;
    }
  }
}

rose::hash_value rose::hash(const enum_info &o) {
  rose::hash_value h = rose::hash(o.name);
  h = rose::xor64(h);
  h ^= rose::hash(o.value);
  h = rose::xor64(h);
  h ^= rose::hash(o.value_type);
  return h;
}
///////////////////////////////////////////////////////////////////
//  struct namespace_path
///////////////////////////////////////////////////////////////////
bool operator==(const namespace_path &lhs, const namespace_path &rhs) {
  return
    rose_parser_equals(lhs.path, rhs.path) ;
}

bool operator!=(const namespace_path &lhs, const namespace_path &rhs) {
  return
    !rose_parser_equals(lhs.path, rhs.path) ;
}

void rose::ecs::serialize(namespace_path &o, ISerializer &s) {
  if(s.node_begin("namespace_path", rose::hash("namespace_path"), &o)) {
    s.key("path");
    serialize(o.path, s, std::strlen(o.path));
    s.node_end();
  }
  s.end();
}

void rose::ecs::deserialize(namespace_path &o, IDeserializer &s) {
  //implement me
  //construct_defaults(o);

  while (s.next_key()) {
    switch (s.hash_key()) {
      case rose::hash("path"):
        deserialize(o.path, s);
        break;
      default: s.skip_key(); break;
    }
  }
}

rose::hash_value rose::hash(const namespace_path &o) {
  rose::hash_value h = rose::hash(o.path);
  return h;
}
///////////////////////////////////////////////////////////////////
//  struct enum_class_info
///////////////////////////////////////////////////////////////////
bool operator==(const enum_class_info &lhs, const enum_class_info &rhs) {
  return
    rose_parser_equals(lhs.name_withns, rhs.name_withns) &&
    rose_parser_equals(lhs.name_withoutns, rhs.name_withoutns) &&
    rose_parser_equals(lhs.type, rhs.type) &&
    rose_parser_equals(lhs.custom_type, rhs.custom_type) &&
    rose_parser_equals(lhs.enums, rhs.enums) &&
    rose_parser_equals(lhs.namespaces, rhs.namespaces) &&
    rose_parser_equals(lhs.default_value, rhs.default_value) &&
    rose_parser_equals(lhs.enum_annotations, rhs.enum_annotations) ;
}

bool operator!=(const enum_class_info &lhs, const enum_class_info &rhs) {
  return
    !rose_parser_equals(lhs.name_withns, rhs.name_withns) ||
    !rose_parser_equals(lhs.name_withoutns, rhs.name_withoutns) ||
    !rose_parser_equals(lhs.type, rhs.type) ||
    !rose_parser_equals(lhs.custom_type, rhs.custom_type) ||
    !rose_parser_equals(lhs.enums, rhs.enums) ||
    !rose_parser_equals(lhs.namespaces, rhs.namespaces) ||
    !rose_parser_equals(lhs.default_value, rhs.default_value) ||
    !rose_parser_equals(lhs.enum_annotations, rhs.enum_annotations) ;
}

void rose::ecs::serialize(enum_class_info &o, ISerializer &s) {
  if(s.node_begin("enum_class_info", rose::hash("enum_class_info"), &o)) {
    s.key("name_withns");
    serialize(o.name_withns, s, std::strlen(o.name_withns));
    s.key("name_withoutns");
    serialize(o.name_withoutns, s, std::strlen(o.name_withoutns));
    s.key("type");
    serialize(o.type, s, std::strlen(o.type));
    s.key("custom_type");
    serialize(o.custom_type, s);
    s.key("enums");
    serialize(o.enums, s);
    s.key("namespaces");
    serialize(o.namespaces, s);
    s.key("default_value");
    serialize(o.default_value, s);
    s.key("enum_annotations");
    serialize(o.enum_annotations, s);
    s.node_end();
  }
  s.end();
}

void rose::ecs::deserialize(enum_class_info &o, IDeserializer &s) {
  //implement me
  //construct_defaults(o);

  while (s.next_key()) {
    switch (s.hash_key()) {
      case rose::hash("name_withns"):
        deserialize(o.name_withns, s);
        break;
      case rose::hash("name_withoutns"):
        deserialize(o.name_withoutns, s);
        break;
      case rose::hash("type"):
        deserialize(o.type, s);
        break;
      case rose::hash("custom_type"):
        deserialize(o.custom_type, s);
        break;
      case rose::hash("enums"):
        deserialize(o.enums, s);
        break;
      case rose::hash("namespaces"):
        deserialize(o.namespaces, s);
        break;
      case rose::hash("default_value"):
        deserialize(o.default_value, s);
        break;
      case rose::hash("enum_annotations"):
        deserialize(o.enum_annotations, s);
        break;
      default: s.skip_key(); break;
    }
  }
}

rose::hash_value rose::hash(const enum_class_info &o) {
  rose::hash_value h = rose::hash(o.name_withns);
  h = rose::xor64(h);
  h ^= rose::hash(o.name_withoutns);
  h = rose::xor64(h);
  h ^= rose::hash(o.type);
  h = rose::xor64(h);
  h ^= rose::hash(o.custom_type);
  h = rose::xor64(h);
  h ^= rose::hash(o.enums);
  h = rose::xor64(h);
  h ^= rose::hash(o.namespaces);
  h = rose::xor64(h);
  h ^= rose::hash(o.default_value);
  h = rose::xor64(h);
  h ^= rose::hash(o.enum_annotations);
  return h;
}
///////////////////////////////////////////////////////////////////
//  struct function_parameter_info
///////////////////////////////////////////////////////////////////
bool operator==(const function_parameter_info &lhs, const function_parameter_info &rhs) {
  return
    rose_parser_equals(lhs.name, rhs.name) &&
    rose_parser_equals(lhs.type, rhs.type) &&
    rose_parser_equals(lhs.modifier, rhs.modifier) &&
    rose_parser_equals(lhs.is_const, rhs.is_const) ;
}

bool operator!=(const function_parameter_info &lhs, const function_parameter_info &rhs) {
  return
    !rose_parser_equals(lhs.name, rhs.name) ||
    !rose_parser_equals(lhs.type, rhs.type) ||
    !rose_parser_equals(lhs.modifier, rhs.modifier) ||
    !rose_parser_equals(lhs.is_const, rhs.is_const) ;
}

void rose::ecs::serialize(function_parameter_info &o, ISerializer &s) {
  if(s.node_begin("function_parameter_info", rose::hash("function_parameter_info"), &o)) {
    s.key("name");
    serialize(o.name, s, std::strlen(o.name));
    s.key("type");
    serialize(o.type, s, std::strlen(o.type));
    s.key("modifier");
    serialize(o.modifier, s);
    s.key("is_const");
    serialize(o.is_const, s);
    s.node_end();
  }
  s.end();
}

void rose::ecs::deserialize(function_parameter_info &o, IDeserializer &s) {
  //implement me
  //construct_defaults(o);

  while (s.next_key()) {
    switch (s.hash_key()) {
      case rose::hash("name"):
        deserialize(o.name, s);
        break;
      case rose::hash("type"):
        deserialize(o.type, s);
        break;
      case rose::hash("modifier"):
        deserialize(o.modifier, s);
        break;
      case rose::hash("is_const"):
        deserialize(o.is_const, s);
        break;
      default: s.skip_key(); break;
    }
  }
}

rose::hash_value rose::hash(const function_parameter_info &o) {
  rose::hash_value h = rose::hash(o.name);
  h = rose::xor64(h);
  h ^= rose::hash(o.type);
  h = rose::xor64(h);
  h ^= rose::hash(o.modifier);
  h = rose::xor64(h);
  h ^= rose::hash(o.is_const);
  return h;
}
///////////////////////////////////////////////////////////////////
//  struct function_info
///////////////////////////////////////////////////////////////////
bool operator==(const function_info &lhs, const function_info &rhs) {
  return
    rose_parser_equals(lhs.name, rhs.name) &&
    rose_parser_equals(lhs.type, rhs.type) &&
    rose_parser_equals(lhs.parameters, rhs.parameters) ;
}

bool operator!=(const function_info &lhs, const function_info &rhs) {
  return
    !rose_parser_equals(lhs.name, rhs.name) ||
    !rose_parser_equals(lhs.type, rhs.type) ||
    !rose_parser_equals(lhs.parameters, rhs.parameters) ;
}

void rose::ecs::serialize(function_info &o, ISerializer &s) {
  if(s.node_begin("function_info", rose::hash("function_info"), &o)) {
    s.key("name");
    serialize(o.name, s, std::strlen(o.name));
    s.key("type");
    serialize(o.type, s, std::strlen(o.type));
    s.key("parameters");
    serialize(o.parameters, s);
    s.node_end();
  }
  s.end();
}

void rose::ecs::deserialize(function_info &o, IDeserializer &s) {
  //implement me
  //construct_defaults(o);

  while (s.next_key()) {
    switch (s.hash_key()) {
      case rose::hash("name"):
        deserialize(o.name, s);
        break;
      case rose::hash("type"):
        deserialize(o.type, s);
        break;
      case rose::hash("parameters"):
        deserialize(o.parameters, s);
        break;
      default: s.skip_key(); break;
    }
  }
}

rose::hash_value rose::hash(const function_info &o) {
  rose::hash_value h = rose::hash(o.name);
  h = rose::xor64(h);
  h ^= rose::hash(o.type);
  h = rose::xor64(h);
  h ^= rose::hash(o.parameters);
  return h;
}
///////////////////////////////////////////////////////////////////
//  struct ParseContext
///////////////////////////////////////////////////////////////////
bool operator==(const ParseContext &lhs, const ParseContext &rhs) {
  return
    rose_parser_equals(lhs.enum_classes, rhs.enum_classes) &&
    rose_parser_equals(lhs.functions, rhs.functions) &&
    rose_parser_equals(lhs.structs, rhs.structs) ;
}

bool operator!=(const ParseContext &lhs, const ParseContext &rhs) {
  return
    !rose_parser_equals(lhs.enum_classes, rhs.enum_classes) ||
    !rose_parser_equals(lhs.functions, rhs.functions) ||
    !rose_parser_equals(lhs.structs, rhs.structs) ;
}

void rose::ecs::serialize(ParseContext &o, ISerializer &s) {
  if(s.node_begin("ParseContext", rose::hash("ParseContext"), &o)) {
    s.key("enum_classes");
    serialize(o.enum_classes, s);
    s.key("functions");
    serialize(o.functions, s);
    s.key("structs");
    serialize(o.structs, s);
    s.node_end();
  }
  s.end();
}

void rose::ecs::deserialize(ParseContext &o, IDeserializer &s) {
  //implement me
  //construct_defaults(o);

  while (s.next_key()) {
    switch (s.hash_key()) {
      case rose::hash("enum_classes"):
        deserialize(o.enum_classes, s);
        break;
      case rose::hash("functions"):
        deserialize(o.functions, s);
        break;
      case rose::hash("structs"):
        deserialize(o.structs, s);
        break;
      default: s.skip_key(); break;
    }
  }
}

rose::hash_value rose::hash(const ParseContext &o) {
  rose::hash_value h = rose::hash(o.enum_classes);
  h = rose::xor64(h);
  h ^= rose::hash(o.functions);
  h = rose::xor64(h);
  h ^= rose::hash(o.structs);
  return h;
}

#endif
