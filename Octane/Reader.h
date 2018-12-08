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

private:
	Memory mem;

	static const std::string simpleDT;
	static const std::string mathExpression;

	static const std::regex rePrint;
	static const std::regex reNumericInit;
	static const std::regex reNumericAssign;

	static const std::regex reString;

};

