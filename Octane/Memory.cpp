#include "Memory.h"
#include <iostream>


Memory::Memory()
= default;


void Memory::addVar(const std::string& name, const Object& o)
{
	nameLocations[name] = o;
}

void Memory::addVar(const std::string& name, const int type, void* value)
{
	addVar(name, Object(type, value));
}

void Memory::addVar(const std::string& name, const Object& o, const std::string& scopeName)
{
	nameLocations[scopeName + "." + name] = o;
}

void Memory::addVar(const std::string& name, const int type, void* value, const std::string& scopeName)
{
	addVar(name, Object(type, value), scopeName);
}

void Memory::deleteVar(const std::string& name, const std::string& scopeName)
{
	// TODO make faster if possible
	for (int i = 0; i < getDeepestVar(name, scopeName).size(); i++)
		delete((char*)getDeepestVar(name, scopeName).location + i);
	nameLocations.erase(name);
}

Object Memory::getVar(const std::string& name)
{
	return nameLocations[name];
}

Object Memory::getVar(const std::string& name, const std::string& scopeName)
{
	return getDeepestVar(name, scopeName);
}

void* Memory::getLocation(const std::string& name, const std::string& scopeName)
{
	return getDeepestVar(name, scopeName).location;
}


int Memory::getType(const std::string& name, const std::string& scopeName)
{
	return getDeepestVar(name, scopeName).type;
}

Object Memory::getDeepestVar(const std::string& name, std::string scopeName)
{
	Object var = getVar(scopeName + "." + name);
	while (!var.exists())
	{
		const int snindex = scopeName.rfind('.');
		scopeName = scopeName.substr(0, snindex);
		var = getVar(scopeName + "." + name);
	}
	return var;
}
