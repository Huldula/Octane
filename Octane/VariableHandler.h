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
	static std::string getAsString(Memory& mem, std::string s, int type, std::string scopeName);

private:
	static const std::regex reIsVar;
	//static const std::regex reIsFuncCall;
	static const std::regex reIsNumber;
	static const std::regex reLastScope;
};

