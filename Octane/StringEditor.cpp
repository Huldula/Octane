#include "StringEditor.h"
#include <algorithm>
#include <cctype>
#include <iostream>



StringEditor::StringEditor()
= default;


StringEditor::~StringEditor()
= default;

static void ltrim(std::string &s) {
	s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](const int ch) {
		return !std::isspace(ch);
	}));
}

static void rtrim(std::string &s) {
	s.erase(std::find_if(s.rbegin(), s.rend(), [](const int ch) {
		return !std::isspace(ch);
	}).base(), s.end());
}

void StringEditor::trim(std::string &s)
{
	ltrim(s);
	rtrim(s);
}

std::vector<std::string> StringEditor::split(const std::string& s, const char c)
{
	std::vector<std::string> list;

	int last = 0, next;
	do {
		next = s.find(c, last);
		list.push_back(s.substr(last, next - last));
		last = next + 1;
	} while (next > 0);

	return list;
}


std::vector<std::string> StringEditor::split(const std::string& s, const std::string& c)
{
	std::vector<std::string> list;

	int last = 0, next;
	do {
		next = s.find(c, last);
		list.push_back(s.substr(last, next - last));
		last = next + 1;
	} while (next > -1);

	return list;
}


std::string StringEditor::replace(const std::string& s, const std::string& toReplace, const std::string& replacement)
{
	std::vector<std::string> list = StringEditor::split(s, toReplace);
	std::string out;

	for (unsigned int i = 0; i < list.size()-1; i++)
	{
		out += list[i] + replacement;
	}
	out += list[list.size() - 1];

	return out;
}