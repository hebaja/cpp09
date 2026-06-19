#include "RPN.hpp"
#include <iostream>

RPN::RPN() : _exp() {}

RPN::~RPN() {}

void	RPN::add(char &c)
{
	int	num;
	
	num = static_cast<unsigned int>(static_cast<unsigned int>(c)) - 48;
	_exp.push(num);
}

void	RPN::calculate(char &c)
{
	int	a;
	int	b;
	int	res;
	
	a = _exp.top();
	_exp.pop();
	b = _exp.top();
	_exp.pop();
	switch (c) {
		case '+':
			res = b + a;
			break ;
		case '-':
			res = b - a;
			break ;
		case '*':
			res = b * a;
			break ;
		case '/':
			if (a == 0)
			{
				std::cerr << "Error: division by zero";
				break ;
			}
			res = b / a;
			break ;
	}
	_exp.push(res);
}

unsigned int	RPN::getResult()
{
	return (_exp.top());
}
