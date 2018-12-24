#include "Object.h"
#include "typevalues.cpp"
#include <string>


Object::Object() : type(-1), location(nullptr)
{
}

Object::Object(const int type_, void* location_) : type(type_), location(location_)
{
}

Object::~Object()
= default;


// returns the amount of bytes in occupies in RAM
int Object::size() const
{
	switch (type)
	{
	case INT:
		return 4;
	case LONG:
		return 8;
	case FLOAT:
		return 4;
	case DOUBLE:
		return 8;
	case CHAR:
		return 1;
	case BOOL:
		return 1;
	case SHORT:
		return 2;
	case FUNC:
		return sizeof(std::string);
	default:
		return 0;
	}
}

bool Object::exists() const
{
	return type != -1;
}
