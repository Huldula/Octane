#include "Reader.h"
#include <iostream>
#include "Timer.h"

class Test
{
public:
	int x, y;
};

class Child : Test
{
};

int main() {
	{
		Timer mainTimer;
		Reader r;
		r.start();
	}

	std::vector<Test> tests;
	Child c;
	Test t;
	tests.push_back(c);


	std::cin.get();
	return 0;
}