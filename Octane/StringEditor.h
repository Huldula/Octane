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
	static std::vector<std::string> split(std::string s, std::string c);
	static std::string replace(std::string s, std::string toReplace, std::string replacement);
};

