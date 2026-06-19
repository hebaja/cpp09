#include "RPN.hpp"
#include <cctype>
#include <iostream>
#include <stdexcept>
#include <string>

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
				if (std::isdigit(static_cast<unsigned char>(*it)))
					rpn.add(*it);
				else if (oper.find_first_of(*it) != std::string::npos)
					rpn.calculate(*it);
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
