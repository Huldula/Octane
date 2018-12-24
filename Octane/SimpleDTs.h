#pragma once
#include "typevalues.cpp"
#include <string>
#include <regex>
#include "Object.h"

class Memory;

class SimpleDTs
{
public:
	SimpleDTs();
	~SimpleDTs();
	static void numericInitEval(Memory& mem, const std::string& dataType,
		const std::string& name, const std::string& val, const std::string& scopeName);
	static void numericInitEval(Memory& mem, std::smatch &matches, const std::string& scopeName);
	static void numericAssignEval(Memory& mem, const std::string& name,
		const std::string& value, const std::string& scopeName);
	static void numericAssignEval(Memory& mem, std::smatch &matches, const std::string& scopeName);
	static void numericAssign(Memory& mem, const std::string& name,
		const std::string& value, const std::string& scopeName);
	static void numericAssign(Memory& mem, const Object& obj,
		const std::string& value);
	static void numericAssign(Memory& mem, std::smatch &matches, const std::string& scopeName);
};

