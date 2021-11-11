#pragma once

#include <rose/hash.h>
#include <serializer/serializer.h>

///////////////////////////////////////////////////////////////////
//  AUTOGEN                                                      //
//  command:
//    rose.parser --include camera.h -O camera_serilizer.h -J camera.json
///////////////////////////////////////////////////////////////////

enum class                   enum_test : long long ;
const char * to_string(const enum_test &);
namespace rose {
  namespace ecs {
    void      deserialize(enum_test &o, IDeserializer &s);
    void        serialize(enum_test &o, ISerializer &s);
  }
  hash_value       hash(const enum_test &o);
}


enum class                   enum_test2;
const char * to_string(const enum_test2 &);
namespace rose {
  namespace ecs {
    void      deserialize(enum_test2 &o, IDeserializer &s);
    void        serialize(enum_test2 &o, ISerializer &s);
  }
  hash_value       hash(const enum_test2 &o);
}


struct                vector3;
namespace rose {
  namespace ecs {
    bool operator==(const vector3 &lhs, const vector3 &rhs);
    bool operator!=(const vector3 &lhs, const vector3 &rhs);
    void      deserialize(vector3 &o, IDeserializer &s);
    void        serialize(vector3 &o, ISerializer &s);
  }
  hash_value       hash(const vector3 &o);
}


struct                Camera;
namespace rose {
  namespace ecs {
    bool operator==(const Camera &lhs, const Camera &rhs);
    bool operator!=(const Camera &lhs, const Camera &rhs);
    void      deserialize(Camera &o, IDeserializer &s);
    void        serialize(Camera &o, ISerializer &s);
  }
  hash_value       hash(const Camera &o);
}


struct                Transform;
namespace rose {
  namespace ecs {
    bool operator==(const Transform &lhs, const Transform &rhs);
    bool operator!=(const Transform &lhs, const Transform &rhs);
    void      deserialize(Transform &o, IDeserializer &s);
    void        serialize(Transform &o, ISerializer &s);
  }
  hash_value       hash(const Transform &o);
}


struct                Scene1;
namespace rose {
  namespace ecs {
    bool operator==(const Scene1 &lhs, const Scene1 &rhs);
    bool operator!=(const Scene1 &lhs, const Scene1 &rhs);
    void      deserialize(Scene1 &o, IDeserializer &s);
    void        serialize(Scene1 &o, ISerializer &s);
  }
  hash_value       hash(const Scene1 &o);
}


#ifdef IMPL_SERIALIZER

const char * to_string(const enum_test & e) {
    switch(e) {
        case enum_test::NONE: return "NONE";
        case enum_test::ONE: return "ONE";
        case enum_test::TWO: return "TWO";
        case enum_test::SIXTEEN: return "SIXTEEN";
        case enum_test::FOURTYTWO: return "FOURTYTWO";
        case enum_test::INVALID: return "INVALID";
        default: return "<UNKNOWN>";
    }
}
void rose::ecs::serialize(enum_test& o, ISerializer& s) {
  switch (o) {
    case enum_test::NONE: {
      char str[] = "NONE";
      serialize(str, s);
      break;
    }
    case enum_test::ONE: {
      char str[] = "ONE";
      serialize(str, s);
      break;
    }
    case enum_test::TWO: {
      char str[] = "TWO";
      serialize(str, s);
      break;
    }
    case enum_test::SIXTEEN: {
      char str[] = "SIXTEEN";
      serialize(str, s);
      break;
    }
    case enum_test::FOURTYTWO: {
      char str[] = "FOURTYTWO";
      serialize(str, s);
      break;
    }
    case enum_test::INVALID: {
      char str[] = "INVALID";
      serialize(str, s);
      break;
    }
    default: /* unknown */ break;
  }
}
void rose::ecs::deserialize(enum_test& o, IDeserializer& s) {
  char str[64];
  deserialize(str, s);
  rose::hash_value h = rose::hash(str);
  switch (h) {
  case rose::hash("NONE"): o = enum_test::NONE; break;
  case rose::hash("ONE"): o = enum_test::ONE; break;
  case rose::hash("TWO"): o = enum_test::TWO; break;
  case rose::hash("SIXTEEN"): o = enum_test::SIXTEEN; break;
  case rose::hash("FOURTYTWO"): o = enum_test::FOURTYTWO; break;
  case rose::hash("INVALID"): o = enum_test::INVALID; break;
  default: /*unknown value*/ break;
  }
}
rose::hash_value       rose::hash(const enum_test& o) {
  return static_cast<rose::hash_value>(o);
}

