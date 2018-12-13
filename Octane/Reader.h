#pragma once

#include "Memory.h"
#include <string>
#include <regex>
#include "MathSolver.h"


class Reader
{
public:
	Reader();
	Reader(Memory& mem);
	Reader(Memory& mem, std::string scopeName);
	~Reader();
	void start();
	void interpret(const std::string& s);


	static const std::string simpleDT;
	static const std::string mathExpression;

	static const std::regex rePrint;
	static const std::regex reNumericInit;
	static const std::regex reNumericAssign;
	static const std::regex reFuncInit;
	static const std::regex reFuncCall;
private:
	Memory mem;
	std::string scopeName;

	bool interpreting = true;
	std::string tempName;
	std::string tempArgs;
	std::vector<std::string> tempLines;
};

