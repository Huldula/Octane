#pragma once

#include <string>
#include "typevalues"

class Object
{
public:
	Object();
	Object(int type_, char* location_);
	~Object();
	int type;
	char* location;
	int size();
};

