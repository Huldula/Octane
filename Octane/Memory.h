#pragma once

#include <string>
#include <map>

#include "Object.h"
#include <vector>

class Memory
{
public:
	Memory();
	void addVar(const std::string& name, const Object& o);
	void addVar(const std::string& name, int type, void* value);
	void addVar(const std::string& name, const Object& o, const std::string& scopeName);
	void addVar(const std::string& name, int type, void* value, const std::string& scopeName);
	void deleteVar(const std::string& name, const std::string& scopeName);

	Object getVar(const std::string& name);
	Object getVar(const std::string& name, const std::string& scopeName);
	void* getLocation(const std::string& name, const std::string& scopeName);
	int getType(const std::string& name, const std::string& scopeName);
	Object getDeepestVar(const std::string& name, std::string scopeName);

	std::vector<std::string> getFuncHeader(const std::string& name, const std::string& scopeName);
	void addFuncHeader(const std::string& name, const std::string& scopeName, const std::vector<std::string>& header);

private:
	std::map<std::string, Object> nameLocations;
	std::map<std::string, std::vector<std::string>> functionHeaders;
};
