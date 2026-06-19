#pragma once

#include <stack>

class RPN
{
private:
	std::stack<int>	_exp;

public:
	RPN();
	RPN(const RPN &other);
	RPN& operator=(const RPN &other);
	~RPN();

	void	add(char &c);
	void	calculate(char &c);
	void	showResult();
};
