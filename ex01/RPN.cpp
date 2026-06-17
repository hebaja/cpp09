#include "RPN.hpp"

RPN::RPN() : _exp() {}

RPN::~RPN() {}

void	RPN::add(char &c)
{
	unsigned int	num;
	
	num = static_cast<unsigned int>(static_cast<unsigned int>(c)) - 48;
	_exp.push(num);
}

void	RPN::calculate(char &c)
{
	unsigned int	a;
	unsigned int	b;
	unsigned int	res;
	
	a = _exp.top();
	_exp.pop();
	b = _exp.top();
	_exp.pop();
	switch (c) {
		case '+':
			res = a + b;
			break ;
		case '-':
			if (b > a)
				res = b - a;
			else
				res = a - b;
			break ;
		case '*':
			res = a * b;
			break ;
		case '/':
			res = a / b;
			break ;
	}
	_exp.push(res);
}

unsigned int	RPN::getResult()
{
	return (_exp.top());
}
