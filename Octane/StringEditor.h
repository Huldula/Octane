#pragma once
#include <string>
#include <vector>

class StringEditor
{
public:
	StringEditor();
	~StringEditor();
	static void trim(std::string &s);
	static std::vector<std::string> split(const std::string& s, char c);
	static std::vector<std::string> split(const std::string& s, const std::string& c);
	static std::string replace(const std::string& s, const std::string& toReplace, const std::string& replacement);
};

