#pragma once

#include <string>
#include "Reader.h"

template <typename T>
class MathSolver
{
public:
	MathSolver();
	~MathSolver();
	T solve(std::string in);
private:
	const char* expressionToParse;
	char peek() const;
	char get();
	T number();
	T factor();
	T term();
	T expression();
};

