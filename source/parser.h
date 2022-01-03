#pragma once

#include <vector>

//@Flag 
enum class member_annotations_t {
  //It's recommendet Bitfields should start 
  //with NONE but it's not mandatory.
  NONE = 0,
  Ignore = 1 << 0,
  String = 1 << 1,
  Data = 1 << 2
};

enum class value_type_t {
  Increment = 0,
  Set
};

//Flag: Enum class is treated as flags, meaning it has |= &= bit flag operators.
//Imposter: Parse the next multiline comment like it's regular code.
enum class global_annotations_t {
  NONE = 0,
  Flag,
  Imposter
};

//1 = simple variabel, >1 = array, -1 = vector
struct member_info {
  //@String
  char type[64];
  //@String
  char name[64];
  //@String
  char default_value[64] = "";
  int count;
  member_annotations_t annotations = member_annotations_t::NONE;
};

struct struct_info {
  //@String
  char name[64];
  global_annotations_t global_annotations = global_annotations_t::NONE;
  std::vector<member_info> members;
};

struct enum_info {
  //@String
  char name[64];
  //@String
  char value[64] = "0";
  value_type_t value_type = value_type_t::Increment;
};

struct enum_class_info {
  //@String
  char name[64];
  //@String
  char type[64] = "int";
  bool custom_type = false;
  std::vector<enum_info> enums;
  enum_info default_value;
  global_annotations_t enum_annotations = global_annotations_t::NONE;
};

//modifier: 0 = none, '*', '&'
struct function_parameter_info {
  //@String
  char name[64];
  //@String
  char type[64];
  char modifier = 0;
  bool is_const = false;
};

struct function_info {
  //@String
  char name[64];
  //@String
  char type[64] = "void";
  std::vector<function_parameter_info> parameters;
};

struct ParseContext {
  std::vector<enum_class_info> enum_classes;
  std::vector<function_info> functions;
  std::vector<struct_info> structs;
};
