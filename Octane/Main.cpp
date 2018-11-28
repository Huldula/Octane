#include "Reader.h"
#include <iostream>
#include "Timer.h"

int main() {
	{
		Timer mainTimer;
		Reader r;
		r.start();
	}

	std::cin.get();
	return 0;
}