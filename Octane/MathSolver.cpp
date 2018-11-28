#include "MathSolver.h"
#include <iostream>
#include "typevalues"


MathSolver::MathSolver()
{
}


MathSolver::~MathSolver()
{
}

char MathSolver::peek()
{
	return *expressionToParse;
}

char MathSolver::get()
{
	return *expressionToParse++;
}

int MathSolver::intNumber()
{
	int result = get() - '0';
	while (peek() >= '0' && peek() <= '9')
	{
		result = 10 * result + get() - '0';
	}
	return result;
}

int MathSolver::intFactor()
{
	if (peek() >= '0' && peek() <= '9')
		return intNumber();
	else if (peek() == '(')
	{
		get(); // '('
		int result = intExpression();
		get(); // ')'
		return result;
	}
	else if (peek() == '-')
	{
		get();
		return -intFactor();
	}
	return 0; // error
}

int MathSolver::intTerm()
{
	int result = intFactor();
	while (peek() == '*' || peek() == '/')
		if (get() == '*')
			result *= intFactor();
		else
			result /= intFactor();
	return result;
}

int MathSolver::intExpression()
{
	int result = intTerm();
	while (peek() == '+' || peek() == '-')
		if (get() == '+')
			result += intTerm();
		else
			result -= intTerm();
	return result;
}

std::variant<int, long, float, double, bool> MathSolver::solve(std::string in, int type)
{
	expressionToParse = in.data();
	int result = intExpression();

	return result;
}