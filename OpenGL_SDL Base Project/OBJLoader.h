#ifndef OBJLOADER
#define OBJLOADER
#include <string>
#include <iostream>
#include "Commons.h"
#include <vector>

using namespace std;

extern bool LoadOBJ(const char* path, obj_type_ptr p_object);

class OBJLoader {

public:
	OBJLoader();
	~OBJLoader();

private:
	long FileLength(int f);

	bool LoadOBJ(const char* path, obj_type_ptr p_object);
};

#endif