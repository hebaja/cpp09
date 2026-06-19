#include "RPN.hpp"
#include <cctype>
#include <iostream>
#include <stdexcept>
#include <string>

bool	validateToken(std::string::iterator &next, std::string::iterator end)
{
	++next;
	if (next != end && *next != ' ')
	{
		std::cerr << "Error: malformed RPN expression" << std::endl;
		return (false);
	}
	return (true);
}

int	main(int argc, char **argv)
{
	if (argc == 2)
	{
		std::string	input = argv[1];
		RPN	rpn;
		std::string		oper = "+-*/";

		try {
			for (std::string::iterator it = input.begin(); it != input.end(); ++it)
			{
				std::string::iterator	next = it;
				if (std::isdigit(static_cast<unsigned char>(*it)))
				{
					if (!validateToken(next, input.end()))
						return (1);
					rpn.add(*it);
				}
				else if (oper.find_first_of(*it) != std::string::npos)
				{
					if (!validateToken(next, input.end()))
						return (1);
					rpn.calculate(*it);
				}
				else if (*it == ' ')
					continue ;
				else
				{
					std::cerr << "Error: invalid character" << std::endl; 
					return (1);
				}
			}
			rpn.showResult();
		} catch (std::runtime_error &e) {
			std::cerr << e.what() << std::endl;
		}
	}
	else
		std::cerr << "you must input an RPN expression" << std::endl;
	return (0);
}
