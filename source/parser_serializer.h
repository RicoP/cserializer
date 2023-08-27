#pragma once

#include <new>
#include <rose/hash.h>
#include <rose/typetraits.h>
#include <rose/serializer.h>
#include <rose/world.h>

///////////////////////////////////////////////////////////////////
//  AUTOGEN
//  command:
//    rose.parser --include parser.h -O parser_serializer.h
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
//  predef enum member_annotations_t
///////////////////////////////////////////////////////////////////

inline rose::BoolConvertible<member_annotations_t> operator|(const member_annotations_t &lhs, const member_annotations_t &rhs) { return { static_cast<member_annotations_t>(static_cast<int>(lhs) | static_cast<int>(rhs)) }; }
inline rose::BoolConvertible<member_annotations_t> operator&(const member_annotations_t &lhs, const member_annotations_t &rhs) { return { static_cast<member_annotations_t>(static_cast<int>(lhs) & static_cast<int>(rhs)) }; }
inline rose::BoolConvertible<member_annotations_t> operator^(const member_annotations_t &lhs, const member_annotations_t &rhs) { return { static_cast<member_annotations_t>(static_cast<int>(lhs) ^ static_cast<int>(rhs)) }; }
inline member_annotations_t operator|=(member_annotations_t & lhs, member_annotations_t rhs) { return lhs = lhs | rhs; }
inline member_annotations_t operator&=(member_annotations_t & lhs, member_annotations_t rhs) { return lhs = lhs & rhs; }
inline member_annotations_t operator^=(member_annotations_t & lhs, member_annotations_t rhs) { return lhs = lhs ^ rhs; }
namespace rose {
inline const char * to_string(const member_annotations_t & e);
inline void serialize(member_annotations_t& o, ISerializer& s);
inline void deserialize(member_annotations_t& o, IDeserializer& s);
inline RHash       hash(const member_annotations_t& o);
} //namespace rose

///////////////////////////////////////////////////////////////////
//  predef enum value_type_t
///////////////////////////////////////////////////////////////////
namespace rose {
inline const char * to_string(const value_type_t & e);
inline void serialize(value_type_t& o, ISerializer& s);
inline void deserialize(value_type_t& o, IDeserializer& s);
inline RHash       hash(const value_type_t& o);
} //namespace rose

///////////////////////////////////////////////////////////////////
//  predef enum global_annotations_t
///////////////////////////////////////////////////////////////////
namespace rose {
inline const char * to_string(const global_annotations_t & e);
inline void serialize(global_annotations_t& o, ISerializer& s);
inline void deserialize(global_annotations_t& o, IDeserializer& s);
inline RHash       hash(const global_annotations_t& o);
} //namespace rose

///////////////////////////////////////////////////////////////////
//  predef enum Member_info_kind
///////////////////////////////////////////////////////////////////
namespace rose {
inline const char * to_string(const Member_info_kind & e);
inline void serialize(Member_info_kind& o, ISerializer& s);
inline void deserialize(Member_info_kind& o, IDeserializer& s);
inline RHash       hash(const Member_info_kind& o);
} //namespace rose

///////////////////////////////////////////////////////////////////
//  predef struct namespace_path
///////////////////////////////////////////////////////////////////
namespace rose {
inline bool equals(const namespace_path &lhs, const namespace_path &rhs);
inline bool operator==(const namespace_path &lhs, const namespace_path &rhs) { return equals(lhs, rhs); }
inline bool operator!=(const namespace_path &lhs, const namespace_path &rhs) { return !equals(lhs, rhs); }
inline void serialize(namespace_path &o, ISerializer &s);
inline void deserialize(namespace_path &o, IDeserializer &s);
inline RHash hash(const namespace_path &o);

template <>
struct type_id<namespace_path>;
template <>
inline const reflection::TypeInfo & reflection::get_type_info<namespace_path>();
} //namespace rose


///////////////////////////////////////////////////////////////////
//  predef struct member_info
///////////////////////////////////////////////////////////////////
namespace rose {
inline bool equals(const member_info &lhs, const member_info &rhs);
inline bool operator==(const member_info &lhs, const member_info &rhs) { return equals(lhs, rhs); }
inline bool operator!=(const member_info &lhs, const member_info &rhs) { return !equals(lhs, rhs); }
inline void serialize(member_info &o, ISerializer &s);
inline void deserialize(member_info &o, IDeserializer &s);
inline RHash hash(const member_info &o);

template <>
struct type_id<member_info>;
template <>
inline const reflection::TypeInfo & reflection::get_type_info<member_info>();
} //namespace rose


