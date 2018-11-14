#pragma once
#include <string>
#include <vector>

class StringEditor
{
public:
	StringEditor();
	~StringEditor();
	static void trim(std::string &s);
	static std::vector<std::string> split(std::string s, char c);
};

