#include "BitcoinExchange.hpp"
#include <iostream>

int main(int argc, char **argv)
{
	{
		if (argc == 2)
		{
			BitcoinExchange be;
			std::ifstream baseFile("data.csv");
			std::ifstream inputFile(argv[1]);

			if (!baseFile.is_open())
			{
				std::cerr << "Error: could not open csv file." << std::endl;
				return (1);
			}
			if (!inputFile.is_open())
			{
				std::cerr << "Error: could not open input file." << std::endl;
				return (1);
			}
			be.consumeCsv(baseFile);
			be.treatInput(inputFile);
			baseFile.close();
			inputFile.close();
		}
		else
		{
			std::cerr << "Error: could not open file." << std::endl;
			return (1);
		}
	}
	return (0);
}
