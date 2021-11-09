#pragma once

#include <rose/hash.h>
#include <serializer/serializer.h>

///////////////////////////////////////////////////////////////////
//  AUTOGEN                                                      //
///////////////////////////////////////////////////////////////////
enum class                   value_type_t;
const char * to_string(const value_type_t &);

struct                member_info;
namespace rose {
  namespace ecs {
    bool operator==(const member_info &lhs, const member_info &rhs);
    bool operator!=(const member_info &lhs, const member_info &rhs);
    void      deserialize(member_info &o, IDeserializer &s);
    void        serialize(member_info &o, ISerializer &s);
  }
  hash_value       hash(member_info &o);
}


struct                struct_info;
namespace rose {
  namespace ecs {
    bool operator==(const struct_info &lhs, const struct_info &rhs);
    bool operator!=(const struct_info &lhs, const struct_info &rhs);
    void      deserialize(struct_info &o, IDeserializer &s);
    void        serialize(struct_info &o, ISerializer &s);
  }
  hash_value       hash(struct_info &o);
}


struct                enum_info;
namespace rose {
  namespace ecs {
    bool operator==(const enum_info &lhs, const enum_info &rhs);
    bool operator!=(const enum_info &lhs, const enum_info &rhs);
    void      deserialize(enum_info &o, IDeserializer &s);
    void        serialize(enum_info &o, ISerializer &s);
  }
  hash_value       hash(enum_info &o);
}


struct                enum_class_info;
namespace rose {
  namespace ecs {
    bool operator==(const enum_class_info &lhs, const enum_class_info &rhs);
    bool operator!=(const enum_class_info &lhs, const enum_class_info &rhs);
    void      deserialize(enum_class_info &o, IDeserializer &s);
    void        serialize(enum_class_info &o, ISerializer &s);
  }
  hash_value       hash(enum_class_info &o);
}


struct                function_parameter_info;
namespace rose {
  namespace ecs {
    bool operator==(const function_parameter_info &lhs, const function_parameter_info &rhs);
    bool operator!=(const function_parameter_info &lhs, const function_parameter_info &rhs);
    void      deserialize(function_parameter_info &o, IDeserializer &s);
    void        serialize(function_parameter_info &o, ISerializer &s);
  }
  hash_value       hash(function_parameter_info &o);
}


struct                function_info;
namespace rose {
  namespace ecs {
    bool operator==(const function_info &lhs, const function_info &rhs);
    bool operator!=(const function_info &lhs, const function_info &rhs);
    void      deserialize(function_info &o, IDeserializer &s);
    void        serialize(function_info &o, ISerializer &s);
  }
  hash_value       hash(function_info &o);
}


struct                ParseContext;
namespace rose {
  namespace ecs {
    bool operator==(const ParseContext &lhs, const ParseContext &rhs);
    bool operator!=(const ParseContext &lhs, const ParseContext &rhs);
    void      deserialize(ParseContext &o, IDeserializer &s);
    void        serialize(ParseContext &o, ISerializer &s);
  }
  hash_value       hash(ParseContext &o);
}


#ifdef IMPL_SERIALIZER

const char * to_string(const value_type_t & e) {
    switch(e) {
        case value_type_t::Increment: return "Increment";
        case value_type_t::Set: return "Set";
        default: return "<UNKNOWN>";
    }
}

///////////////////////////////////////////////////////////////////
//  struct member_info
///////////////////////////////////////////////////////////////////
bool operator==(const member_info &lhs, const member_info &rhs) { 
  return 
    lhs.type == rhs.type &&
    lhs.name == rhs.name &&
    lhs.default_value == rhs.default_value &&
    lhs.count == rhs.count;
} 

bool operator!=(const member_info &lhs, const member_info &rhs) { 
  return 
    lhs.type != rhs.type ||
    lhs.name != rhs.name ||
    lhs.default_value != rhs.default_value ||
    lhs.count != rhs.count;
} 

