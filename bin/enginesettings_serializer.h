#pragma once

#include <rose/hash.h>
#include <serializer/serializer.h>

///////////////////////////////////////////////////////////////////
//  AUTOGEN                                                      //
//  command:
//    rose.parser --include enginesettings.h -O enginesettings_serializer.h -J enginesettings.json -V
///////////////////////////////////////////////////////////////////

struct                EngineSettings;
namespace rose {
  namespace ecs {
    bool operator==(const EngineSettings &lhs, const EngineSettings &rhs);
    bool operator!=(const EngineSettings &lhs, const EngineSettings &rhs);
    void      deserialize(EngineSettings &o, IDeserializer &s);
    void        serialize(EngineSettings &o, ISerializer &s);
  }
  hash_value         hash(const EngineSettings &o);
  void construct_defaults(      EngineSettings &o); //TODO: implement me
}


#ifdef IMPL_SERIALIZER

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
        if (lhs[i] == 0) return false;
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
  
///////////////////////////////////////////////////////////////////
//  struct EngineSettings
///////////////////////////////////////////////////////////////////
bool operator==(const EngineSettings &lhs, const EngineSettings &rhs) {
  return
    rose_parser_equals(lhs.raytracer, rhs.raytracer) ;
}

bool operator!=(const EngineSettings &lhs, const EngineSettings &rhs) {
  return
    !rose_parser_equals(lhs.raytracer, rhs.raytracer) ;
}

void rose::ecs::serialize(EngineSettings &o, ISerializer &s) {
  if(s.node_begin("EngineSettings", rose::hash("EngineSettings"), &o)) {
    s.key("raytracer");
    serialize(o.raytracer, s);
    s.node_end();
  }
  s.end();
}

void rose::ecs::deserialize(EngineSettings &o, IDeserializer &s) {
  //TODO: implement me
  //construct_defaults(o);

  while (s.next_key()) {
    switch (s.hash_key()) {
      case rose::hash("raytracer"):
        deserialize(o.raytracer, s);
        break;
      default: s.skip_key(); break;
    }
  }
}

rose::hash_value rose::hash(const EngineSettings &o) {
  rose::hash_value h = 0;
  h ^= rose::hash(o.raytracer);
  h = rose::xor64(h);
  return h;
}

#endif
