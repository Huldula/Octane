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
	std::string test = "Hallo ich bin nicht Leo.";
	std::cout << test.find("ich") << std::endl;



	std::ifstream input("Resources/helloWorld.oc");
	std::string line;
	std::cout << "starting" << std::endl;

	while (std::getline(input, line))
	{
		StringEditor::trim(line);

		std::string words[1];
	}
}
