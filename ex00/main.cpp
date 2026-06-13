#include <cstddef>
#include <fstream>
#include <iostream>
#include <string>
#include "BitcoinExchange.hpp"

int	main(int argc, char **argv)
{
	{
		if (argc == 2)
		{
			(void)argc;
			(void)argv;

			BitcoinExchange be;
			std::ifstream	baseFile("data.csv");
			std::ifstream	inputFile(argv[1]);
			

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

			// be.readData();


			baseFile.close();
			inputFile.close();
		}
	}
	return (0);
}
