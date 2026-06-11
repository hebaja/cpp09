#include <fstream>
#include <iostream>
#include <string>

int	main()
{
	std::ifstream	baseFile("data.csv");

	if (!baseFile.is_open())
	{
		std::cerr << "Error: could not open csv file" << std::endl;
		return (1);
	}

	std::string	line;
	while (std::getline(baseFile, line))
		std::cout << line << std::endl;

	return (0);
}
