#pragma once

#include "Object.h"
#include <vector>
#include <variant>
#include <string>
#include <regex>
#include <map>
#include "MathSolver.h"


class Reader
{
public:
	Reader();
	~Reader();
	void start();
	void interpret(std::string s);

	std::string getAsString(std::string s);

	void numericInit(std::smatch &matches);
	void printVar(std::smatch &matches);
	void printString(std::smatch &matches);

private:
	char* mem;
	int pointer;
	std::map<std::string, Object> nameLocations;


	static const std::string varName;
	static const std::regex reIsVar;

	static const std::regex rePrintString;
	static const std::regex rePrintVar;
	static const std::regex rePrint;
	static const std::regex reNumericInit;

	static const std::regex reString;
};

