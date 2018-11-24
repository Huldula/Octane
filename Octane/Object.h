#pragma once

#include <string>
#include "typevalues"

class Object
{
public:
	Object();
	Object(int type_, int location_);
	~Object();
	int type;
	int location;
};

