#include "PmergeMe.hpp"
#include <algorithm>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <stdexcept>
#include <sys/time.h>

std::string stringfy(int argc, char **argv)
{
	std::string str;

	for (int i = 1; i < argc; ++i)
	{
		if (i > 1)
			str += " ";
		str += argv[i];
	}
	return (str);
}

template <typename T> T convertToContainer(int argc, char **argv)
{
	int tmp;
	std::string str;
	T numbers;

	str = stringfy(argc, argv);
	if (str.find_last_not_of("0123456789 ") != std::string::npos)
		throw std::runtime_error("Error");
	std::stringstream iss(str);
	while (iss >> tmp)
		numbers.push_back(tmp);
	return (numbers);
}

/* *** *** *** *** *** *** ***  */
/* *** VECTOR SECTION START *** */
/* *** *** *** *** *** *** ***  */

std::vector<Pair> vecPairing(UintVec &list)
{
	std::vector<Pair> pairs;

	for (UintVec::iterator it = list.begin(); it != list.end(); ++it)
	{
		UintVec::iterator next_it = it;
		++next_it;
		if (next_it == list.end())
			continue;
		Pair p;
		p.a = *it;
		p.b = *next_it;
		pairs.push_back(p);
		++it;
	}
	return (pairs);
}

void sortVecPairs(std::vector<Pair> &pairs)
{
	for (std::vector<Pair>::iterator it = pairs.begin(); it != pairs.end(); ++it)
	{
		if (it->a < it->b)
		{
			unsigned int tmp = it->a;
			it->a = it->b;
			it->b = tmp;
		}
	}
}

UintVec buildVecJacobsthal(unsigned int n)
{
	UintVec order;
	if (n == 0)
		return order;
	UintVec jacobsthal;
	jacobsthal.push_back(0);
	jacobsthal.push_back(1);
	while (jacobsthal.back() < n)
		jacobsthal.push_back(jacobsthal.back() + 2 * jacobsthal[jacobsthal.size() - 2]);

	for (UintVec::size_type k = 1;; ++k)
	{
		if (jacobsthal[k] > n && jacobsthal[k - 1] >= n)
			break;
		unsigned int high = jacobsthal[k] > n ? n : jacobsthal[k];
		unsigned int low = jacobsthal[k - 1] + 1;
		for (unsigned int j = high; j >= low; --j)
			order.push_back(j);
		if (high == n)
			break;
	}
	return order;
}

UintVec doVecFordJohnson(UintVec list)
{
	UintVec winners;
	UintVec losers;
	UintVec jacobsthal;
	unsigned int straggler;
	bool hasStraggler;
	std::vector<Pair> pairs;

	if (list.size() <= 1)
		return (list);

	straggler = 0;
	hasStraggler = (list.size() % 2 != 0);
	if (hasStraggler)
		straggler = list.back();

	pairs = vecPairing(list);
	sortVecPairs(pairs);

	for (std::vector<Pair>::iterator it = pairs.begin(); it != pairs.end(); ++it)
	{
		winners.push_back(it->a);
		losers.push_back(it->b);
	}

	jacobsthal = buildVecJacobsthal(losers.size());
	std::vector<bool> inserted(pairs.size(), false);

	winners = doVecFordJohnson(winners);

	for (UintVec::iterator it = jacobsthal.begin(); it != jacobsthal.end(); ++it)
	{
		unsigned int idx = *it;
		if (idx == 0 || idx > pairs.size())
			continue;
		unsigned int target = pairs[idx - 1].b;
		unsigned int winner_val = pairs[idx - 1].a;

		UintVec::iterator winner_it = std::lower_bound(winners.begin(), winners.end(), winner_val);
		UintVec::iterator pos = std::lower_bound(winners.begin(), winner_it, target);
		winners.insert(pos, target);
		inserted[idx - 1] = true;
	}

	for (unsigned int i = 0; i < pairs.size(); ++i)
	{
		if (!inserted[i])
		{
			unsigned int target = pairs[i].b;
			unsigned int winner_val = pairs[i].a;
			UintVec::iterator winner_it = std::lower_bound(winners.begin(), winners.end(), winner_val);
			UintVec::iterator pos = std::lower_bound(winners.begin(), winner_it, target);
			winners.insert(pos, target);
		}
	}

	if (hasStraggler)
	{
		UintVec::iterator pos = std::lower_bound(winners.begin(), winners.end(), straggler);
		winners.insert(pos, straggler);
	}
	return (winners);
}

/* *** *** *** *** *** *** *** */
/* *** VECTOR SECTION END ***  */
/* *** *** *** *** *** *** *** */

/* *** *** *** *** *** *** *** */
/* *** DEQUE SECTION START *** */
/* *** *** *** *** *** *** *** */

std::deque<Pair> deqPairing(UintDeq &list)
{
	std::deque<Pair> pairs;

	for (UintDeq::iterator it = list.begin(); it != list.end(); ++it)
	{
		UintDeq::iterator next_it = it;
		++next_it;
		if (next_it == list.end())
			continue;
		Pair p;
		p.a = *it;
		p.b = *next_it;
		pairs.push_back(p);
		++it;
	}
	return (pairs);
}

void sortDeqPairs(std::deque<Pair> &pairs)
{
	for (std::deque<Pair>::iterator it = pairs.begin(); it != pairs.end(); ++it)
	{
		if (it->a < it->b)
		{
			unsigned int tmp = it->a;
			it->a = it->b;
			it->b = tmp;
		}
	}
}

