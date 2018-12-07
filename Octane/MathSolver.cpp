#include "MathSolver.h"
#include <complex>

template class MathSolver<int>;
template class MathSolver<long>;
template class MathSolver<float>;
template class MathSolver<double>;
template class MathSolver<char>;
template class MathSolver<short>;

template <typename T>
MathSolver<T>::MathSolver()
= default;


template <typename T>
MathSolver<T>::~MathSolver()
= default;

template <typename T>
char MathSolver<T>::peek() const
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
		result = 10 * result + get() - '0';
	if (peek() == '.')
	{
		get();
		int fp = 1;
		while (peek() >= '0' && peek() <= '9')
			result += (get() - '0') / std::pow(10, fp++);
	}
	return result;
}

template <typename T>
T MathSolver<T>::factor()
{
	while (peek() == ' ')
		get();
	if (peek() >= '0' && peek() <= '9')
		return number();
	if (peek() == '(')
	{
		get(); // '('
		T result = expression();
		get(); // ')'
		return result;
	}
	if (peek() == '-')
	{
		get();
		return -factor();
	}
	throw 1000;
}

template <typename T>
T MathSolver<T>::term()
{
	T result = factor();
	while (peek() == ' ')
		get();
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
	while (peek() == ' ')
		get();
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