#include "Reader.h"
#include <iostream>
#include "Timer.h"

int main() {
	std::cout << "Test Branch" << std::endl;
	{
		Timer mainTimer;
		Reader r;
		r.start();
	}

	std::cin.get();
	return 0;
}