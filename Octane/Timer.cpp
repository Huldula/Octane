#include "Timer.h"



Timer::Timer(): duration(), name("")
{
	start = std::chrono::high_resolution_clock::now();
}

Timer::Timer(const std::string& name) : duration(), name(name + " ")
{
	start = std::chrono::high_resolution_clock::now();
}


Timer::~Timer()
{
	stop();
}

void Timer::stop()
{
	duration = std::chrono::high_resolution_clock::now() - start;

	const float ms = duration.count() * 1000.0f;
	std::cout << "Timer " << name.data() << "took " << ms << "ms" << std::endl;
}