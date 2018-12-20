#include "VariableHandler.h"
#include "Object.h"
#include "typevalues.cpp"
#include "StringEditor.h"
#include "MathSolver.h"
#include <iostream>
#include <regex>


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



std::string VariableHandler::getAsString(Memory& mem, std::string s, int type)
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
#define FUNC_CALL case FUNC: {\
			Reader r(mem, scopeName + '.' + std::string(matches[1])); \
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


void VariableHandler::numericInit(Memory& mem, const std::string& dataType, 
	const std::string& name, const std::string& val, const std::string& scopeName)
{
	const std::string fullName = scopeName + "." + name;
	if (dataType._Equal("int")) {
		mem.addVar(fullName, INT, new int(std::stoi(VariableHandler::getAsString(mem, val, INT))));
	}
	else if (dataType._Equal("long")) {
		MathSolver<long> solver;
		mem.addVar(fullName, LONG, new long(std::stol(VariableHandler::getAsString(mem, val, LONG))));
	}
	else if (dataType._Equal("float")) {
		MathSolver<float> solver;
		mem.addVar(fullName, FLOAT, new float(std::stof(VariableHandler::getAsString(mem, val, FLOAT))));
	}
	else if (dataType._Equal("double")) {
		MathSolver<double> solver;
		mem.addVar(fullName, DOUBLE, new double(std::stod(VariableHandler::getAsString(mem, val, DOUBLE))));
	}
	else if (dataType._Equal("char")) {
		MathSolver<char> solver;
		mem.addVar(fullName, CHAR, new char(solver.solve(VariableHandler::getAsString(mem, val, CHAR))));
	}
	else if (dataType._Equal("short")) {
		MathSolver<short> solver;
		mem.addVar(fullName, SHORT, new short(solver.solve(VariableHandler::getAsString(mem, val, SHORT))));
	}
}

//TODO check if scopeName is useless
void VariableHandler::numericInit(Memory& mem, std::smatch &matches, const std::string& scopeName)
{
	std::string val = "0";
	if (matches.size() > 3 && matches[3].length() > 0)
		val = matches[3];
	
	numericInit(mem, matches[1], scopeName + std::string(matches[2]), val, scopeName);
}


void VariableHandler::numericAssign(Memory& mem, const std::string& name, 
	const std::string& value, const std::string& scopeName)
{
	const Object& obj = mem.getVar(name);
	const std::string val = VariableHandler::getAsString(mem, value, obj.type);

	// TODO char and short (if keeping them)
	switch (obj.type)
	{
	case INT:
		*(int*)mem.getLocation(name) = std::stoi(val);
		break;
	case LONG:
		*(long*)mem.getLocation(name) = std::stol(val);
		break;
	case FLOAT:
		*(float*)mem.getLocation(name) = std::stof(val);
		break;
	case DOUBLE:
		*(double*)mem.getLocation(name) = std::stod(val);
		break;
	default:;
	}
}

void VariableHandler::numericAssign(Memory& mem, std::smatch &matches, const std::string& scopeName)
{
	numericAssign(mem, matches[1], matches[2], scopeName);
}



void VariableHandler::funcInit(Memory& mem, const std::string& name, const std::string& args,
	std::vector<std::string> lines, const std::string& scopeName)
{
	std::vector<std::string> varInits = StringEditor::split(args, ',');
	for (auto& varInit : varInits)
	{
		StringEditor::trim(varInit);
		std::smatch matches;
		if (std::regex_match(varInit, matches, Reader::reNumericInit))
		{
			numericInit(mem, matches[1], name + std::string(".") + std::string(matches[2]), "0", scopeName);
		}
		else
		{
			std::cout << "Arg is wrong or so" << std::endl;
		}
	}
	std::vector<std::string>* out = new std::vector<std::string>();
	for (const auto& line : lines)
	{
		out->push_back(line);
	}
	mem.addVar(scopeName + "." + name, FUNC, out);
}