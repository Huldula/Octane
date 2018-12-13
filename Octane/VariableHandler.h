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
	static std::string getAsString(Memory& mem, std::string s, int type, const std::string& scopeName);

	static void numericInit(Memory& mem, const std::string& dataType, 
		const std::string& name, const std::string& val);
	static void numericInit(Memory& mem, std::smatch &matches, const std::string& scopeName);
	static void numericAssign(Memory& mem, std::smatch &matches);
	static void numericAssign(Memory& mem, const std::string& name, const std::string& value);

	static void funcInit(Memory& mem, const std::string& name, const std::string& args, 
		std::vector<std::string> lines);

private:
	static const std::regex reIsVar;
	//static const std::regex reIsFuncCall;
	static const std::regex reIsNumber;
};

