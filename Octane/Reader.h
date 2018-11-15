#pragma once

#include <vector>
#include <variant>
#include <string>
#include <regex>


class Reader
{
public:
	Reader();
	~Reader();
	void start();
	void interpret(std::string s);

private:
	std::vector<std::string> allNames;
	std::vector<std::variant<int, long, float, double, bool, std::string>> allObjects;
	std::variant<int, long, float, double, bool, std::string> temp;

	static const std::string varName;
	static const std::regex rePrint;
	static const std::regex reNumericInit;
};

