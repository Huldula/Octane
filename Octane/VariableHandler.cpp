#include "VariableHandler.h"
#include "Object.h"
#include "typevalues.cpp"
#include "StringEditor.h"
#include "MathSolver.h"
#include <iostream>
#include <regex>
#include "Functions.h"


//const std::regex VariableHandler::reIsVar("[^\\w]?(" + VAR_NAME + ")[^\\w]?");
//const std::regex VariableHandler::reIsVar("[^\\w]?(" + VAR_NAME + R"() *?(?:\(\))?[^\w]?)");
const std::regex VariableHandler::reIsVar("(" + VAR_NAME + R"()(?:\((.*)\))?)");
//const std::regex VariableHandler::reIsFuncCall("[^\\w]?(" + VAR_NAME + R"() *?\(\)[^\w]?)");
const std::regex VariableHandler::reIsNumber(R"( *?(-|\+)?\d+(?:\.?\d*) *)");
const std::regex VariableHandler::reLastScope(".*(" + VAR_NAME + ")");

VariableHandler::VariableHandler()
= default;


VariableHandler::~VariableHandler()
= default;



std::string VariableHandler::getAsString(Memory& mem, std::string s, const int type)
{
	return VariableHandler::getAsString(mem, s, type, "");
}


std::string VariableHandler::getAsString(Memory& mem, std::string s, int type, const std::string& scopeName)
{
	//std::cout << "scopeName in getasstring:   " << scopeName << std::endl;
	if (std::regex_match(s, reIsNumber))
		return s;

	std::smatch matches;
	while (std::regex_search(s, matches, reIsVar))
	{
		const size_t index = s.find(matches[1]);
		const Object var = mem.getVar(std::string(matches[1]), scopeName);
		//std::cout << "scopeName+matches[1]:   " << scopeName + "." + std::string(matches[1]) << std::endl;

		if (type == -1)
			type = var.type;
		std::string val;
		//Functions::callFunc(mem, matches[1], scopeName, var.location); 

#define TO_STRING(type) val = std::to_string(*(type*)var.location);
		// TODO remove spaces from args
#define FUNC_CALL case FUNC: {\
			std::string argString = StringEditor::replace(matches[2], " ", ""); \
			Functions::callFunc(mem, matches[1], scopeName, var.location, argString); }\
			default: break;
		SWITCH(var.type, TO_STRING, FUNC_CALL);

		s.replace(index, matches[1].length(), val);
	}

	if (type == -1)
		type = StringEditor::split(s, " ")[0].find(".") == (unsigned int)-1 ? INT : DOUBLE;

#define MATH_SOLVE(type) { \
			MathSolver<type> solver; \
			s = std::to_string(solver.solve(s)); \
		}

	SWITCH(type, MATH_SOLVE, );
	//std::cout << s << std::endl;
	return s;
}
