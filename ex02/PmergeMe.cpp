#include "PmergeMe.hpp"
#include <algorithm>
#include <ctime>
#include <iomanip>
#include <sys/time.h>
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

std::deque<unsigned int> convertToDeque(int argc, char **argv)
{
	int							tmp;
	std::string					str;
	std::deque<unsigned int>	numbers;

	str = stringfy(argc, argv);
	if (str.find_last_not_of("0123456789 ") != std::string::npos)
		throw std::runtime_error("Error");
	std::stringstream	iss(str);
	while (iss >> tmp)
		numbers.push_back(tmp);
	return (numbers);
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

std::vector<unsigned int> buildJacobsthal(unsigned int n)
{
    std::vector<unsigned int> jacobsthal;
    jacobsthal.push_back(0);
    jacobsthal.push_back(1);
    while (jacobsthal.back() < n)
        jacobsthal.push_back(jacobsthal[jacobsthal.size() - 1] + 2 * jacobsthal[jacobsthal.size() - 2]);
    return (jacobsthal);
}

void	insertPending(std::vector<unsigned int> &pending, std::vector<unsigned int> &winners, std::vector<unsigned int> &jacobsthal)
{
	for (std::vector<unsigned int>::iterator it = jacobsthal.begin(); it != jacobsthal.end(); ++it)
	{
		unsigned int idx = *it;
		if (idx == 0 || idx > pending.size())
			continue;
		std::vector<unsigned int>::iterator pos = std::lower_bound(winners.begin(), winners.end(), pending[idx - 1]);
		winners.insert(pos, pending[idx - 1]);
		pending.erase(pending.begin() + (idx - 1));
	}
}

void	insertPendingRest(std::vector<unsigned int> &pending, std::vector<unsigned int> &winners)
{
	for (std::vector<unsigned int>::iterator it = pending.begin(); it != pending.end(); ++it)
	{
		std::vector<unsigned int>::iterator pos = std::lower_bound(winners.begin(), winners.end(), *it);
		winners.insert(pos, *it);
	}
}

std::vector<unsigned int> doFordJonhson(std::vector<unsigned int> list)
{
	std::vector<unsigned int> winners;
	std::vector<unsigned int> losers;
	std::vector<unsigned int> jacobsthal;
	std::vector<unsigned int> pending;

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
	pending = losers;
	jacobsthal = buildJacobsthal(pending.size());

	insertPending(pending, winners, jacobsthal);
	insertPendingRest(pending, winners);

	if (hasStraggler)
	{
		std::vector<unsigned int>::iterator pos = std::lower_bound(winners.begin(), winners.end(), straggler);
		winners.insert(pos, straggler);
	}
	return (winners);
}

template <typename T>
void	showList(T list)
{
	typename T::iterator last = list.end(); 
	--last;
	for (typename T::iterator it = list.begin(); it != list.end(); ++it) {
		std::cout << *it;
		if (it != last)
			std::cout << " ";
	}
	std::cout << std::endl;
}

PmergeMe::PmergeMe() : _alist(), _blist() {}

PmergeMe::PmergeMe(int argc, char **argv) : _alist(convertToVector(argc, argv)), _blist(convertToDeque(argc, argv)) {}

PmergeMe::PmergeMe(const PmergeMe &other) : _alist(other._alist), _blist(other._blist) {}

PmergeMe &PmergeMe::operator=(const PmergeMe &other)
{
	if (this != &other)
	{
		this->_alist = other._alist;
		this->_blist = other._blist;
	}
	return (*this);
}

PmergeMe::~PmergeMe(){}

void	PmergeMe::showBeforeSort()
{
	std::cout << "Before: ";
	showList(_alist);
}

void	PmergeMe::showAfterSort()
{
	double						us;
	struct timespec				ts_start, ts_end;
	std::vector<unsigned int>	asorted;

	clock_gettime(CLOCK_MONOTONIC, &ts_start);
	asorted = doFordJonhson(_alist);
	clock_gettime(CLOCK_MONOTONIC, &ts_end);

	std::cout << "After:  ";
	showList(asorted);
	us = (ts_end.tv_sec - ts_start.tv_sec) + (ts_end.tv_nsec - ts_start.tv_nsec) / 1e9;

	std::cout << "Time to process a range of " << asorted.size() << " elements with std::vector : " <<
	std::fixed << std::setprecision(6) << us << " us" << std::endl;



	

}