void rose::ecs::serialize(member_info &o, ISerializer &s) {                      
  if(s.node_begin("member_info", rose::hash("member_info"), &o)) {                
    s.key("type");                                                
    serialize(o.type, s);                                           
    s.key("name");                                                
    serialize(o.name, s);                                           
    s.key("default_value");                                                
    serialize(o.default_value, s);                                           
    s.key("count");                                                
    serialize(o.count, s);                                           
    s.node_end();                                                   
  }                                                                 
  s.end();                                                          
}                                                                   

void rose::ecs::deserialize(member_info &o, IDeserializer &s) {              
  //TODO: implement me                                   
  //construct_defaults(o);                                 
                                                         
  while (s.next_key()) {                                 
    switch (s.hash_key()) {                              
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
      default: s.skip_key(); break;                      
    }                                                    
  }                                                      
}                                                        

rose::hash_value rose::hash(member_info &o) {              
  rose::hash_value h = 0;                   
  h ^= rose::hash(o.type);                  
  h = rose::xor64(h);                     
  h ^= rose::hash(o.name);                  
  h = rose::xor64(h);                     
  h ^= rose::hash(o.default_value);                  
  h = rose::xor64(h);                     
  h ^= rose::hash(o.count);                  
  h = rose::xor64(h);                     
  return h;                           
}                                     
///////////////////////////////////////////////////////////////////
//  struct struct_info
///////////////////////////////////////////////////////////////////
bool operator==(const struct_info &lhs, const struct_info &rhs) { 
  return 
    lhs.name == rhs.name &&
    lhs.members == rhs.members;
} 

bool operator!=(const struct_info &lhs, const struct_info &rhs) { 
  return 
    lhs.name != rhs.name ||
    lhs.members != rhs.members;
} 

void rose::ecs::serialize(struct_info &o, ISerializer &s) {                      
  if(s.node_begin("struct_info", rose::hash("struct_info"), &o)) {                
    s.key("name");                                                
    serialize(o.name, s);                                           
    s.key("members");                                                
    serialize(o.members, s);                                           
    s.node_end();                                                   
  }                                                                 
  s.end();                                                          
}                                                                   

void rose::ecs::deserialize(struct_info &o, IDeserializer &s) {              
  //TODO: implement me                                   
  //construct_defaults(o);                                 
                                                         
  while (s.next_key()) {                                 
    switch (s.hash_key()) {                              
      case rose::hash("name"):                         
        deserialize(o.name, s);                          
        break;                                         
      case rose::hash("members"):                         
        deserialize(o.members, s);                          
        break;                                         
      default: s.skip_key(); break;                      
    }                                                    
  }                                                      
}                                                        

rose::hash_value rose::hash(struct_info &o) {              
  rose::hash_value h = 0;                   
  h ^= rose::hash(o.name);                  
  h = rose::xor64(h);                     
  h ^= rose::hash(o.members);                  
  h = rose::xor64(h);                     
  return h;                           
}                                     
///////////////////////////////////////////////////////////////////
//  struct enum_info
///////////////////////////////////////////////////////////////////
bool operator==(const enum_info &lhs, const enum_info &rhs) { 
  return 
    lhs.name == rhs.name &&
    lhs.value == rhs.value &&
    lhs.value_type == rhs.value_type;
} 

bool operator!=(const enum_info &lhs, const enum_info &rhs) { 
  return 
    lhs.name != rhs.name ||
    lhs.value != rhs.value ||
    lhs.value_type != rhs.value_type;
} 

void rose::ecs::serialize(enum_info &o, ISerializer &s) {                      
  if(s.node_begin("enum_info", rose::hash("enum_info"), &o)) {                
    s.key("name");                                                
    serialize(o.name, s);                                           
    s.key("value");                                                
    serialize(o.value, s);                                           
    //s.key("value_type");                                                
    //serialize(o.value_type, s);                                           
    s.node_end();                                                   
  }                                                                 
  s.end();                                                          
}                                                                   

