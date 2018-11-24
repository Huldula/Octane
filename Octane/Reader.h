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

private:
	std::map<std::string, int> nameLocations;
	std::vector<std::variant<int, long, float, double, bool>> allObjects;

	static const std::string varName;
	static const std::regex rePrintString;
	static const std::regex rePrintVar;
	static const std::regex reNumericInit;
};

