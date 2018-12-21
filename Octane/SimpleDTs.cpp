#include "SimpleDTs.h"
#include "VariableHandler.h"
#include "MathSolver.h"


SimpleDTs::SimpleDTs()
= default;


SimpleDTs::~SimpleDTs()
= default;


void SimpleDTs::numericInit(Memory& mem, const std::string& dataType,
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
void SimpleDTs::numericInit(Memory& mem, std::smatch &matches, const std::string& scopeName)
{
	std::string val = "0";
	if (matches.size() > 3 && matches[3].length() > 0)
		val = matches[3];

	numericInit(mem, matches[1], scopeName + std::string(matches[2]), val, scopeName);
}


void SimpleDTs::numericAssign(Memory& mem, const std::string& name,
	const std::string& value, const std::string& scopeName)
{
	const Object& obj = mem.getVar(name, scopeName);
	const std::string val = VariableHandler::getAsString(mem, value, obj.type);

	// TODO char and short (if keeping them)
	switch (obj.type)
	{
	case INT:
		*(int*)mem.getLocation(name, scopeName) = std::stoi(val);
		break;
	case LONG:
		*(long*)mem.getLocation(name, scopeName) = std::stol(val);
		break;
	case FLOAT:
		*(float*)mem.getLocation(name, scopeName) = std::stof(val);
		break;
	case DOUBLE:
		*(double*)mem.getLocation(name, scopeName) = std::stod(val);
		break;
	default:;
	}

}

void SimpleDTs::numericAssign(Memory& mem, std::smatch &matches, const std::string& scopeName)
{
	numericAssign(mem, matches[1], matches[2], scopeName);
}
