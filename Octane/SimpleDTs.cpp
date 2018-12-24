#include "SimpleDTs.h"
#include "VariableHandler.h"
#include "MathSolver.h"
#include <iostream>


SimpleDTs::SimpleDTs()
= default;


SimpleDTs::~SimpleDTs()
= default;



// evaluates the given string (value) and tells mem to init it with the wanted datatype
void SimpleDTs::numericInitEval(Memory& mem, const std::string& dataType,
	const std::string& name, const std::string& value, const std::string& scopeName)
{
	const std::string fullName = scopeName + "." + name;
	if (dataType._Equal("int")) {
		mem.addVar(fullName, INT, new int(std::stoi(VariableHandler::getAsString(mem, value, INT))));
	}
	else if (dataType._Equal("long")) {
		mem.addVar(fullName, LONG, new long(std::stol(VariableHandler::getAsString(mem, value, LONG))));
	}
	else if (dataType._Equal("float")) {
		mem.addVar(fullName, FLOAT, new float(std::stof(VariableHandler::getAsString(mem, value, FLOAT))));
	}
	else if (dataType._Equal("double")) {
		mem.addVar(fullName, DOUBLE, new double(std::stod(VariableHandler::getAsString(mem, value, DOUBLE))));
	}
}



// get values from matches so it is easier to call
//TODO check if scopeName is useless
void SimpleDTs::numericInitEval(Memory& mem, std::smatch &matches, const std::string& scopeName)
{
	std::string val = "0";
	if (matches.size() > 3 && matches[3].length() > 0)
		val = matches[3];

	numericInitEval(mem, matches[1], scopeName + std::string(matches[2]), val, scopeName);
}



// evaluates the given string (value) and assigns it to the already existing variable
void SimpleDTs::numericAssignEval(Memory& mem, const std::string& name,
	const std::string& value, const std::string& scopeName)
{
	const Object& obj = mem.getVar(name, scopeName);
	const std::string evaluated = VariableHandler::getAsString(mem, value, obj.type);

	numericAssign(mem, obj, evaluated);

}



// get values from matches so it is easier to call
void SimpleDTs::numericAssignEval(Memory& mem, std::smatch &matches, const std::string& scopeName)
{
	numericAssignEval(mem, matches[1], matches[2], scopeName);
}



// assigns given string (value) it to the already existing variable (scopeName + name)
void SimpleDTs::numericAssign(Memory& mem, const std::string& name,
	const std::string& value, const std::string& scopeName)
{
	const Object& obj = mem.getVar(name, scopeName);
	numericAssign(mem, obj, value);
}



// assigns given string (value) it to the already existing variable (obj)
void SimpleDTs::numericAssign(Memory& mem, const Object& obj, const std::string& value)
{
	// TODO char and short (if keeping them)
	switch (obj.type)
	{
	case INT:
		*(int*)obj.location = std::stoi(value);
		break;
	case LONG:
		*(long*)obj.location = std::stol(value);
		break;
	case FLOAT:
		*(float*)obj.location = std::stof(value);
		break;
	case DOUBLE:
		*(double*)obj.location = std::stod(value);
		break;
	default:;
	}
}


// get values from matches so it is easier to call
void SimpleDTs::numericAssign(Memory& mem, std::smatch &matches, const std::string& scopeName)
{
	numericAssign(mem, matches[1], matches[2], scopeName);
}