///////////////////////////////////////////////////////////////////
//  predef struct struct_info
///////////////////////////////////////////////////////////////////
namespace rose {
inline bool equals(const struct_info &lhs, const struct_info &rhs);
inline bool operator==(const struct_info &lhs, const struct_info &rhs) { return equals(lhs, rhs); }
inline bool operator!=(const struct_info &lhs, const struct_info &rhs) { return !equals(lhs, rhs); }
inline void serialize(struct_info &o, ISerializer &s);
inline void deserialize(struct_info &o, IDeserializer &s);
inline RHash hash(const struct_info &o);

template <>
struct type_id<struct_info>;
template <>
inline const reflection::TypeInfo & reflection::get_type_info<struct_info>();
} //namespace rose


///////////////////////////////////////////////////////////////////
//  predef struct enum_info
///////////////////////////////////////////////////////////////////
namespace rose {
inline bool equals(const enum_info &lhs, const enum_info &rhs);
inline bool operator==(const enum_info &lhs, const enum_info &rhs) { return equals(lhs, rhs); }
inline bool operator!=(const enum_info &lhs, const enum_info &rhs) { return !equals(lhs, rhs); }
inline void serialize(enum_info &o, ISerializer &s);
inline void deserialize(enum_info &o, IDeserializer &s);
inline RHash hash(const enum_info &o);

template <>
struct type_id<enum_info>;
template <>
inline const reflection::TypeInfo & reflection::get_type_info<enum_info>();
} //namespace rose


///////////////////////////////////////////////////////////////////
//  predef struct enum_class_info
///////////////////////////////////////////////////////////////////
namespace rose {
inline bool equals(const enum_class_info &lhs, const enum_class_info &rhs);
inline bool operator==(const enum_class_info &lhs, const enum_class_info &rhs) { return equals(lhs, rhs); }
inline bool operator!=(const enum_class_info &lhs, const enum_class_info &rhs) { return !equals(lhs, rhs); }
inline void serialize(enum_class_info &o, ISerializer &s);
inline void deserialize(enum_class_info &o, IDeserializer &s);
inline RHash hash(const enum_class_info &o);

template <>
struct type_id<enum_class_info>;
template <>
inline const reflection::TypeInfo & reflection::get_type_info<enum_class_info>();
} //namespace rose


///////////////////////////////////////////////////////////////////
//  predef struct function_parameter_info
///////////////////////////////////////////////////////////////////
namespace rose {
inline bool equals(const function_parameter_info &lhs, const function_parameter_info &rhs);
inline bool operator==(const function_parameter_info &lhs, const function_parameter_info &rhs) { return equals(lhs, rhs); }
inline bool operator!=(const function_parameter_info &lhs, const function_parameter_info &rhs) { return !equals(lhs, rhs); }
inline void serialize(function_parameter_info &o, ISerializer &s);
inline void deserialize(function_parameter_info &o, IDeserializer &s);
inline RHash hash(const function_parameter_info &o);

template <>
struct type_id<function_parameter_info>;
template <>
inline const reflection::TypeInfo & reflection::get_type_info<function_parameter_info>();
} //namespace rose


///////////////////////////////////////////////////////////////////
//  predef struct function_info
///////////////////////////////////////////////////////////////////
namespace rose {
inline bool equals(const function_info &lhs, const function_info &rhs);
inline bool operator==(const function_info &lhs, const function_info &rhs) { return equals(lhs, rhs); }
inline bool operator!=(const function_info &lhs, const function_info &rhs) { return !equals(lhs, rhs); }
inline void serialize(function_info &o, ISerializer &s);
inline void deserialize(function_info &o, IDeserializer &s);
inline RHash hash(const function_info &o);

template <>
struct type_id<function_info>;
template <>
inline const reflection::TypeInfo & reflection::get_type_info<function_info>();
} //namespace rose


