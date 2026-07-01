#pragma once

#include <deque>
#include <iostream>
#include <vector>

struct Pair {
  unsigned int a;
  unsigned int b;

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

  bool operator<(const Pair &other) const { return (a < other.a); }
};

inline std::ostream &operator<<(std::ostream &os, const Pair &p) {
  os << p[0] << " " << p[1];
  return os;
}

typedef std::vector<unsigned int> UintVec;
typedef std::deque<unsigned int> UintDeq;

class PmergeMe {
private:
  std::vector<unsigned int> _alist;
  std::deque<unsigned int> _blist;

public:
  PmergeMe();
  PmergeMe(int argc, char **argv);
  PmergeMe(const PmergeMe &other);
  PmergeMe &operator=(const PmergeMe &other);
  ~PmergeMe();

  void showBeforeSort();
  void showAfterSort();
};
