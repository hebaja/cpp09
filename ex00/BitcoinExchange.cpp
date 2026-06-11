#include "BitcoinExchange.hpp"
#include <iostream>

BitcoinExchange::BitcoinExchange() : _data() {}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &other)
{
	(void)other;
}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange &other)
{
	(void)other;
	return (*this);
}

BitcoinExchange::~BitcoinExchange(){}

void	BitcoinExchange::consumeCsv(std::ifstream &file)
{
	std::string	line;

	std::getline(file, line);
	while (std::getline(file, line))
		_data[line.substr(0, line.find(","))] = line.substr(line.find(",") + 1, line.length());
}

void BitcoinExchange::readData()
{
	for (std::map<std::string, std::string>::iterator it = _data.begin(); it != _data.end(); ++it)
		std::cout << it->first << " *** " << it->second << std::endl;
}
