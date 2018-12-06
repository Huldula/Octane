#include "Reader.h"
#include "StringEditor.h"
#include <fstream>
#include <iostream>
#include "typevalues.cpp"
#include "MathSolver.h"

const std::string Reader::varName("[a-zA-Z_]\\w*");
const std::regex Reader::reIsVar("[^\\w]?(" + Reader::varName + ")[^\\w]?");

const std::regex Reader::rePrintString("print *?\\(\"(.*)\"\\)");
const std::regex Reader::rePrintVar("print *?\\((.*)\\)");
const std::regex Reader::rePrint("print *?\\((.*)\\)");
const std::regex Reader::reNumericInit("(int|long|float|double) *?(" + varName + R"()(?: *?= *?(-?\d+(?:\.?\d*)))?)");

const std::regex Reader::reString("\".*\"");


Reader::Reader()
= default;


Reader::~Reader()
= default;


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

void Reader::interpret(const std::string& s)
{
	std::cout << s << std::endl;

	std::smatch matches;

	if (std::regex_match(s, matches, rePrint)) {
		std::cout << get_as_string(matches[1]) << std::endl;
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

std::string Reader::get_as_string(std::string s)
{
	if (s._Starts_with("\"") && s.find('"', 1) == s.length() - 1)
		return s;

	int type = -1;
	std::smatch matches;
	while (std::regex_search(s, matches, reIsVar))
	{
		const int index = s.find(matches[1]);
		const Object var = mem.getVar(matches[1]);
		if (type == -1)
			type = var.type;
		std::string val;
		#define TO_STRING(type) val = std::to_string(*(type*)var.location);
		SWITCH(var.type, TO_STRING, EMPTY);
		s.replace(index, matches[1].length(), val);
	}

	#define MATH_SOLVE(type) { \
			MathSolver<type> solver; \
			s = std::to_string(solver.solve(s)); \
			break; \
		}

	SWITCH(type, MATH_SOLVE, return s;);
	return s;
}

void Reader::numericInit(std::smatch &matches)
{
	std::string val = "0";
	if (matches.size() > 3 && matches[3].length() > 0)
		val = matches[3];

	if (!matches[1].compare("int")) {
		mem.addVar(matches[2], INT, new int(std::stoi(val)));
	}
	else if (!matches[1].compare("long")) {
		mem.addVar(matches[2], LONG, new long(std::stol(val)));
	}
	else if (!matches[1].compare("float")) {
		mem.addVar(matches[2], FLOAT, new float(std::stof(val)));
	}
	else if (!matches[1].compare("double")) {
		mem.addVar(matches[2], DOUBLE, new double(std::stod(val)));
	}
}

void Reader::printVar(std::smatch &matches)
{
	std::cout << std::to_string(*(short*)mem.getLocation(matches[1])) << std::endl;
}

void Reader::printString(std::smatch &matches)
{
	std::cout << matches[1] << std::endl;
}