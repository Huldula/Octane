#include "Reader.h"
#include <iostream>
#include "Timer.h"

int main() {
	//int* i = new int(5);
	//int pi = (int)i;
	//long pl = (long)i;
	//std::cout << i << std::endl;
	//std::cout << pi << std::endl;
	//std::cout << pl << std::endl;
	//std::cout << *(int*)pl << std::endl;

	//long long l = *(new long long(1));
	//std::cout << l << std::endl;
	//int p = (int)&l;
	//std::cout << sizeof(int) << std::endl;
	//std::cout << sizeof(long long) << std::endl;

	//for (int i = p; i < p+8; i++)
	//{
	//	bool l0 = *(bool*)i;
	//	std::cout << l0 << std::endl;
	//}
	{
		Timer mainTimer;
		Reader r;
		r.start();
	}

	std::cin.get();
	return 0;
}