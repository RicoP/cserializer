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

/* Multi 
line comments
should work fine*/

// Single comments too 

//@Imposter vector3 is declared somewhere else, but we need just the basic version
/*
struct vector3 {
	float x,  y  ,   z;
};

void operator== (const vector3 & lhs, const vector3 & rhs) {
	return
		lhs.x == rhs.x &&
		lhs.y == rhs.y &&
		lhs.z == rhs.z;
}

void operator!= (const vector3 & lhs, const vector3 & rhs) {
	return
		lhs.x != rhs.x ||
		lhs.y != rhs.y ||
		lhs.z != rhs.z;
}

*/

struct Camera {
	int x;
	int y;
	int z;
};

struct Transform {
	//@String
	char name[64] = "Hello";
	Camera camera;
	vector3 position;

	//@Ignore this will not be serialized
	vector3 interpolated_position;
};

struct Scene1 {
	Camera cameras[16];
};

void serialize1(Camera & o, ISerializer & s)  ;

void serialize2(const Camera o, ISerializer & s) {
	//BLA BLA
}


bool compare(const Camera & lhs, const Camera & rhs) {
	return false;
}