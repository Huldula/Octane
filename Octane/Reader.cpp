#include "Reader.h"
#include "StringEditor.h"
#include <sstream>
#include <fstream>
#include <iterator>
#include <iostream>

const std::string varName = "[a-zA-Z_][a-zA-Z_0-9]*";
const std::regex Reader::rePrint("print *?\\(\"(.*)\"\\)");
const std::regex Reader::reNumericInit("(int|long|float|double) *?(" + varName + ")(?:= *?(\\d+))");

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

		interpret(line);
	}
}

void Reader::interpret(std::string s)
{
	//if (!s.compare("print")) {
	//	Interpreter::print(s);
	//}
	std::smatch matches;

	if (std::regex_match(s, matches, rePrint)) {
		std::cout << matches[1] << std::endl;
	}
	else if (std::regex_match(s, matches, reNumericInit)) {
		allNames.push_back(matches[2]);
		double num = 0;
		if (matches.length() > 3)
			num = std::stod(matches[3]);
		else if (!matches[1].compare("int"))
			temp = (int)num;
		else if (!matches[1].compare("long"))
			temp = (long)num;
		else if (!matches[1].compare("float"))
			temp = (float)num;

		std::cout << temp.index << std::endl;
	}
}