void rose::ecs::deserialize(enum_info &o, IDeserializer &s) {              
  //TODO: implement me                                   
  //construct_defaults(o);                                 
                                                         
  while (s.next_key()) {                                 
    switch (s.hash_key()) {                              
      case rose::hash("name"):                         
        deserialize(o.name, s);                          
        break;                                         
      case rose::hash("value"):                         
        deserialize(o.value, s);                          
        break;                                         
      //case rose::hash("value_type"):                         
        //deserialize(o.value_type, s);                          
        break;                                         
      default: s.skip_key(); break;                      
    }                                                    
  }                                                      
}                                                        

rose::hash_value rose::hash(enum_info &o) {              
  rose::hash_value h = 0;                   
  h ^= rose::hash(o.name);                  
  h = rose::xor64(h);                     
  h ^= rose::hash(o.value);                  
  //h = rose::xor64(h);                     
  //h ^= rose::hash(o.value_type);                  
  h = rose::xor64(h);                     
  return h;                           
}                                     
///////////////////////////////////////////////////////////////////
//  struct enum_class_info
///////////////////////////////////////////////////////////////////
bool operator==(const enum_class_info &lhs, const enum_class_info &rhs) { 
  return 
    lhs.name == rhs.name &&
    lhs.type == rhs.type &&
    lhs.enums == rhs.enums;
} 

bool operator!=(const enum_class_info &lhs, const enum_class_info &rhs) { 
  return 
    lhs.name != rhs.name ||
    lhs.type != rhs.type ||
    lhs.enums != rhs.enums;
} 

void rose::ecs::serialize(enum_class_info &o, ISerializer &s) {                      
  if(s.node_begin("enum_class_info", rose::hash("enum_class_info"), &o)) {                
    s.key("name");                                                
    serialize(o.name, s);                                           
    s.key("type");                                                
    serialize(o.type, s);                                           
    s.key("enums");                                                
    serialize(o.enums, s);                                           
    s.node_end();                                                   
  }                                                                 
  s.end();                                                          
}                                                                   

void rose::ecs::deserialize(enum_class_info &o, IDeserializer &s) {              
  //TODO: implement me                                   
  //construct_defaults(o);                                 
                                                         
  while (s.next_key()) {                                 
    switch (s.hash_key()) {                              
      case rose::hash("name"):                         
        deserialize(o.name, s);                          
        break;                                         
      case rose::hash("type"):                         
        deserialize(o.type, s);                          
        break;                                         
      case rose::hash("enums"):                         
        deserialize(o.enums, s);                          
        break;                                         
      default: s.skip_key(); break;                      
    }                                                    
  }                                                      
}                                                        

rose::hash_value rose::hash(enum_class_info &o) {              
  rose::hash_value h = 0;                   
  h ^= rose::hash(o.name);                  
  h = rose::xor64(h);                     
  h ^= rose::hash(o.type);                  
  h = rose::xor64(h);                     
  h ^= rose::hash(o.enums);                  
  h = rose::xor64(h);                     
  return h;                           
}                                     
///////////////////////////////////////////////////////////////////
//  struct function_parameter_info
///////////////////////////////////////////////////////////////////
bool operator==(const function_parameter_info &lhs, const function_parameter_info &rhs) { 
  return 
    lhs.name == rhs.name &&
    lhs.type == rhs.type &&
    lhs.modifier == rhs.modifier &&
    lhs.is_const == rhs.is_const;
} 

bool operator!=(const function_parameter_info &lhs, const function_parameter_info &rhs) { 
  return 
    lhs.name != rhs.name ||
    lhs.type != rhs.type ||
    lhs.modifier != rhs.modifier ||
    lhs.is_const != rhs.is_const;
} 

void rose::ecs::serialize(function_parameter_info &o, ISerializer &s) {                      
  if(s.node_begin("function_parameter_info", rose::hash("function_parameter_info"), &o)) {                
    s.key("name");                                                
    serialize(o.name, s);                                           
    s.key("type");                                                
    serialize(o.type, s);                                           
    //s.key("modifier");                                                
    //serialize(o.modifier, s);                                           
    s.key("is_const");                                                
    serialize(o.is_const, s);                                           
    s.node_end();                                                   
  }                                                                 
  s.end();                                                          
}                                                                   