///////////////////////////////////////////////////////////////////
//  predef struct ParseContext
///////////////////////////////////////////////////////////////////
namespace rose {
inline bool equals(const ParseContext &lhs, const ParseContext &rhs);
inline bool operator==(const ParseContext &lhs, const ParseContext &rhs) { return equals(lhs, rhs); }
inline bool operator!=(const ParseContext &lhs, const ParseContext &rhs) { return !equals(lhs, rhs); }
inline void serialize(ParseContext &o, ISerializer &s);
inline void deserialize(ParseContext &o, IDeserializer &s);
inline RHash hash(const ParseContext &o);

template <>
struct type_id<ParseContext>;
template <>
inline const reflection::TypeInfo & reflection::get_type_info<ParseContext>();
} //namespace rose



#ifndef IMPL_SERIALIZER_UTIL
#define IMPL_SERIALIZER_UTIL

///////////////////////////////////////////////////////////////////
// internal helper methods
///////////////////////////////////////////////////////////////////

namespace rose {
template<class T>
bool rose_parser_equals(const T& lhs, const T& rhs) {
  return lhs == rhs;
}

template<class T, size_t N>
bool rose_parser_equals(const T(&lhs)[N], const T(&rhs)[N]) {
  for (size_t i = 0; i != N; ++i) {
    if (!rose_parser_equals(lhs, rhs)) return false;
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
    if (!rose_parser_equals(lhs, rhs)) return false;
  }
  return true;
}

template<class T>
RHash rose_parser_hash(const T & value) { return hash(value); }

template<class T>
RHash rose_parser_hash(const std::vector<T>& v) {
  RHash h = 0;
  for (const auto& o : v) {
    h ^= rose_parser_hash(o);
    h = xor64(h);
  }
  return h;
}

}
#endif
  
