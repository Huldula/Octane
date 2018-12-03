#include "Memory.h"
#include <iostream>


Memory::Memory()
= default;


void Memory::addVar(const std::string& name, const Object& o)
{
	nameLocations[name] = o;
}

// TODO mach so pointer wieder nicht template
//template<typename T>
//void Memory::addVar(const std::string& name, const int type, T value)
void Memory::addVar(const std::string& name, const int type, void* value)
{
	addVar(name, Object(type, value));
}

void Memory::deleteVar(const std::string& name)
{
	// TODO make faster if possible
	for (int i = 0; i < nameLocations[name].size(); i++)
		delete((char*)nameLocations[name].location + i);
	nameLocations.erase(name);
}

Object Memory::getVar(const std::string& name)
{
	return nameLocations[name];
}


void* Memory::getLocation(const std::string& name)
{
	return nameLocations[name].location;
}

template<typename T>
T* Memory::getLocation(const std::string& name)
{
	return (T*)nameLocations[name].location;
}


int Memory::getType(const std::string& name)
{
	return nameLocations[name].type;
}

//template void Memory::addVar<int>(const std::string& name, int type, int value);
//template void Memory::addVar<long>(const std::string& name, int type, long value);
//template void Memory::addVar<float>(const std::string& name, int type, float value);
//template void Memory::addVar<double>(const std::string& name, int type, double value);
//template void Memory::addVar<short>(const std::string& name, int type, short value);
//template void Memory::addVar<bool>(const std::string& name, int type, bool value);
//template void Memory::addVar<char>(const std::string& name, int type, char value);