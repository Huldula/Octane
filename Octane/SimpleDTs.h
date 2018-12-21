#pragma once
#include "typevalues.cpp"
#include <string>
#include <regex>

class Memory;

class SimpleDTs
{
public:
	SimpleDTs();
	~SimpleDTs();
	static void numericInit(Memory& mem, const std::string& dataType,
		const std::string& name, const std::string& val, const std::string& scopeName);
	static void numericInit(Memory& mem, std::smatch &matches, const std::string& scopeName);
	static void numericAssign(Memory& mem, const std::string& name,
		const std::string& value, const std::string& scopeName);
	static void numericAssign(Memory& mem, std::smatch &matches, const std::string& scopeName);
};

