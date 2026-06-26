#include "PmergeMe.hpp"
#include <algorithm>
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

std::vector<Pair> pairing(std::vector<unsigned int> &list)
{
	std::vector<Pair>	pairs;

	for (std::vector<unsigned int>::iterator it = list.begin(); it != list.end(); ++it)
	{
		std::vector<unsigned int>::iterator	next_it = it;
		++next_it;
		if (next_it == list.end())
			continue ;
		Pair p;
		p.a = *it;
		p.b = *next_it;
		pairs.push_back(p);
		++it;
	}
	return (pairs);
}

void	sortPairs(std::vector<Pair> &pairs)
{
	for (std::vector<Pair>::iterator it = pairs.begin(); it != pairs.end(); ++it)
	{
		if (it->a < it->b)
		{
			unsigned int	tmp = it->a;
			it->a = it->b;
			it->b = tmp;
		}
	}
}

std::vector<unsigned int> doJacobsthal(unsigned int n)
{
    std::vector<unsigned int> jacobsthal;
    jacobsthal.push_back(0);
    jacobsthal.push_back(1);
    while (jacobsthal.back() < n)
        jacobsthal.push_back(jacobsthal[jacobsthal.size() - 1] + 2 * jacobsthal[jacobsthal.size() - 2]);
    return (jacobsthal);
}


std::vector<unsigned int> doFordJonhson(std::vector<unsigned int> list)
{
	std::vector<unsigned int> winners;
	std::vector<unsigned int> losers;
	std::vector<unsigned int> jacobsthal;

	if (list.size() <= 1)
		return (list);

	unsigned int straggler = 0;
	bool hasStraggler = (list.size() % 2 != 0);
	if (hasStraggler)
		straggler = list.back();

	std::vector<Pair> pairs = pairing(list);
	sortPairs(pairs);
	for (std::vector<Pair>::iterator it = pairs.begin(); it != pairs.end(); ++it)
	{
		winners.push_back(it->a);
		losers.push_back(it->b);
	}
	winners = doFordJonhson(winners);

	std::vector<unsigned int> pending = losers;
	jacobsthal = doJacobsthal(pending.size());

	for (int i = static_cast<int>(jacobsthal.size()) - 1; i >= 0; --i)
	{
		unsigned int idx = jacobsthal[i];
		if (idx == 0 || idx > pending.size())
			continue;
		std::vector<unsigned int>::iterator pos = std::lower_bound(winners.begin(), winners.end(), pending[idx - 1]);
		winners.insert(pos, pending[idx - 1]);
		pending.erase(pending.begin() + (idx - 1));
	}

	for (int i = static_cast<int>(pending.size()) - 1; i >= 0; --i)
	{
		std::vector<unsigned int>::iterator pos = std::lower_bound(winners.begin(), winners.end(), pending[i]);
		winners.insert(pos, pending[i]);
	}

	if (hasStraggler)
	{
		std::vector<unsigned int>::iterator pos = std::lower_bound(winners.begin(), winners.end(), straggler);
		winners.insert(pos, straggler);
	}

	return (winners);
}

PmergeMe::PmergeMe() : _alist(){}

PmergeMe::PmergeMe(int argc, char **argv) : _alist(convertToVector(argc, argv)), _pairs(pairing(_alist))
{
	std::vector<unsigned int> n = doFordJonhson(_alist);

	for (std::vector<unsigned int>::iterator it = n.begin(); it != n.end(); ++it) {
		std::cout << *it << " ";
	}
	std::cout << std::endl;

}

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
