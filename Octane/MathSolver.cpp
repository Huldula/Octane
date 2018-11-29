#include "MathSolver.h"
#include <iostream>
#include "typevalues"

template class MathSolver<int>;
template class MathSolver<long>;
template class MathSolver<float>;
template class MathSolver<double>;

template <typename T>
MathSolver<T>::MathSolver()
{
}


template <typename T>
MathSolver<T>::~MathSolver()
{

}

template <typename T>
char MathSolver<T>::peek()
{
	return *expressionToParse;
}

template <typename T>
char MathSolver<T>::get()
{
	return *expressionToParse++;
}

template <typename T>
T MathSolver<T>::number()
{
	T result = get() - '0';
	while (peek() >= '0' && peek() <= '9')
	{
		result = 10 * result + get() - '0';
	}
	return result;
}

template <typename T>
T MathSolver<T>::factor()
{
	if (peek() >= '0' && peek() <= '9')
		return number();
	else if (peek() == '(')
	{
		get(); // '('
		T result = expression();
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

template <typename T>
T MathSolver<T>::term()
{
	T result = factor();
	while (peek() == '*' || peek() == '/')
		if (get() == '*')
			result *= factor();
		else
			result /= factor();
	return result;
}

template <typename T>
T MathSolver<T>::expression()
{
	T result = term();
	while (peek() == '+' || peek() == '-')
		if (get() == '+')
			result += term();
		else
			result -= term();
	return result;
}

template <typename T>
T MathSolver<T>::solve(std::string in)
{
	expressionToParse = in.data();
	return expression();
}