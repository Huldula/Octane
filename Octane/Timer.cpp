#include "Timer.h"



Timer::Timer()
{
	start = std::chrono::high_resolution_clock::now();
	name = "";
}

Timer::Timer(std::string name)
{
	this->name = name + " ";
}


Timer::~Timer()
{
	stop();
}

void Timer::stop()
{
	duration = std::chrono::high_resolution_clock::now() - start;

	float ms = duration.count() * 1000.0f;
	std::cout << "Timer " << name.data() << "took " << ms << "ms" << std::endl;
}