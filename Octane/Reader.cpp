#include "Reader.h"
#include "StringEditor.h"
#include <sstream>
#include <fstream>
#include <iterator>
#include <iostream>
#include "typevalues"

<<<<<<< HEAD
const std::string Reader::varName("[a-zA-Z][a-zA-Z0-9]*");
const std::regex Reader::rePrint("print *?\\(\"(.*)\"\\)");
const std::regex Reader::reNumericInit("(int|long|float|double) *?(" + varName + ") *?(?:= *?(\\d+))?");
=======
const std::string Reader::varName("[a-zA-Z_][a-zA-Z_0-9]*");
const std::regex Reader::rePrintString("print *?\\(\"(.*)\"\\)");
const std::regex Reader::rePrintVar("print *?\\((.*)\\)");
const std::regex Reader::reNumericInit("(int|long|float|double) *?(" + varName + ")(?: *?= *?(-?\\d+(?:\\.?\\d*)))?");
>>>>>>> 8449dfaed9c76139c16a8d5f59d012ec637f20a1

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
	//if (!s.compare("print")) {
	//	Interpreter::print(s);
	//}
	std::smatch matches;

	if (std::regex_match(s, matches, rePrintString)) {
		std::cout << matches[1] << std::endl;
	}
	else if (std::regex_match(s, matches, rePrintVar)) {
		std::variant<int, long, float, double, bool> *temp = &allObjects[nameLocations[matches[1]]];
		switch (temp->index())
		{
		case INT:
			std::cout << std::get<int>(*temp) << std::endl;
			break;
		case LONG:
			std::cout << std::get<long>(*temp) << std::endl;
			break;
		case FLOAT:
			std::cout << std::get<float>(*temp) << std::endl;
			break;
		case DOUBLE:
			std::cout << std::get<double>(*temp) << std::endl;
			break;
		}
	}
	else if (std::regex_match(s, matches, reNumericInit)) {
<<<<<<< HEAD
		std::cout << "yeit" << std::endl;
		allNames.push_back(matches[2]);
		double num = 0;
		if (!matches[2].compare(""))
			num = std::stod(matches[3]);
		else if (!matches[1].compare("int"))
			temp = (int)num;
		else if (!matches[1].compare("long"))
			temp = (long)num;
		else if (!matches[1].compare("float"))
			temp = (float)num;

		std::cout << std::get<int>(temp) << std::endl;
		if (std::holds_alternative<int>(temp))
			std::cout << "the variant holds an int!\n";
		else if (std::holds_alternative<float>(temp))
			std::cout << "the variant holds a float\n";
		else if (std::holds_alternative<std::string>(temp))
			std::cout << "the variant holds a string\n";
=======
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
		nameLocations[matches[2]] = allObjects.size()-1;
>>>>>>> 8449dfaed9c76139c16a8d5f59d012ec637f20a1
	}
}