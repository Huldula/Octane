#pragma once

#include "Object.h"
#include <vector>
#include <variant>
#include <string>
#include <regex>
#include <map>


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
	std::string variantToString(std::variant<int, long, float, double, bool> &var);
	void printString(std::smatch &matches);

private:
	std::map<std::string, int> nameLocations;
	std::vector<std::variant<int, long, float, double, bool>> allObjects;
	std::variant<int, long, float, double, bool> getValue(std::string s);

	static const std::string varName;
	static const std::regex reIsVar;

	static const std::regex rePrintString;
	static const std::regex rePrintVar;
	static const std::regex rePrint;
	static const std::regex reNumericInit;

	static const std::regex reString;
};

