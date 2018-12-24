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
	static void assignArgValue(Memory& mem, const std::string& funcName, const std::string& scopeName,
	                           std::vector<std::string>& doneArgs, const size_t varIndex,
	                           std::string& arg);
	static void assignAllGivenArgValues(Memory& mem, const std::string& funcName, const std::string& scopeName,
	                            const std::string& argString, std::vector<std::string>& doneArgs);
	static void assignAllDefaultArgValues(Memory& mem, const std::string& funcName, const std::string& scopeName,
	                                      std::vector<std::string> doneArgs);
	static void callFunc(Memory& mem, const std::string& funcName, const std::string& scopeName, void* location);
	static void callFunc(Memory& mem, const std::string& funcName, const std::string& scopeName, void* location, const std::string& argString);
};

