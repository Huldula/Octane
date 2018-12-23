#pragma once
#include <string>
#include <vector>
#include "typevalues.cpp"

class Memory;

class Functions
{
public:
	Functions();
	~Functions();
	static void funcInit(Memory& mem, const std::string& name, const std::string& args,
		std::vector<std::string> lines, const std::string& scopeName);
	static void callFunc(Memory& mem, const std::string& name, const std::string& scopeName, void* location);
	static void callFunc(Memory& mem, const std::string& name, const std::string& scopeName, void* location, const std::string& argString);
};

