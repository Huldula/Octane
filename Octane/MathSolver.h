#pragma once

#include <string>
#include <variant>

class MathSolver
{
public:
	MathSolver();
	~MathSolver();
	std::variant<int, long, float, double, bool> solve(std::string in, int type);
private:
	char *expressionToParse;
	char peek();
	char get();
	int intNumber();
	int intFactor();
	int intTerm();
	int intExpression();
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

