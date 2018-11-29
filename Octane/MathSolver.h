#pragma once

#include <string>
#include <variant>
#include "Reader.h"

template <typename T>
class MathSolver
{
public:
	MathSolver();
	~MathSolver();
	T solve(std::string in);
private:
	char *expressionToParse;
	char peek();
	char get();
	T number();
	T factor();
	T term();
	T expression();
	//long longNumber();
	//long longFactor();
	//long longTerm();
	//long longExpression();
	//float floatNumber();
	//float floatFactor();
	//float floatTerm();
	//float floatExpression();
	//double doubleNumber();
	//double doubleFactor();
	//double doubleTerm();
	//double doubleExpression();

};

