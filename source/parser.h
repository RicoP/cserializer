#pragma once

#include <vector>

//TODO: Make this flags
enum class member_annotations_t {
  NONE = 0,
  Ignore,
  String,
  Data
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
  std::vector<member_info> members;
};

enum class value_type_t {
  Increment = 0,
  Set
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