const char * to_string(const enum_test2 & e) {
    switch(e) {
        case enum_test2::NONE: return "NONE";
        case enum_test2::ONE: return "ONE";
        case enum_test2::TWO: return "TWO";
        case enum_test2::SIXTEEN: return "SIXTEEN";
        case enum_test2::FOURTYTWO: return "FOURTYTWO";
        case enum_test2::INVALID: return "INVALID";
        default: return "<UNKNOWN>";
    }
}
void rose::ecs::serialize(enum_test2& o, ISerializer& s) {
  switch (o) {
    case enum_test2::NONE: {
      char str[] = "NONE";
      serialize(str, s);
      break;
    }
    case enum_test2::ONE: {
      char str[] = "ONE";
      serialize(str, s);
      break;
    }
    case enum_test2::TWO: {
      char str[] = "TWO";
      serialize(str, s);
      break;
    }
    case enum_test2::SIXTEEN: {
      char str[] = "SIXTEEN";
      serialize(str, s);
      break;
    }
    case enum_test2::FOURTYTWO: {
      char str[] = "FOURTYTWO";
      serialize(str, s);
      break;
    }
    case enum_test2::INVALID: {
      char str[] = "INVALID";
      serialize(str, s);
      break;
    }
    default: /* unknown */ break;
  }
}
void rose::ecs::deserialize(enum_test2& o, IDeserializer& s) {
  char str[64];
  deserialize(str, s);
  rose::hash_value h = rose::hash(str);
  switch (h) {
  case rose::hash("NONE"): o = enum_test2::NONE; break;
  case rose::hash("ONE"): o = enum_test2::ONE; break;
  case rose::hash("TWO"): o = enum_test2::TWO; break;
  case rose::hash("SIXTEEN"): o = enum_test2::SIXTEEN; break;
  case rose::hash("FOURTYTWO"): o = enum_test2::FOURTYTWO; break;
  case rose::hash("INVALID"): o = enum_test2::INVALID; break;
  default: /*unknown value*/ break;
  }
}
rose::hash_value       rose::hash(const enum_test2& o) {
  return static_cast<rose::hash_value>(o);
}

///////////////////////////////////////////////////////////////////
//  struct vector3
///////////////////////////////////////////////////////////////////
bool operator==(const vector3 &lhs, const vector3 &rhs) {
  return
    lhs.x == rhs.x &&
    lhs.y == rhs.y &&
    lhs.z == rhs.z;
}

bool operator!=(const vector3 &lhs, const vector3 &rhs) {
  return
    lhs.x != rhs.x ||
    lhs.y != rhs.y ||
    lhs.z != rhs.z;
}

void rose::ecs::serialize(vector3 &o, ISerializer &s) {
  if(s.node_begin("vector3", rose::hash("vector3"), &o)) {
    s.key("x");
    serialize(o.x, s);
    s.key("y");
    serialize(o.y, s);
    s.key("z");
    serialize(o.z, s);
    s.node_end();
  }
  s.end();
}

void rose::ecs::deserialize(vector3 &o, IDeserializer &s) {
  //TODO: implement me
  //construct_defaults(o);

  while (s.next_key()) {
    switch (s.hash_key()) {
      case rose::hash("x"):
        deserialize(o.x, s);
        break;
      case rose::hash("y"):
        deserialize(o.y, s);
        break;
      case rose::hash("z"):
        deserialize(o.z, s);
        break;
      default: s.skip_key(); break;
    }
  }
}

rose::hash_value rose::hash(const vector3 &o) {
  rose::hash_value h = 0;
  h ^= rose::hash(o.x);
  h = rose::xor64(h);
  h ^= rose::hash(o.y);
  h = rose::xor64(h);
  h ^= rose::hash(o.z);
  h = rose::xor64(h);
  return h;
}
///////////////////////////////////////////////////////////////////
//  struct Camera
///////////////////////////////////////////////////////////////////
bool operator==(const Camera &lhs, const Camera &rhs) {
  return
    lhs.x == rhs.x &&
    lhs.y == rhs.y &&
    lhs.z == rhs.z;
}

