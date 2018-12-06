#pragma once

#include <chrono>
#include <iostream>

class Timer
{
public:
	Timer();
	Timer(const std::string& name);
	~Timer();
	void stop();
private:
	std::chrono::time_point<std::chrono::steady_clock> start;
	std::chrono::duration<float> duration;

	std::string name;
};

