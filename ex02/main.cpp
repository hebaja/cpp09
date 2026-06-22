#include "PmergeMe.hpp"

int	main(int argc, char **argv)
{
	if (argc > 1)
	{
		try {
			PmergeMe pm(argc, argv);
			pm.showAlist();
		} catch (std::runtime_error &e) {
			std::cout << e.what() << std::endl;		
		}
	}
	else
	{
		std::cerr << "Error" << std::endl;
		return (1);
	}
	return (0);
}