void rose::ecs::deserialize(function_parameter_info &o, IDeserializer &s) {              
  //TODO: implement me                                   
  //construct_defaults(o);                                 
                                                         
  while (s.next_key()) {                                 
    switch (s.hash_key()) {                              
      case rose::hash("name"):                         
        deserialize(o.name, s);                          
        break;                                         
      case rose::hash("type"):                         
        deserialize(o.type, s);                          
        break;                                         
     // case rose::hash("modifier"):                         
      //  deserialize(o.modifier, s);                          
        break;                                         
      case rose::hash("is_const"):                         
        deserialize(o.is_const, s);                          
        break;                                         
      default: s.skip_key(); break;                      
    }                                                    
  }                                                      
}                                                        

rose::hash_value rose::hash(function_parameter_info &o) {              
  rose::hash_value h = 0;                   
  h ^= rose::hash(o.name);                  
  h = rose::xor64(h);                     
  h ^= rose::hash(o.type);                  
  h = rose::xor64(h);                     
  h ^= rose::hash(o.modifier);                  
  h = rose::xor64(h);                     
  h ^= rose::hash(o.is_const);                  
  h = rose::xor64(h);                     
  return h;                           
}                                     
///////////////////////////////////////////////////////////////////
//  struct function_info
///////////////////////////////////////////////////////////////////
bool operator==(const function_info &lhs, const function_info &rhs) { 
  return 
    lhs.name == rhs.name &&
    lhs.type == rhs.type &&
    lhs.parameters == rhs.parameters;
} 

bool operator!=(const function_info &lhs, const function_info &rhs) { 
  return 
    lhs.name != rhs.name ||
    lhs.type != rhs.type ||
    lhs.parameters != rhs.parameters;
} 

void rose::ecs::serialize(function_info &o, ISerializer &s) {                      
  if(s.node_begin("function_info", rose::hash("function_info"), &o)) {                
    s.key("name");                                                
    serialize(o.name, s);                                           
    s.key("type");                                                
    serialize(o.type, s);                                           
    s.key("parameters");                                                
    serialize(o.parameters, s);                                           
    s.node_end();                                                   
  }                                                                 
  s.end();                                                          
}                                                                   

void rose::ecs::deserialize(function_info &o, IDeserializer &s) {              
  //TODO: implement me                                   
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

rose::hash_value rose::hash(function_info &o) {              
  rose::hash_value h = 0;                   
  h ^= rose::hash(o.name);                  
  h = rose::xor64(h);                     
  h ^= rose::hash(o.type);                  
  h = rose::xor64(h);                     
  h ^= rose::hash(o.parameters);                  
  h = rose::xor64(h);                     
  return h;                           
}                                     
///////////////////////////////////////////////////////////////////
//  struct ParseContext
///////////////////////////////////////////////////////////////////
bool operator==(const ParseContext &lhs, const ParseContext &rhs) { 
  return 
    lhs.enum_classes == rhs.enum_classes &&
    lhs.functions == rhs.functions &&
    lhs.structs == rhs.structs;
} 

bool operator!=(const ParseContext &lhs, const ParseContext &rhs) { 
  return 
    lhs.enum_classes != rhs.enum_classes ||
    lhs.functions != rhs.functions ||
    lhs.structs != rhs.structs;
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
  //TODO: implement me                                   
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

rose::hash_value rose::hash(ParseContext &o) {              
  rose::hash_value h = 0;                   
  h ^= rose::hash(o.enum_classes);                  
  h = rose::xor64(h);                     
  h ^= rose::hash(o.functions);                  
  h = rose::xor64(h);                     
  h ^= rose::hash(o.structs);                  
  h = rose::xor64(h);                     
  return h;                           
}                                     

#endif
