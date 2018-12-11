#include "VariableHandler.h"
#include "Object.h"
#include "typevalues.cpp"
#include "StringEditor.h"
#include "MathSolver.h"
#include <iostream>


//const std::regex VariableHandler::reIsVar("[^\\w]?(" + VAR_NAME + ")[^\\w]?");
//const std::regex VariableHandler::reIsVar("[^\\w]?(" + VAR_NAME + R"() *?(?:\(\))?[^\w]?)");
const std::regex VariableHandler::reIsVar("(" + VAR_NAME + ")");
//const std::regex VariableHandler::reIsFuncCall("[^\\w]?(" + VAR_NAME + R"() *?\(\)[^\w]?)");
const std::regex VariableHandler::reIsNumber(R"( *?(-|\+)?\d+(?:\.?\d*) *)");

VariableHandler::VariableHandler()
= default;


VariableHandler::~VariableHandler()
= default;



std::string VariableHandler::getAsString(Memory& mem, std::string s, int type)
{
	//if (s._Starts_with("\"") && s.find('"', 1) == s.length() - 1)
	//	return s;
	if (std::regex_match(s, reIsNumber))
		return s;

	std::smatch matches;
	while (std::regex_search(s, matches, reIsVar))
	{
		const int index = s.find(matches[1]);
		const Object& var = mem.getVar(matches[1]);
		if (type == -1)
			type = var.type;
		std::string val;
#define TO_STRING(type) val = std::to_string(*(type*)var.location);
#define FUNC_CALL case FUNC: {\
			Reader r(mem); \
			std::vector<std::string> lines = *(std::vector<std::string>*)var.location; \
			for (unsigned int i = 0; i < lines.size(); i++) { \
				r.interpret(lines[i]); \
			}} \
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


void VariableHandler::numericInit(Memory& mem, std::smatch &matches)
{
	std::string val = "0";
	if (matches.size() > 3 && matches[3].length() > 0)
		val = matches[3];
	
	if (!matches[1].compare("int")) {
		mem.addVar(matches[2], INT, new int(std::stoi(VariableHandler::getAsString(mem, val, INT))));
	}
	else if (!matches[1].compare("long")) {
		MathSolver<long> solver;
		mem.addVar(matches[2], LONG, new long(std::stol(VariableHandler::getAsString(mem, val, LONG))));
	}
	else if (!matches[1].compare("float")) {
		MathSolver<float> solver;
		mem.addVar(matches[2], FLOAT, new float(std::stof(VariableHandler::getAsString(mem, val, FLOAT))));
	}
	else if (!matches[1].compare("double")) {
		MathSolver<double> solver;
		mem.addVar(matches[2], DOUBLE, new double(std::stod(VariableHandler::getAsString(mem, val, DOUBLE))));
	}
	else if (!matches[1].compare("char")) {
		MathSolver<char> solver;
		mem.addVar(matches[2], CHAR, new char(solver.solve(VariableHandler::getAsString(mem, val, CHAR))));
	}
	else if (!matches[1].compare("short")) {
		MathSolver<short> solver;
		mem.addVar(matches[2], SHORT, new short(solver.solve(VariableHandler::getAsString(mem, val, SHORT))));
	}
}


void VariableHandler::numericAssign(Memory& mem, std::smatch &matches)
{
	const Object& obj = mem.getVar(matches[1]);
	const std::string val = VariableHandler::getAsString(mem, matches[2], obj.type);

	// TODO char and short (if keeping them)
	switch (obj.type)
	{
	case INT:
		*(int*)mem.getLocation(matches[1]) = std::stoi(val);
		break;
	case LONG:
		*(long*)mem.getLocation(matches[1]) = std::stol(val);
		break;
	case FLOAT:
		*(float*)mem.getLocation(matches[1]) = std::stof(val);
		break;
	case DOUBLE:
		*(double*)mem.getLocation(matches[1]) = std::stod(val);
		break;
	default:;
	}
}



void VariableHandler::funcInit(Memory& mem, const std::string& name, const std::vector<std::string>& lines)
{
	mem.addVar(name, FUNC, new std::vector<std::string>(lines));
}