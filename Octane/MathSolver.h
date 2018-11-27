#pragma once

#include <string>

class MathSolver
{
public:
	MathSolver();
	~MathSolver();
	int solve(std::string in);
private:
	char peek();
	char get();
	int number();
	int factor();
	int term();
	int expression();

};

