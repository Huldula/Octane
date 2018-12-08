#pragma once
#include <string>
#include <regex>
#include "Memory.h"

class VariableHandler
{
public:
	VariableHandler();
	~VariableHandler();
	static std::string getAsString(Memory& mem, std::string s, int type);
	static void numericInit(Memory& mem, std::smatch &matches);
	static void numericAssign(Memory& mem, std::smatch &matches);

private:
	static const std::regex reIsVar;
	static const std::regex reIsNumber;
};

