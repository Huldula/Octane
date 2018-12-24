#include "Reader.h"
#include "StringEditor.h"
#include <fstream>
#include <iostream>
#include <utility>
#include "typevalues.cpp"
#include "VariableHandler.h"
#include "SimpleDTs.h"
#include "Functions.h"

const std::string Reader::simpleDT("(int|long|float|double|char|short)");
//const std::string Reader::mathExpression("(" + Reader::varName + R"(|+|-|\(|\)|\*|/|))");

const std::regex Reader::rePrint("print *?\\((.*)\\)");
const std::regex Reader::reNumericInit(simpleDT + " *?(" + VAR_NAME + R"()(?: *?= *?(.*?))?)");
const std::regex Reader::reNumericAssign("(" + VAR_NAME + R"() *?= *?(.*?))");
const std::regex Reader::reFuncInit("(" + VAR_NAME + ") +?(" + VAR_NAME + R"() *?\((.*)\) *?\{?)");
const std::regex Reader::reFuncCall("(" + VAR_NAME + ") *?\\(.*\\)");


Reader::Reader()
= default;

Reader::Reader(Memory& mem) : mem(mem), scopeName("")
{}

Reader::Reader(Memory& mem, std::string scopeName) : mem(mem), scopeName(std::move(scopeName))
{}

Reader::~Reader()
= default;


void Reader::start()
{
	// start reading the file ~beginning of the program
	std::ifstream input("Resources/helloWorld.oc");
	std::string line;
	std::cout << "starting" << std::endl;

	while (std::getline(input, line))
	{
		line = StringEditor::split(line, "//")[0];	// remove comments
		StringEditor::trimThis(line);	// remove spaces at the beginning and the end of the line

		if (line.length() > 0)
		{
			if (interpreting)
				interpret(line);
			else if (line._Equal("}"))
			{
				// save the function-lines and go along
				// TODO make the read-pointer jump to the function
				Functions::funcInit(mem, tempName, tempArgs, tempLines, scopeName);
				interpreting = true;
				tempLines.clear();
			}
			else
				// add line to current function
				tempLines.push_back(line);
		}
	}
}
// interpret one line at a time
void Reader::interpret(const std::string& s)
{
	std::cout << "~~~~~~~~~~~" << s << std::endl;

	//std::cout << "scopeName Reader::interpret  " << scopeName << std::endl;

	std::smatch matches;

	if (std::regex_match(s, matches, rePrint)) {
		std::cout << VariableHandler::getAsString(mem, matches[1], -1, scopeName) << std::endl;
	}
	else if (std::regex_match(s, matches, reNumericInit)) {
		SimpleDTs::numericInitEval(mem, matches, scopeName);
	}
	else if (std::regex_match(s, matches, reNumericAssign)) {
		SimpleDTs::numericAssignEval(mem, matches, scopeName);
	}
	else if (std::regex_match(s, matches, reFuncInit)) {
		interpreting = false;	// don't interpret the following lines until the funciton ends
		tempName = matches[2];
		tempArgs = matches[3];
	}
	else if (std::regex_match(s, matches, reFuncCall)) {
		//std::cout << "funccall   " << scopeName << std::endl;
		VariableHandler::getAsString(mem, s, -1, scopeName);
	}
	else
	{
		std::cout << "WTF is das: " << s << std::endl;
	}
}