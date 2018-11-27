#include "MathSolver.h"



MathSolver::MathSolver()
{
}


MathSolver::~MathSolver()
{
}

const char * expressionToParse = "3*2+4*1+(4+9)*6";

char MathSolver::peek()
{
	return *expressionToParse;
}

char MathSolver::get()
{
	return *expressionToParse++;
}

int MathSolver::number()
{
	int result = get() - '0';
	while (peek() >= '0' && peek() <= '9')
	{
		result = 10 * result + get() - '0';
	}
	return result;
}

int MathSolver::factor()
{
	if (peek() >= '0' && peek() <= '9')
		return number();
	else if (peek() == '(')
	{
		get(); // '('
		int result = expression();
		get(); // ')'
		return result;
	}
	else if (peek() == '-')
	{
		get();
		return -factor();
	}
	return 0; // error
}

int MathSolver::term()
{
	int result = factor();
	while (peek() == '*' || peek() == '/')
		if (get() == '*')
			result *= factor();
		else
			result /= factor();
	return result;
}

int MathSolver::expression(std::string in)
{
	int result = term();
	while (peek() == '+' || peek() == '-')
		if (get() == '+')
			result += term();
		else
			result -= term();
	return result;
}

int MathSolver::solve(std::string in)
{
	int result = expression(in);

	return 0;
}