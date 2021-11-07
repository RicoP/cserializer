#include <cstdio>

enum class enum_test : long long {
	NONE = 0,
	ONE,
	TWO,
	SIXTEEN = 1 << 4,
	FOURTYTWO = 42,

	INVALID = -1
};

enum struct enum_test2 {
	NONE,
	ONE,
	TWO,
	SIXTEEN=1<<4,
	FOURTYTWO = 42      ,

	INVALID
};

struct Camera {
	int x;
	int y;
	int z;
};

struct Transform {
	Camera camera;
	vector3 position;
};

struct Scene1 {
	Camera cameras[16];
};
