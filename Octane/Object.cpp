#include "Object.h"
#include "typevalues"



Object::Object() : type(-1), location((char*)-1)
{
}

Object::Object(const int type_, void* location_) : type(type_), location(location_)
{
}

Object::~Object()
= default;

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
	default:
		return 0;
	}
}
