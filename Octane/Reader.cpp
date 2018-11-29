#include "Reader.h"
#include "StringEditor.h"
#include <sstream>
#include <fstream>
#include <iterator>
#include <iostream>
#include "typevalues"

const std::string Reader::varName("[a-zA-Z_]\\w*");
const std::regex Reader::reIsVar("[^\\w]?(" + Reader::varName + ")[^\\w]?");

const std::regex Reader::rePrintString("print *?\\(\"(.*)\"\\)");
const std::regex Reader::rePrintVar("print *?\\((.*)\\)");
const std::regex Reader::rePrint("print *?\\((.*)\\)");
const std::regex Reader::reNumericInit("(int|long|float|double) *?(" + varName + ")(?: *?= *?(-?\\d+(?:\\.?\\d*)))?");

const std::regex Reader::reString("\".*\"");


Reader::Reader()
{
	mem = (char*)malloc(10000);
}


Reader::~Reader()
{
}


void Reader::start() 
{
	std::ifstream input("Resources/helloWorld.oc");
	std::string line;
	std::cout << "starting" << std::endl;

	while (std::getline(input, line))
	{
		StringEditor::trim(line);

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

	int type = -1;
	std::smatch matches;
	while (std::regex_search(s, matches, reIsVar))
	{
		int index = s.find(matches[1]);
		Object &var = nameLocations[matches[1]];
		if (type == -1)
			type = var.type;
		s.replace(index, matches[1].length(), std::to_string(mem[(long long)var.location]));
	}
	
	switch (type)
	{
	case INT:
	{
		MathSolver<int> solver;
		s = std::to_string(solver.solve(s));
		break;
	}
	case LONG:
	{
		MathSolver<long> solver;
		s = std::to_string(solver.solve(s));
		break;
	}
	case FLOAT:
	{
		MathSolver<float> solver;
		s = std::to_string(solver.solve(s));
		break;
	}
	case DOUBLE:
	{
		MathSolver<double> solver;
		s = std::to_string(solver.solve(s));
		break;
	}
	default:
		return s;
	}
	return s;
}

void Reader::numericInit(std::smatch &matches)
{
	Object obj;
	std::string val = "0";
	if (matches.size() > 3 && matches[3].length() > 0)
		val = matches[3];

	if (!matches[1].compare("int")) {
		(mem)[pointer] = std::stoi(val);
		obj.type = INT;
		obj.location = (char*)pointer;
		pointer += sizeof(int);
	}
	else if (!matches[1].compare("long")) {
		(mem)[pointer] = std::stol(val);
		obj.type = LONG;
		obj.location = (char*)pointer;
		pointer += sizeof(long long);
	}
	else if (!matches[1].compare("float")) {
		(mem)[pointer] = std::stof(val);
		obj.type = FLOAT;
		obj.location = (char*)pointer;
		pointer += sizeof(float);
	}
	else if (!matches[1].compare("double")) {
		(mem)[pointer] = std::stod(val);
		obj.type = DOUBLE;
		obj.location = (char*)pointer;
		pointer += sizeof(double);
	}

	nameLocations[matches[2]] = obj;
	std::cout << pointer << std::endl;
}

void Reader::printVar(std::smatch &matches)
{
	std::cout << std::to_string(*(char*)nameLocations[matches[1]].location) << std::endl;
}

//std::string Reader::variantToString(std::variant<int, long, float, double, bool> &var)
//{
//	switch (var.index())
//	{
//	case INT:
//		return std::to_string(std::get<int>(var));
//	case LONG:
//		return std::to_string(std::get<long>(var));
//	case FLOAT:
//		return std::to_string(std::get<float>(var));
//	case DOUBLE:
//		return std::to_string(std::get<double>(var));
//	}
//}

void Reader::printString(std::smatch &matches)
{
	std::cout << matches[1] << std::endl;
}