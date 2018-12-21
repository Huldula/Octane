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
const std::regex VariableHandler::reIsVar("(" + VAR_NAME + ")");
//const std::regex VariableHandler::reIsFuncCall("[^\\w]?(" + VAR_NAME + R"() *?\(\)[^\w]?)");
const std::regex VariableHandler::reIsNumber(R"( *?(-|\+)?\d+(?:\.?\d*) *)");
const std::regex VariableHandler::reLastScope(".*(" + VAR_NAME + ")");

VariableHandler::VariableHandler()
= default;


VariableHandler::~VariableHandler()
= default;



std::string VariableHandler::getAsString(Memory& mem, const std::string s, const int type)
{
	return VariableHandler::getAsString(mem, s, type, "");
}


std::string VariableHandler::getAsString(Memory& mem, std::string s, int type, std::string scopeName)
{
	//std::cout << "scopeName in getasstring:   " << scopeName << std::endl;
	if (std::regex_match(s, reIsNumber))
		return s;

	std::smatch matches;
	while (std::regex_search(s, matches, reIsVar))
	{
		const int index = s.find(matches[1]);
		//std::cout << "scopeName+matches[1]:   " << scopeName + "." + std::string(matches[1]) << std::endl;
		Object var = mem.getVar(scopeName + "." + std::string(matches[1]));
		while (!var.exists())
		{
			const int snindex = scopeName.rfind('.');
			scopeName = scopeName.substr(0, snindex);
			var = mem.getVar(scopeName + "." + std::string(matches[1]));
		}

		if (type == -1)
			type = var.type;
		std::string val;
#define TO_STRING(type) val = std::to_string(*(type*)var.location);
#define FUNC_CALL case FUNC: \
			Functions::callFunc(mem, matches[1], scopeName, var.location); \
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
