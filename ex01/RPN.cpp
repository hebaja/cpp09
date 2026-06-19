#include "RPN.hpp"
#include <iostream>
#include <stdexcept>

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

	if (_exp.empty())
		throw std::runtime_error("Error: not enough operands");
	a = _exp.top();
	_exp.pop();
	if (_exp.empty())
		throw std::runtime_error("Error: not enough operands");
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
				throw std::runtime_error("Error: division by zero");
			res = b / a;
			break ;
	}
	_exp.push(res);
}

void	RPN::showResult()
{
	int	res;

	res = _exp.top();
	_exp.pop();
	if (!_exp.empty())
		throw std::runtime_error("Error: malformed RPN expression");
	else
		std::cout << res << std::endl;
}
