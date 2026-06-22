#include "PmergeMe.hpp"
#include <sstream>

std::string	stringfy(int argc, char **argv)
{
	std::string	str;

	for (int i = 1; i < argc; ++i)
	{
		if (i > 1)
			str += " ";
		str += argv[i];
	}
	return (str);
}

std::vector<unsigned int> convertToVector(int argc, char **argv)
{
	int							tmp;
	std::string					str;
	std::vector<unsigned int>	numbers;

	str = stringfy(argc, argv);
	if (str.find_last_not_of("0123456789 ") != std::string::npos)
		throw std::runtime_error("Error");
	std::stringstream	iss(str);
	while (iss >> tmp)
		numbers.push_back(tmp);
	return (numbers);
}

PmergeMe::PmergeMe() : _alist(){}

PmergeMe::PmergeMe(int argc, char **argv) : _alist(convertToVector(argc, argv)) {}

PmergeMe::PmergeMe(const PmergeMe &other) : _alist(other._alist) {}

PmergeMe &PmergeMe::operator=(const PmergeMe &other)
{
	if (this != &other)
		this->_alist = other._alist;
	return (*this);
}

PmergeMe::~PmergeMe(){}

void	PmergeMe::showAlist()
{
	for (std::vector<unsigned int>::iterator it = _alist.begin(); it != _alist.end(); ++it) {
		std::cout << *it << " ";
	}
	std::cout << std::endl;
}
