#pragma once
#include <string>

class StringEditor
{
public:
	StringEditor();
	~StringEditor();
	static void trim(std::string &s);
	static int indexOf(std::string s, char c);
	static void split(std::string &s, char c, std::string a[]);
};

