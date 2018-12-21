#include "Functions.h"
#include "StringEditor.h"
#include <regex>
#include "Reader.h"
#include "SimpleDTs.h"
#include <iostream>


Functions::Functions()
= default;


Functions::~Functions()
= default;


void Functions::funcInit(Memory& mem, const std::string& name, const std::string& args,
	std::vector<std::string> lines, const std::string& scopeName)
{
	std::vector<std::string> varInits = StringEditor::split(args, ',');
	for (auto& varInit : varInits)
	{
		StringEditor::trim(varInit);
		std::smatch matches;
		if (std::regex_match(varInit, matches, Reader::reNumericInit))
		{
			SimpleDTs::numericInit(mem, matches[1], name + "." + std::string(matches[2]), "0", scopeName);
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


void Functions::callFunc(Memory& mem, const std::string& name, const std::string& scopeName, void* location)
{
	Reader r(mem, scopeName + '.' + name);
	std::vector<std::string> lines = *(std::vector<std::string>*)location;
	for (const auto& line : lines)
	{
		r.interpret(line);
	}
}