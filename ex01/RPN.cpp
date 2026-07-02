#include "RPN.hpp"
#include <iostream>

RPN::RPN() : _exp() {}

RPN::~RPN() {}

RPN::RPN(const RPN &other) : _exp(other._exp) {}

RPN &RPN::operator=(const RPN &other)
{
	if (this != &other)
		_exp = other._exp;
	return (*this);
}

void RPN::add(char &c)
{
	int num;

	num = static_cast<unsigned int>(static_cast<unsigned int>(c)) - 48;
	_exp.push(num);
}

void RPN::calculate(char &c)
{
	int a;
	int b;
	int res;

	if (_exp.empty())
		throw std::runtime_error("Error: not enough operands");
	a = _exp.top();
	_exp.pop();
	if (_exp.empty())
		throw std::runtime_error("Error: not enough operands");
	b = _exp.top();
	_exp.pop();
	switch (c)
	{
	case '+':
		res = b + a;
		break;
	case '-':
		res = b - a;
		break;
	case '*':
		res = b * a;
		break;
	case '/':
		if (a == 0)
			throw std::runtime_error("Error: division by zero");
		res = b / a;
		break;
	}
	_exp.push(res);
}

void RPN::showResult()
{
	int res;

	res = _exp.top();
	_exp.pop();
	if (!_exp.empty())
		throw std::runtime_error("Error: malformed RPN expression");
	else
		std::cout << res << std::endl;
}
