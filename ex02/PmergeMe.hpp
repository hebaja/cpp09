#pragma  once

#include <vector>
#include <iostream>
#include <stdexcept>

struct Pair
{
	unsigned int	a;
	unsigned int	b;

	unsigned int operator[](unsigned int index) const {
		if (index == 0)
			return (a);
		return (b);
	}
	
	unsigned int &operator[](unsigned int index) {
		if (index == 0)
			return (a);
		return (b);
	}
};

inline std::ostream &operator<<(std::ostream &os, const Pair &p) {
	os << p[0] << " " << p[1];
	return os;
}

class PmergeMe
{
private:
	std::vector<unsigned int>	_alist;
	std::vector<Pair>			_pairs;

public:
	PmergeMe();
	PmergeMe(int argc, char **argv);
	PmergeMe(const PmergeMe &other);
	PmergeMe& operator=(const PmergeMe &other);
	~PmergeMe();

	// void	sortPairs();

	void	showAlist();
	void	showPairs() {
		for (std::vector<Pair>::iterator it = _pairs.begin(); it != _pairs.end(); ++it) {
			std::cout << *it << std::endl;
		}
	}
};
