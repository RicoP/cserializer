#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <stdarg.h>
#include <stdio.h>
#include <vector>

#include <rose/hash.h>
#include <serializer/serializer.h>
#include <serializer/jsonserializer.h>

#include "camera.h"
#include "enginesettings.h"

#define IMPL_SERIALIZER
#include "serializer.h"

int main() {
  
  Camera camera;
  camera.x = 1;
  camera.y = 2;
  camera.z = 3;

  Transform transform;
  transform.camera = camera;
  vector3 position{ 4,5,6 };
  transform.position = position;

  char tmp_path_B[L_tmpnam];
  
  char* tmp_path = tmpnam(tmp_path_B);

  assert(tmp_path);

  FILE* f = fopen(tmp_path, "wb");
  assert(f);
  JsonSerializer jsons(f);
  rose::ecs::serialize(transform, jsons);
  fclose(f);

  char json[10 * 1024];

  f = fopen(tmp_path, "rb");
  assert(f);

  size_t size = fread(json, 1, sizeof(json), f);
  fclose(f);
  remove(tmp_path);
  assert(size);
  assert(size < sizeof(json));
  json[size] = 0;
  JsonDeserializer jsond(json);
  Transform transform2;
  rose::ecs::deserialize(transform2, jsond);

  assert(transform == transform2);

  transform.interpolated_position.x = 1;
  transform2.interpolated_position.x = 2;
  assert(transform == transform2); //interpolated_position is ignored

  transform2.name[0] = 'B';
  assert(transform != transform2);

  return 0;
}