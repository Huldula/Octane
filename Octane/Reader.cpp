#include "Reader.h"
#include "StringEditor.h"
#include <sstream>
#include <fstream>
#include <iterator>
#include <iostream>
#include "typevalues"
#include "MathSolver.h"

const std::string Reader::varName("[a-zA-Z_]\\w*");
const std::regex Reader::reIsVar("[^\\w]?(" + Reader::varName + ")[^\\w]?");

const std::regex Reader::rePrintString("print *?\\(\"(.*)\"\\)");
const std::regex Reader::rePrintVar("print *?\\((.*)\\)");
const std::regex Reader::rePrint("print *?\\((.*)\\)");
const std::regex Reader::reNumericInit("(int|long|float|double) *?(" + varName + ")(?: *?= *?(-?\\d+(?:\\.?\\d*)))?");

const std::regex Reader::reString("\".*\"");


Reader::Reader()
{
}


Reader::~Reader()
{
}


void Reader::start() 
{
	std::variant<int, long, float, double, bool> var = 12345.12345;
	std::string s = "abcdef";
	std::cout << s.replace(1, 3, Reader::variantToString(var)) << std::endl;

	std::ifstream input("Resources/helloWorld.oc");
	std::string line;
	std::cout << "starting" << std::endl;

	while (std::getline(input, line))
	{
		StringEditor::trim(line);
		//std::vector<std::string> words = StringEditor::split(line, ' ');

		//for (int i = 0; i < words.size(); i++)
		//{
		//	interpret(words[i]);
		//}

		if (line.length() > 0)
			interpret(line);
	}
}

void Reader::interpret(std::string s)
{
	std::cout << s << std::endl;

	std::smatch matches;

	if (std::regex_match(s, matches, rePrint)) {
		std::cout << getAsString(matches[1]) << std::endl;
	}
	else if (std::regex_match(s, matches, rePrintString)) {
		printString(matches);
	}
	else if (std::regex_match(s, matches, rePrintVar)) {
		printVar(matches);
	}
	else if (std::regex_match(s, matches, reNumericInit)) {
		numericInit(matches);
	}
}

std::string Reader::getAsString(std::string s)
{
	if (s._Starts_with("\"") && s.find("\"", 1) == s.length() - 1)
		return s;

	std::smatch matches;
	while (std::regex_search(s, matches, reIsVar))
	{
		int index = s.find(matches[1]);
		s.replace(index, matches[1].length(), variantToString(allObjects[nameLocations[matches[1]]]));
	}

	MathSolver solver;
	return std::to_string(solver.solve(s));
	//s = StringEditor::replace(s, " ", "");

	/*std::vector<std::string> adds = StringEditor::split(s, "+");
	for (int i = 0; i < adds.size(); i++)
	{

	}*/

	return s;
}

void Reader::numericInit(std::smatch &matches)
{
	std::variant<int, long, float, double, bool> var;

	if (matches.size() > 3 && matches[3].length() > 0)
	{
		if (!matches[1].compare("int"))
			var = std::stoi(matches[3]);
		else if (!matches[1].compare("double"))
			var = std::stod(matches[3]);
		else if (!matches[1].compare("long"))
			var = std::stol(matches[3]);
		else if (!matches[1].compare("float"))
			var = std::stof(matches[3]);
	}

	allObjects.push_back(var);
	nameLocations[matches[2]] = allObjects.size() - 1;
}

void Reader::printVar(std::smatch &matches)
{
	std::variant<int, long, float, double, bool> &temp = allObjects[nameLocations[matches[1]]];
	variantToString(temp);
}

std::string Reader::variantToString(std::variant<int, long, float, double, bool> &var)
{
	switch (var.index())
	{
	case INT:
		return std::to_string(std::get<int>(var));
	case LONG:
		return std::to_string(std::get<long>(var));
	case FLOAT:
		return std::to_string(std::get<float>(var));
	case DOUBLE:
		return std::to_string(std::get<double>(var));
	}
}

void Reader::printString(std::smatch &matches)
{
	std::cout << matches[1] << std::endl;
}