bool operator!=(const Camera &lhs, const Camera &rhs) {
  return
    lhs.x != rhs.x ||
    lhs.y != rhs.y ||
    lhs.z != rhs.z;
}

void rose::ecs::serialize(Camera &o, ISerializer &s) {
  if(s.node_begin("Camera", rose::hash("Camera"), &o)) {
    s.key("x");
    serialize(o.x, s);
    s.key("y");
    serialize(o.y, s);
    s.key("z");
    serialize(o.z, s);
    s.node_end();
  }
  s.end();
}

void rose::ecs::deserialize(Camera &o, IDeserializer &s) {
  //TODO: implement me
  //construct_defaults(o);

  while (s.next_key()) {
    switch (s.hash_key()) {
      case rose::hash("x"):
        deserialize(o.x, s);
        break;
      case rose::hash("y"):
        deserialize(o.y, s);
        break;
      case rose::hash("z"):
        deserialize(o.z, s);
        break;
      default: s.skip_key(); break;
    }
  }
}

rose::hash_value rose::hash(const Camera &o) {
  rose::hash_value h = 0;
  h ^= rose::hash(o.x);
  h = rose::xor64(h);
  h ^= rose::hash(o.y);
  h = rose::xor64(h);
  h ^= rose::hash(o.z);
  h = rose::xor64(h);
  return h;
}
///////////////////////////////////////////////////////////////////
//  struct Transform
///////////////////////////////////////////////////////////////////
bool operator==(const Transform &lhs, const Transform &rhs) {
  return
    lhs.camera == rhs.camera &&
    lhs.position == rhs.position;
}

bool operator!=(const Transform &lhs, const Transform &rhs) {
  return
    lhs.camera != rhs.camera ||
    lhs.position != rhs.position;
}

void rose::ecs::serialize(Transform &o, ISerializer &s) {
  if(s.node_begin("Transform", rose::hash("Transform"), &o)) {
    s.key("camera");
    serialize(o.camera, s);
    s.key("position");
    serialize(o.position, s);
    s.node_end();
  }
  s.end();
}

void rose::ecs::deserialize(Transform &o, IDeserializer &s) {
  //TODO: implement me
  //construct_defaults(o);

  while (s.next_key()) {
    switch (s.hash_key()) {
      case rose::hash("camera"):
        deserialize(o.camera, s);
        break;
      case rose::hash("position"):
        deserialize(o.position, s);
        break;
      default: s.skip_key(); break;
    }
  }
}

rose::hash_value rose::hash(const Transform &o) {
  rose::hash_value h = 0;
  h ^= rose::hash(o.camera);
  h = rose::xor64(h);
  h ^= rose::hash(o.position);
  h = rose::xor64(h);
  return h;
}
///////////////////////////////////////////////////////////////////
//  struct Scene1
///////////////////////////////////////////////////////////////////
bool operator==(const Scene1 &lhs, const Scene1 &rhs) {
  return
    lhs.cameras == rhs.cameras;
}

bool operator!=(const Scene1 &lhs, const Scene1 &rhs) {
  return
    lhs.cameras != rhs.cameras;
}

void rose::ecs::serialize(Scene1 &o, ISerializer &s) {
  if(s.node_begin("Scene1", rose::hash("Scene1"), &o)) {
    s.key("cameras");
    serialize(o.cameras, s);
    s.node_end();
  }
  s.end();
}

void rose::ecs::deserialize(Scene1 &o, IDeserializer &s) {
  //TODO: implement me
  //construct_defaults(o);

  while (s.next_key()) {
    switch (s.hash_key()) {
      case rose::hash("cameras"):
        deserialize(o.cameras, s);
        break;
      default: s.skip_key(); break;
    }
  }
}

rose::hash_value rose::hash(const Scene1 &o) {
  rose::hash_value h = 0;
  h ^= rose::hash(o.cameras);
  h = rose::xor64(h);
  return h;
}

#endif
