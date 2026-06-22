#pragma  once

#include <vector>
#include <iostream>
#include <stdexcept>

class PmergeMe
{
private:
	std::vector<unsigned int>	_alist;

public:
	PmergeMe();
	PmergeMe(int argc, char **argv);
	PmergeMe(const PmergeMe &other);
	PmergeMe& operator=(const PmergeMe &other);
	~PmergeMe();

	void	showAlist();
};
