#pragma once

#include <string>
#include <map>

#include "Object.h"

class Memory
{
public:
	Memory();
	void addVar(const std::string& name, const Object& o);
	//template<typename T>
	//void addVar(const std::string& name, int type, T value);
	void addVar(const std::string& name, int type, void* value);
	void deleteVar(const std::string& name);

	Object getVar(const std::string& name);
	void* getLocation(const std::string& name);
	template<typename T>
	T* getLocation(const std::string& name);
	int getType(const std::string& name);

private:
	std::map<std::string, Object> nameLocations;
};
