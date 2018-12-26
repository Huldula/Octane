#include "Functions.h"
#include "StringEditor.h"
#include <regex>
#include "Reader.h"
#include "SimpleDTs.h"
#include <iostream>
#include "VariableHandler.h"


Functions::Functions()
= default;


Functions::~Functions()
= default;





void Functions::funcInit(Memory& mem, const std::string& name, const std::string& args,
	std::vector<std::string> lines, const std::string& scopeName)
{
	if (args.length() > 0)
	{
		std::vector<std::string> nameList;	// store order so you don't have to specify the name
		std::vector<std::string> initList;	// store the default init
		std::vector<std::string> varInits = StringEditor::split(args, ',');
		for (auto& varInit : varInits)
		{
			StringEditor::trimThis(varInit);
			std::smatch matches;
			if (std::regex_match(varInit, matches, Reader::reNumericInit))
			{
				// init the numbers so they exist
				SimpleDTs::numericInitEval(mem, matches[1], name + '.' + std::string(matches[2]), "0", scopeName);
				nameList.push_back(matches[2]);
				initList.push_back(matches[3]);
			}
			else
			{
				std::cout << "Arg is wrong or so" << std::endl;
			}
		}
		// store the info in mem
		mem.addFuncHeader(name, scopeName, nameList);
		mem.addFuncInit(name, scopeName, initList);
	}
	// the only way I found to make a new vector and get the pointer to store it in the object
	std::vector<std::string>* out = new std::vector<std::string>();
	for (const auto& line : lines)
	{
		out->push_back(line);
	}
	mem.addVar(scopeName + '.' + name, FUNC, out);	// add object to mem
}






// when value has been given to the funciton it will be assigned
// e.g. int example(int arg = 5) { when you call example(2) arg will be 2
void Functions::assignArgValue(Memory& mem, const std::string& funcName, const std::string& scopeName,
	std::vector<std::string>& doneArgs, const size_t varIndex, std::string& arg)
{
	const std::string innerScopeName = scopeName + '.' + funcName;
	//const std::string innerScopeName = mem.getDeepestName(funcName, scopeName);
	const size_t index = arg.find(':');
	std::string argName;
	std::string value;
	if (index > arg.length())
	{
		// if the argName has been specified e.g. example(i: 5)
		argName = mem.getFuncHeader(funcName, scopeName)[varIndex];
		value = VariableHandler::getAsString(mem, arg, mem.getType(argName, innerScopeName), scopeName);
	}
	else
	{
		// if the argName has NOT been specified e.g. example(5)
		argName = arg.substr(0, index);
		value = VariableHandler::getAsString(mem, arg.substr(index + 1), mem.getType(argName, innerScopeName), scopeName);
	}
	SimpleDTs::numericAssign(mem, argName, value, innerScopeName);
	doneArgs.push_back(argName);	// mark argument as done
}



// iterate through the given arguments and assign the values
void Functions::assignAllGivenArgValues(Memory& mem, const std::string& funcName, const std::string& scopeName, const std::string& argString,
	std::vector<std::string>& doneArgs)
{
	std::vector<std::string> args = StringEditor::split(argString, ',');
	for (size_t i = 0; i < args.size(); i++)
	{
		assignArgValue(mem, funcName, scopeName, doneArgs, i, args[i]);
	}
}



// when default values are set in the function header these will be called
// e.g. int example(int arg = 5) { when you call example() arg will be 5
void Functions::assignAllDefaultArgValues(Memory& mem, const std::string& funcName, const std::string& scopeName,
	std::vector<std::string> doneArgs)
{
	const std::string innerScopeName = scopeName + '.' + funcName;
	std::vector<std::string> header = mem.getFuncHeader(funcName, scopeName);	// get order of the arguments
	for (size_t i = 0; i < header.size(); i++)
	{
		std::string& argName = header[i];
		if (std::find(doneArgs.begin(), doneArgs.end(), argName) == doneArgs.end())	// if doneArgs contains argName
		{
			// evaluate and assign
			std::string value = VariableHandler::getAsString(mem, mem.getFuncInits(funcName, scopeName)[i],
			                                                 mem.getType(argName, innerScopeName), scopeName);
			SimpleDTs::numericAssign(mem, argName, value, innerScopeName);
		}
	}
}




// assign values to the argument-variables and then interpret the lines belonging to the function
void Functions::callFunc(Memory& mem, const std::string& funcName, const std::string& scopeName, void* location, const std::string& argString)
{
	std::vector<std::string> doneArgs;
	if (argString.length() > 0)
	{
		assignAllGivenArgValues(mem, funcName, scopeName, argString, doneArgs);
	}
	if (doneArgs.size() < mem.getFuncHeader(funcName, scopeName).size())
	{
		assignAllDefaultArgValues(mem, funcName, scopeName, doneArgs);
	}
	Functions::callFunc(mem, funcName, scopeName, location);
}





// interpret the lines belonging to the function
void Functions::callFunc(Memory& mem, const std::string& funcName, const std::string& scopeName, void* location)
{
	Reader r(mem, scopeName + '.' + funcName);
	//Reader r(mem, mem.getDeepestName(funcName, scopeName));
	std::vector<std::string> lines = *(std::vector<std::string>*)location;
	for (const std::string& line : lines)
	{
		r.interpret(line);
	}
}