UintDeq buildDeqJacobsthal(unsigned int n)
{
	UintDeq order;
	if (n == 0)
		return order;
	UintDeq jacobsthal;
	jacobsthal.push_back(0);
	jacobsthal.push_back(1);
	while (jacobsthal.back() < n)
		jacobsthal.push_back(jacobsthal.back() + 2 * jacobsthal[jacobsthal.size() - 2]);

	for (UintDeq::size_type k = 1;; ++k)
	{
		if (jacobsthal[k] > n && jacobsthal[k - 1] >= n)
			break;
		unsigned int high = jacobsthal[k] > n ? n : jacobsthal[k];
		unsigned int low = jacobsthal[k - 1] + 1;
		for (unsigned int j = high; j >= low; --j)
			order.push_back(j);
		if (high == n)
			break;
	}
	return order;
}

UintDeq doDeqFordJohnson(UintDeq list)
{
	UintDeq winners;
	UintDeq losers;
	UintDeq jacobsthal;
	unsigned int straggler;
	bool hasStraggler;
	std::deque<Pair> pairs;

	if (list.size() <= 1)
		return (list);

	straggler = 0;
	hasStraggler = (list.size() % 2 != 0);
	if (hasStraggler)
		straggler = list.back();

	pairs = deqPairing(list);
	sortDeqPairs(pairs);

	for (std::deque<Pair>::iterator it = pairs.begin(); it != pairs.end(); ++it)
	{
		winners.push_back(it->a);
		losers.push_back(it->b);
	}

	jacobsthal = buildDeqJacobsthal(losers.size());
	std::vector<bool> inserted(pairs.size(), false);

	winners = doDeqFordJohnson(winners);

	for (UintDeq::iterator it = jacobsthal.begin(); it != jacobsthal.end(); ++it)
	{
		unsigned int idx = *it;
		if (idx == 0 || idx > pairs.size())
			continue;
		unsigned int target = pairs[idx - 1].b;
		unsigned int winner_val = pairs[idx - 1].a;

		UintDeq::iterator winner_it = std::lower_bound(winners.begin(), winners.end(), winner_val);
		UintDeq::iterator pos = std::lower_bound(winners.begin(), winner_it, target);
		winners.insert(pos, target);
		inserted[idx - 1] = true;
	}

	for (unsigned int i = 0; i < pairs.size(); ++i)
	{
		if (!inserted[i])
		{
			unsigned int target = pairs[i].b;
			unsigned int winner_val = pairs[i].a;
			UintDeq::iterator winner_it = std::lower_bound(winners.begin(), winners.end(), winner_val);
			UintDeq::iterator pos = std::lower_bound(winners.begin(), winner_it, target);
			winners.insert(pos, target);
		}
	}

	if (hasStraggler)
	{
		UintDeq::iterator pos = std::lower_bound(winners.begin(), winners.end(), straggler);
		winners.insert(pos, straggler);
	}
	return (winners);
}

/* *** *** *** *** *** *** *** */
/* *** DEQUE SECTION END ***   */
/* *** *** *** *** *** *** *** */

template <typename T> void showList(T list)
{
	typename T::iterator last = list.end();
	--last;
	for (typename T::iterator it = list.begin(); it != list.end(); ++it)
	{
		std::cout << *it;
		if (it != last)
			std::cout << " ";
	}
	std::cout << std::endl;
}

void checkLists(UintVec alist, UintDeq blist, bool isBefore)
{
	if (alist.size() == blist.size() && std::equal(alist.begin(), alist.end(), blist.begin()))
		return;
	throw std::runtime_error(isBefore ? "Error: lists are different" : "Error: lists sorted differently");
}

PmergeMe::PmergeMe() : _alist(), _blist() {}

PmergeMe::PmergeMe(int argc, char **argv)
    : _alist(convertToContainer<UintVec>(argc, argv)), _blist(convertToContainer<UintDeq>(argc, argv))
{
	checkLists(_alist, _blist, true);
}

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

PmergeMe::~PmergeMe() {}

void PmergeMe::showBeforeSort()
{
	std::cout << "Before: ";
	showList(_alist);
}

template <typename T>
void showAfter(T &sortList, struct timespec &ts_start, struct timespec &ts_end, std::string containerName)
{
	double us;

	us = (ts_end.tv_sec - ts_start.tv_sec) + (ts_end.tv_nsec - ts_start.tv_nsec) / 1e9;

	std::cout << "Time to process a range of " << sortList.size() << " elements with " << containerName << " : "
	          << std::fixed << std::setprecision(6) << us << " us" << std::endl;
}

void PmergeMe::showAfterSort()
{
	struct timespec a_ts_start, a_ts_end, b_ts_start, b_ts_end;
	UintVec asorted;
	UintDeq bsorted;

	clock_gettime(CLOCK_MONOTONIC, &a_ts_start);
	asorted = doVecFordJohnson(_alist);
	clock_gettime(CLOCK_MONOTONIC, &a_ts_end);

	clock_gettime(CLOCK_MONOTONIC, &b_ts_start);
	bsorted = doDeqFordJohnson(_blist);
	clock_gettime(CLOCK_MONOTONIC, &b_ts_end);

	checkLists(asorted, bsorted, false);

	std::cout << "After:  ";
	showList(asorted);
	showAfter(asorted, a_ts_start, a_ts_end, "std::vector");
	showAfter(bsorted, b_ts_start, b_ts_end, "std::deque");
}