///////////////////////////////////////////////////////////////////
//  impl enum member_annotations_t
///////////////////////////////////////////////////////////////////
inline const char * rose::to_string(const member_annotations_t & e) {
    switch(e) {
        case member_annotations_t::NONE: return "NONE";
        case member_annotations_t::Ignore: return "Ignore";
        case member_annotations_t::String: return "String";
        case member_annotations_t::Data: return "Data";
        default: return "<UNKNOWN>";
    }
}
inline void rose::serialize(member_annotations_t& o, ISerializer& s) {
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
inline void rose::deserialize(member_annotations_t& o, IDeserializer& s) {
  char str[64];
  deserialize(str, s);
  RHash h = rose::hash(str);
  switch (h) {
  case rose::hash("NONE"): o = member_annotations_t::NONE; break;
  case rose::hash("Ignore"): o = member_annotations_t::Ignore; break;
  case rose::hash("String"): o = member_annotations_t::String; break;
  case rose::hash("Data"): o = member_annotations_t::Data; break;
  default: /*unknown value*/ break;
  }
}
inline RHash rose::hash(const member_annotations_t& o) {
  return static_cast<RHash>(o);
}

///////////////////////////////////////////////////////////////////
//  impl enum value_type_t
///////////////////////////////////////////////////////////////////
inline const char * rose::to_string(const value_type_t & e) {
    switch(e) {
        case value_type_t::Increment: return "Increment";
        case value_type_t::Set: return "Set";
        default: return "<UNKNOWN>";
    }
}
inline void rose::serialize(value_type_t& o, ISerializer& s) {
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
inline void rose::deserialize(value_type_t& o, IDeserializer& s) {
  char str[64];
  deserialize(str, s);
  RHash h = rose::hash(str);
  switch (h) {
  case rose::hash("Increment"): o = value_type_t::Increment; break;
  case rose::hash("Set"): o = value_type_t::Set; break;
  default: /*unknown value*/ break;
  }
}
inline RHash rose::hash(const value_type_t& o) {
  return static_cast<RHash>(o);
}

///////////////////////////////////////////////////////////////////
//  impl enum global_annotations_t
///////////////////////////////////////////////////////////////////
inline const char * rose::to_string(const global_annotations_t & e) {
    switch(e) {
        case global_annotations_t::NONE: return "NONE";
        case global_annotations_t::Flag: return "Flag";
        case global_annotations_t::Imposter: return "Imposter";
        default: return "<UNKNOWN>";
    }
}
inline void rose::serialize(global_annotations_t& o, ISerializer& s) {
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
inline void rose::deserialize(global_annotations_t& o, IDeserializer& s) {
  char str[64];
  deserialize(str, s);
  RHash h = rose::hash(str);
  switch (h) {
  case rose::hash("NONE"): o = global_annotations_t::NONE; break;
  case rose::hash("Flag"): o = global_annotations_t::Flag; break;
  case rose::hash("Imposter"): o = global_annotations_t::Imposter; break;
  default: /*unknown value*/ break;
  }
}
inline RHash rose::hash(const global_annotations_t& o) {
  return static_cast<RHash>(o);
}

///////////////////////////////////////////////////////////////////
//  impl enum Member_info_kind
///////////////////////////////////////////////////////////////////
inline const char * rose::to_string(const Member_info_kind & e) {
    switch(e) {
        case Member_info_kind::NONE: return "NONE";
        case Member_info_kind::Field: return "Field";
        case Member_info_kind::Function: return "Function";
        case Member_info_kind::Constructor: return "Constructor";
        case Member_info_kind::Destructor: return "Destructor";
        default: return "<UNKNOWN>";
    }
}
inline void rose::serialize(Member_info_kind& o, ISerializer& s) {
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
    case Member_info_kind::Constructor: {
      char str[] = "Constructor";
      serialize(str, s);
      break;
    }
    case Member_info_kind::Destructor: {
      char str[] = "Destructor";
      serialize(str, s);
      break;
    }
    default: /* unknown */ break;
  }
}
inline void rose::deserialize(Member_info_kind& o, IDeserializer& s) {
  char str[64];
  deserialize(str, s);
  RHash h = rose::hash(str);
  switch (h) {
  case rose::hash("NONE"): o = Member_info_kind::NONE; break;
  case rose::hash("Field"): o = Member_info_kind::Field; break;
  case rose::hash("Function"): o = Member_info_kind::Function; break;
  case rose::hash("Constructor"): o = Member_info_kind::Constructor; break;
  case rose::hash("Destructor"): o = Member_info_kind::Destructor; break;
  default: /*unknown value*/ break;
  }
}
inline RHash rose::hash(const Member_info_kind& o) {
  return static_cast<RHash>(o);
}

///////////////////////////////////////////////////////////////////
//  impl struct namespace_path
///////////////////////////////////////////////////////////////////
inline bool rose::equals(const namespace_path &lhs, const namespace_path &rhs) {
  return
    rose::rose_parser_equals(lhs.path, rhs.path);
}

inline void rose::serialize(namespace_path &o, ISerializer &s) {
  if(s.node_begin("namespace_path", hash("namespace_path"), &o)) {
    s.key("path");
    serialize(o.path, s, std::strlen(o.path));
    s.node_end();
  }
  s.end();
}

inline void rose::deserialize(namespace_path &o, IDeserializer &s) {
  while (s.next_key()) {
    switch (s.hash_key()) {
      case rose::hash("path"):
        deserialize(o.path, s);
        break;
      default: s.skip_key(); break;
    }
  }
}

inline RHash rose::hash(const namespace_path &o) {
  RHash h = 0;
  h ^= rose::rose_parser_hash(o.path);
  return h;
}

template <>
struct rose::type_id<namespace_path> {
    inline static RHash VALUE = 12258869517490701093ULL;
};

template <>
inline const rose::reflection::TypeInfo & rose::reflection::get_type_info<namespace_path>() {
  static rose::reflection::TypeInfo info = {
    /*             unique_id */ rose::hash("namespace_path"),
    /*           member_hash */ 12258869517490701093ULL,
    /*      memory_footprint */ sizeof(namespace_path),
    /*      memory_alignment */ 16,
    /*                  name */ "namespace_path",
    /*  fp_default_construct */ +[](void * ptr) { new (ptr) namespace_path(); },
    /*   fp_default_destruct */ +[](void * ptr) { std::launder(reinterpret_cast<namespace_path*>(ptr))->~namespace_path(); },
    /*          fp_serialize */ +[](void * ptr, ISerializer & s) { ::rose::serialize(*std::launder(reinterpret_cast<namespace_path*>(ptr)), s); },
    /*        fp_deserialize */ +[](void * ptr, IDeserializer & d) { ::rose::deserialize(*std::launder(reinterpret_cast<namespace_path*>(ptr)), d); }
  };
  return info;
}

///////////////////////////////////////////////////////////////////
//  impl struct member_info
///////////////////////////////////////////////////////////////////
inline bool rose::equals(const member_info &lhs, const member_info &rhs) {
  return
    rose::rose_parser_equals(lhs.kind, rhs.kind) &&
    rose::rose_parser_equals(lhs.type, rhs.type) &&
    rose::rose_parser_equals(lhs.name, rhs.name) &&
    rose::rose_parser_equals(lhs.default_value, rhs.default_value) &&
    rose::rose_parser_equals(lhs.count, rhs.count) &&
    rose::rose_parser_equals(lhs.annotations, rhs.annotations);
}

inline void rose::serialize(member_info &o, ISerializer &s) {
  if(s.node_begin("member_info", hash("member_info"), &o)) {
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

inline void rose::deserialize(member_info &o, IDeserializer &s) {
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

inline RHash rose::hash(const member_info &o) {
  RHash h = 0;
  h ^= rose::rose_parser_hash(o.kind);
  h = rose::xor64(h);
  h ^= rose::rose_parser_hash(o.type);
  h = rose::xor64(h);
  h ^= rose::rose_parser_hash(o.name);
  h = rose::xor64(h);
  h ^= rose::rose_parser_hash(o.default_value);
  h = rose::xor64(h);
  h ^= rose::rose_parser_hash(o.count);
  h = rose::xor64(h);
  h ^= rose::rose_parser_hash(o.annotations);
  return h;
}

template <>
struct rose::type_id<member_info> {
    inline static RHash VALUE = 11323069267460255306ULL;
};

template <>
inline const rose::reflection::TypeInfo & rose::reflection::get_type_info<member_info>() {
  static rose::reflection::TypeInfo info = {
    /*             unique_id */ rose::hash("member_info"),
    /*           member_hash */ 11323069267460255306ULL,
    /*      memory_footprint */ sizeof(member_info),
    /*      memory_alignment */ 16,
    /*                  name */ "member_info",
    /*  fp_default_construct */ +[](void * ptr) { new (ptr) member_info(); },
    /*   fp_default_destruct */ +[](void * ptr) { std::launder(reinterpret_cast<member_info*>(ptr))->~member_info(); },
    /*          fp_serialize */ +[](void * ptr, ISerializer & s) { ::rose::serialize(*std::launder(reinterpret_cast<member_info*>(ptr)), s); },
    /*        fp_deserialize */ +[](void * ptr, IDeserializer & d) { ::rose::deserialize(*std::launder(reinterpret_cast<member_info*>(ptr)), d); }
  };
  return info;
}

///////////////////////////////////////////////////////////////////
//  impl struct struct_info
///////////////////////////////////////////////////////////////////
inline bool rose::equals(const struct_info &lhs, const struct_info &rhs) {
  return
    rose::rose_parser_equals(lhs.name_withns, rhs.name_withns) &&
    rose::rose_parser_equals(lhs.name_withoutns, rhs.name_withoutns) &&
    rose::rose_parser_equals(lhs.namespaces, rhs.namespaces) &&
    rose::rose_parser_equals(lhs.global_annotations, rhs.global_annotations) &&
    rose::rose_parser_equals(lhs.members, rhs.members);
}

inline void rose::serialize(struct_info &o, ISerializer &s) {
  if(s.node_begin("struct_info", hash("struct_info"), &o)) {
    s.key("name_withns");
    serialize(o.name_withns, s, std::strlen(o.name_withns));
    s.key("name_withoutns");
    serialize(o.name_withoutns, s, std::strlen(o.name_withoutns));
    s.key("namespaces");
    serialize(o.namespaces, s);
    s.key("global_annotations");
    serialize(o.global_annotations, s);
    s.key("members");
    serialize(o.members, s);
    s.node_end();
  }
  s.end();
}

inline void rose::deserialize(struct_info &o, IDeserializer &s) {
  while (s.next_key()) {
    switch (s.hash_key()) {
      case rose::hash("name_withns"):
        deserialize(o.name_withns, s);
        break;
      case rose::hash("name_withoutns"):
        deserialize(o.name_withoutns, s);
        break;
      case rose::hash("namespaces"):
        deserialize(o.namespaces, s);
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

inline RHash rose::hash(const struct_info &o) {
  RHash h = 0;
  h ^= rose::rose_parser_hash(o.name_withns);
  h = rose::xor64(h);
  h ^= rose::rose_parser_hash(o.name_withoutns);
  h = rose::xor64(h);
  h ^= rose::rose_parser_hash(o.namespaces);
  h = rose::xor64(h);
  h ^= rose::rose_parser_hash(o.global_annotations);
  h = rose::xor64(h);
  h ^= rose::rose_parser_hash(o.members);
  return h;
}

template <>
struct rose::type_id<struct_info> {
    inline static RHash VALUE = 2652356125487541418ULL;
};

template <>
inline const rose::reflection::TypeInfo & rose::reflection::get_type_info<struct_info>() {
  static rose::reflection::TypeInfo info = {
    /*             unique_id */ rose::hash("struct_info"),
    /*           member_hash */ 2652356125487541418ULL,
    /*      memory_footprint */ sizeof(struct_info),
    /*      memory_alignment */ 16,
    /*                  name */ "struct_info",
    /*  fp_default_construct */ +[](void * ptr) { new (ptr) struct_info(); },
    /*   fp_default_destruct */ +[](void * ptr) { std::launder(reinterpret_cast<struct_info*>(ptr))->~struct_info(); },
    /*          fp_serialize */ +[](void * ptr, ISerializer & s) { ::rose::serialize(*std::launder(reinterpret_cast<struct_info*>(ptr)), s); },
    /*        fp_deserialize */ +[](void * ptr, IDeserializer & d) { ::rose::deserialize(*std::launder(reinterpret_cast<struct_info*>(ptr)), d); }
  };
  return info;
}

///////////////////////////////////////////////////////////////////
//  impl struct enum_info
///////////////////////////////////////////////////////////////////
inline bool rose::equals(const enum_info &lhs, const enum_info &rhs) {
  return
    rose::rose_parser_equals(lhs.name, rhs.name) &&
    rose::rose_parser_equals(lhs.value, rhs.value) &&
    rose::rose_parser_equals(lhs.value_type, rhs.value_type);
}

inline void rose::serialize(enum_info &o, ISerializer &s) {
  if(s.node_begin("enum_info", hash("enum_info"), &o)) {
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

inline void rose::deserialize(enum_info &o, IDeserializer &s) {
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

inline RHash rose::hash(const enum_info &o) {
  RHash h = 0;
  h ^= rose::rose_parser_hash(o.name);
  h = rose::xor64(h);
  h ^= rose::rose_parser_hash(o.value);
  h = rose::xor64(h);
  h ^= rose::rose_parser_hash(o.value_type);
  return h;
}

template <>
struct rose::type_id<enum_info> {
    inline static RHash VALUE = 9578114829779115887ULL;
};

template <>
inline const rose::reflection::TypeInfo & rose::reflection::get_type_info<enum_info>() {
  static rose::reflection::TypeInfo info = {
    /*             unique_id */ rose::hash("enum_info"),
    /*           member_hash */ 9578114829779115887ULL,
    /*      memory_footprint */ sizeof(enum_info),
    /*      memory_alignment */ 16,
    /*                  name */ "enum_info",
    /*  fp_default_construct */ +[](void * ptr) { new (ptr) enum_info(); },
    /*   fp_default_destruct */ +[](void * ptr) { std::launder(reinterpret_cast<enum_info*>(ptr))->~enum_info(); },
    /*          fp_serialize */ +[](void * ptr, ISerializer & s) { ::rose::serialize(*std::launder(reinterpret_cast<enum_info*>(ptr)), s); },
    /*        fp_deserialize */ +[](void * ptr, IDeserializer & d) { ::rose::deserialize(*std::launder(reinterpret_cast<enum_info*>(ptr)), d); }
  };
  return info;
}

///////////////////////////////////////////////////////////////////
//  impl struct enum_class_info
///////////////////////////////////////////////////////////////////
inline bool rose::equals(const enum_class_info &lhs, const enum_class_info &rhs) {
  return
    rose::rose_parser_equals(lhs.name_withns, rhs.name_withns) &&
    rose::rose_parser_equals(lhs.name_withoutns, rhs.name_withoutns) &&
    rose::rose_parser_equals(lhs.type, rhs.type) &&
    rose::rose_parser_equals(lhs.custom_type, rhs.custom_type) &&
    rose::rose_parser_equals(lhs.enums, rhs.enums) &&
    rose::rose_parser_equals(lhs.namespaces, rhs.namespaces) &&
    rose::rose_parser_equals(lhs.default_value, rhs.default_value) &&
    rose::rose_parser_equals(lhs.enum_annotations, rhs.enum_annotations);
}

inline void rose::serialize(enum_class_info &o, ISerializer &s) {
  if(s.node_begin("enum_class_info", hash("enum_class_info"), &o)) {
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

inline void rose::deserialize(enum_class_info &o, IDeserializer &s) {
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

inline RHash rose::hash(const enum_class_info &o) {
  RHash h = 0;
  h ^= rose::rose_parser_hash(o.name_withns);
  h = rose::xor64(h);
  h ^= rose::rose_parser_hash(o.name_withoutns);
  h = rose::xor64(h);
  h ^= rose::rose_parser_hash(o.type);
  h = rose::xor64(h);
  h ^= rose::rose_parser_hash(o.custom_type);
  h = rose::xor64(h);
  h ^= rose::rose_parser_hash(o.enums);
  h = rose::xor64(h);
  h ^= rose::rose_parser_hash(o.namespaces);
  h = rose::xor64(h);
  h ^= rose::rose_parser_hash(o.default_value);
  h = rose::xor64(h);
  h ^= rose::rose_parser_hash(o.enum_annotations);
  return h;
}

template <>
struct rose::type_id<enum_class_info> {
    inline static RHash VALUE = 15820409074394059996ULL;
};

template <>
inline const rose::reflection::TypeInfo & rose::reflection::get_type_info<enum_class_info>() {
  static rose::reflection::TypeInfo info = {
    /*             unique_id */ rose::hash("enum_class_info"),
    /*           member_hash */ 15820409074394059996ULL,
    /*      memory_footprint */ sizeof(enum_class_info),
    /*      memory_alignment */ 16,
    /*                  name */ "enum_class_info",
    /*  fp_default_construct */ +[](void * ptr) { new (ptr) enum_class_info(); },
    /*   fp_default_destruct */ +[](void * ptr) { std::launder(reinterpret_cast<enum_class_info*>(ptr))->~enum_class_info(); },
    /*          fp_serialize */ +[](void * ptr, ISerializer & s) { ::rose::serialize(*std::launder(reinterpret_cast<enum_class_info*>(ptr)), s); },
    /*        fp_deserialize */ +[](void * ptr, IDeserializer & d) { ::rose::deserialize(*std::launder(reinterpret_cast<enum_class_info*>(ptr)), d); }
  };
  return info;
}

///////////////////////////////////////////////////////////////////
//  impl struct function_parameter_info
///////////////////////////////////////////////////////////////////
inline bool rose::equals(const function_parameter_info &lhs, const function_parameter_info &rhs) {
  return
    rose::rose_parser_equals(lhs.name, rhs.name) &&
    rose::rose_parser_equals(lhs.type, rhs.type) &&
    rose::rose_parser_equals(lhs.modifier, rhs.modifier) &&
    rose::rose_parser_equals(lhs.is_const, rhs.is_const);
}

inline void rose::serialize(function_parameter_info &o, ISerializer &s) {
  if(s.node_begin("function_parameter_info", hash("function_parameter_info"), &o)) {
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

inline void rose::deserialize(function_parameter_info &o, IDeserializer &s) {
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

inline RHash rose::hash(const function_parameter_info &o) {
  RHash h = 0;
  h ^= rose::rose_parser_hash(o.name);
  h = rose::xor64(h);
  h ^= rose::rose_parser_hash(o.type);
  h = rose::xor64(h);
  h ^= rose::rose_parser_hash(o.modifier);
  h = rose::xor64(h);
  h ^= rose::rose_parser_hash(o.is_const);
  return h;
}

template <>
struct rose::type_id<function_parameter_info> {
    inline static RHash VALUE = 9370255687959554376ULL;
};

template <>
inline const rose::reflection::TypeInfo & rose::reflection::get_type_info<function_parameter_info>() {
  static rose::reflection::TypeInfo info = {
    /*             unique_id */ rose::hash("function_parameter_info"),
    /*           member_hash */ 9370255687959554376ULL,
    /*      memory_footprint */ sizeof(function_parameter_info),
    /*      memory_alignment */ 16,
    /*                  name */ "function_parameter_info",
    /*  fp_default_construct */ +[](void * ptr) { new (ptr) function_parameter_info(); },
    /*   fp_default_destruct */ +[](void * ptr) { std::launder(reinterpret_cast<function_parameter_info*>(ptr))->~function_parameter_info(); },
    /*          fp_serialize */ +[](void * ptr, ISerializer & s) { ::rose::serialize(*std::launder(reinterpret_cast<function_parameter_info*>(ptr)), s); },
    /*        fp_deserialize */ +[](void * ptr, IDeserializer & d) { ::rose::deserialize(*std::launder(reinterpret_cast<function_parameter_info*>(ptr)), d); }
  };
  return info;
}

///////////////////////////////////////////////////////////////////
//  impl struct function_info
///////////////////////////////////////////////////////////////////
inline bool rose::equals(const function_info &lhs, const function_info &rhs) {
  return
    rose::rose_parser_equals(lhs.name, rhs.name) &&
    rose::rose_parser_equals(lhs.type, rhs.type) &&
    rose::rose_parser_equals(lhs.parameters, rhs.parameters);
}

inline void rose::serialize(function_info &o, ISerializer &s) {
  if(s.node_begin("function_info", hash("function_info"), &o)) {
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

inline void rose::deserialize(function_info &o, IDeserializer &s) {
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

inline RHash rose::hash(const function_info &o) {
  RHash h = 0;
  h ^= rose::rose_parser_hash(o.name);
  h = rose::xor64(h);
  h ^= rose::rose_parser_hash(o.type);
  h = rose::xor64(h);
  h ^= rose::rose_parser_hash(o.parameters);
  return h;
}

template <>
struct rose::type_id<function_info> {
    inline static RHash VALUE = 5216781949972949934ULL;
};

template <>
inline const rose::reflection::TypeInfo & rose::reflection::get_type_info<function_info>() {
  static rose::reflection::TypeInfo info = {
    /*             unique_id */ rose::hash("function_info"),
    /*           member_hash */ 5216781949972949934ULL,
    /*      memory_footprint */ sizeof(function_info),
    /*      memory_alignment */ 16,
    /*                  name */ "function_info",
    /*  fp_default_construct */ +[](void * ptr) { new (ptr) function_info(); },
    /*   fp_default_destruct */ +[](void * ptr) { std::launder(reinterpret_cast<function_info*>(ptr))->~function_info(); },
    /*          fp_serialize */ +[](void * ptr, ISerializer & s) { ::rose::serialize(*std::launder(reinterpret_cast<function_info*>(ptr)), s); },
    /*        fp_deserialize */ +[](void * ptr, IDeserializer & d) { ::rose::deserialize(*std::launder(reinterpret_cast<function_info*>(ptr)), d); }
  };
  return info;
}

///////////////////////////////////////////////////////////////////
//  impl struct ParseContext
///////////////////////////////////////////////////////////////////
inline bool rose::equals(const ParseContext &lhs, const ParseContext &rhs) {
  return
    rose::rose_parser_equals(lhs.enum_classes, rhs.enum_classes) &&
    rose::rose_parser_equals(lhs.functions, rhs.functions) &&
    rose::rose_parser_equals(lhs.structs, rhs.structs);
}

inline void rose::serialize(ParseContext &o, ISerializer &s) {
  if(s.node_begin("ParseContext", hash("ParseContext"), &o)) {
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

inline void rose::deserialize(ParseContext &o, IDeserializer &s) {
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

inline RHash rose::hash(const ParseContext &o) {
  RHash h = 0;
  h ^= rose::rose_parser_hash(o.enum_classes);
  h = rose::xor64(h);
  h ^= rose::rose_parser_hash(o.functions);
  h = rose::xor64(h);
  h ^= rose::rose_parser_hash(o.structs);
  return h;
}

template <>
struct rose::type_id<ParseContext> {
    inline static RHash VALUE = 4083862798227823235ULL;
};

template <>
inline const rose::reflection::TypeInfo & rose::reflection::get_type_info<ParseContext>() {
  static rose::reflection::TypeInfo info = {
    /*             unique_id */ rose::hash("ParseContext"),
    /*           member_hash */ 4083862798227823235ULL,
    /*      memory_footprint */ sizeof(ParseContext),
    /*      memory_alignment */ 16,
    /*                  name */ "ParseContext",
    /*  fp_default_construct */ +[](void * ptr) { new (ptr) ParseContext(); },
    /*   fp_default_destruct */ +[](void * ptr) { std::launder(reinterpret_cast<ParseContext*>(ptr))->~ParseContext(); },
    /*          fp_serialize */ +[](void * ptr, ISerializer & s) { ::rose::serialize(*std::launder(reinterpret_cast<ParseContext*>(ptr)), s); },
    /*        fp_deserialize */ +[](void * ptr, IDeserializer & d) { ::rose::deserialize(*std::launder(reinterpret_cast<ParseContext*>(ptr)), d); }
  };
  return info;
}

