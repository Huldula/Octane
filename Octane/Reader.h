#pragma once

#include "Memory.h"
#include <string>
#include <regex>
#include "MathSolver.h"


class Reader
{
public:
	Reader();
	~Reader();
	void start();
	void interpret(const std::string& s);

	std::string getAsString(std::string s);

	void numericInit(std::smatch &matches);
	void numericAssign(std::smatch &matches);
	void printVar(std::smatch &matches);
	static void printString(std::smatch &matches);

private:
	Memory mem;

	static const std::string varName;
	static const std::string simpleDT;
	static const std::string mathExpression;
	static const std::regex reIsVar;
	static const std::regex reIsNumber;

	static const std::regex rePrintString;
	static const std::regex rePrintVar;
	static const std::regex rePrint;
	static const std::regex reNumericInit;
	static const std::regex reNumericAssign;

	static const std::regex reString;

};

