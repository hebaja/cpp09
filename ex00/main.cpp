#include <cstddef>
#include <fstream>
#include <iostream>
#include <string>

int	main(int argc, char **argv)
{
	/*
	{
		if (argc == 2)
		{
			std::ifstream	inputFile(argv[1]);
		
			if (!inputFile.is_open())
			{
				std::cerr << "Error: could not open input file." << std::endl;
				return (1);
			}
			else
			{
				std::string	line;
				while (std::getline(inputFile, line))
					std::cout << line << std::endl;

				inputFile.close();
			}
		}
		else
		{
			std::cerr << "Error: could not open file." << std::endl;
			return (1);
		}
			
	}
	*/
	{
		(void)argc;
		(void)argv;


		std::ifstream	baseFile("data.csv");

		if (!baseFile.is_open())
		{
			std::cerr << "Error: could not open csv file." << std::endl;
			return (1);
		}

		std::string	line;
		std::getline(baseFile, line);
		while (std::getline(baseFile, line))
		{
			std::cout << line.substr(0, line.find(",")) << " ---> " << 
				line.substr(line.find(",") + 1, line.length()) << std::endl;
		}

		baseFile.close();
	}
	return (0);
}
