#include "StringEditor.h"
#include <algorithm>
#include <cctype>



StringEditor::StringEditor()
{
}


StringEditor::~StringEditor()
{
}

static inline void ltrim(std::string &s) {
	s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) {
		return !std::isspace(ch);
	}));
}

static inline void rtrim(std::string &s) {
	s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) {
		return !std::isspace(ch);
	}).base(), s.end());
}

void StringEditor::trim(std::string &s)
{
	ltrim(s);
	rtrim(s);
}

int StringEditor::indexOf(std::string s, char c)
{
	return -1;
}

void StringEditor::split(std::string &s, char c, std::string a[])
{

}