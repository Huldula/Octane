#include "Object.h"



Object::Object()
{
}

Object::Object(int type_, char* location_)
{
	type = type_;
	location = location_;
}

Object::~Object()
{
}

int Object::size()
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
	}
	return 0;
}