#include "Reader.h"
#include "StringEditor.h"
#include <sstream>
#include <fstream>
#include <string>
#include <iterator>
#include <iostream>


Reader::Reader()
{
}


Reader::~Reader()
{
}


void Reader::start() 
{
	std::ifstream input("Resources/helloWorld.oc");
	std::string line;
	std::cout << "starting" << std::endl;

	while (std::getline(input, line))
	{
		StringEditor::trim(line);
		std::vector<std::string> words = StringEditor::split(line, ' ');

		for (int i = 0; i < words.size(); i++)
		{
			
		}
	}
}
