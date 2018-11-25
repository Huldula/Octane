#include "Reader.h"
#include "StringEditor.h"
#include <sstream>
#include <fstream>
#include <iterator>
#include <iostream>
#include "typevalues"

const std::string Reader::varName("[a-zA-Z_][a-zA-Z_0-9]*");
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
	switch (temp.index())
	{
	case INT:
		std::cout << std::get<int>(temp) << std::endl;
		break;
	case LONG:
		std::cout << std::get<long>(temp) << std::endl;
		break;
	case FLOAT:
		std::cout << std::get<float>(temp) << std::endl;
		break;
	case DOUBLE:
		std::cout << std::get<double>(temp) << std::endl;
		break;
	}
}

void Reader::printString(std::smatch &matches)
{
	std::cout << matches[1] << std::endl;
}
