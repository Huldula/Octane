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



std::string VariableHandler::getAsString(Memory& mem, const std::string s, const int type)
{
	return VariableHandler::getAsString(mem, s, type, "");
}

// calls MathSolver to solve mathematical expressions with the right datatype
void VariableHandler::mathEval(std::string& s, int& type)
{
	if (type == -1)
		type = StringEditor::split(s, " ")[0].find(".") == (unsigned int)-1 ? INT : DOUBLE;

#define MATH_SOLVE(type) { \
			MathSolver<type> solver; \
			s = std::to_string(solver.solve(s)); \
		}

	SWITCH(type, MATH_SOLVE, );
}


// replaces the variables and functions with their values in the string
void VariableHandler::replaceVarFunc(Memory& mem, std::string& s, int& type, const std::string& scopeName)
{
	std::smatch matches;
	while (std::regex_search(s, matches, reIsVar))
	{
		const size_t index = s.find(matches[1]);
		// get the variable to the name
		const Object var = mem.getVar(std::string(matches[1]), scopeName);

		// set type so the MathSolver knows what to do
		if (type == -1)
			type = var.type;
		std::string val;

#define TO_STRING(type) val = std::to_string(*(type*)var.location);
#define FUNC_CALL case FUNC: {\
			std::string argString = StringEditor::replace(matches[2], " ", ""); \
			Functions::callFunc(mem, matches[1], scopeName, var.location, argString); }\
			default: break;
		SWITCH(var.type, TO_STRING, FUNC_CALL);

		s.replace(index, matches[1].length(), val);
	}
}

// evaluates all expressions and returns the result as a string
// TODO make it work with numbers, not as string
std::string VariableHandler::getAsString(Memory& mem, std::string s, int type, const std::string& scopeName)
{
	if (std::regex_match(s, reIsNumber))
		return s;

	replaceVarFunc(mem, s, type, scopeName);

	mathEval(s, type);
	return s;
}
