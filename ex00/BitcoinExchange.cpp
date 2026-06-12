#include "BitcoinExchange.hpp"
#include <cstddef>
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

void	trim(std::string &str)
{
    const std::string whitespace = " \t\n\r\f\v";

	std::size_t start = str.find_first_not_of(whitespace);
    std::size_t end = str.find_last_not_of(whitespace);
	if (start != std::string::npos && end != std::string::npos)
		str = str.substr(start, end - start + 1);
}

void	BitcoinExchange::treatInput(std::ifstream &file)
{
	std::string	line;
	std::string	date;
	std::string	value;

	std::getline(file, line);
	while (std::getline(file, line))
	{
		std::size_t	pos = line.find("|");
		
		if (pos != std::string::npos)
		{
			date = line.substr(0, pos);
			value = line.substr(pos + 1, line.length());
		}
		else
			date = line;
		trim(date);
		trim(value);
		// TODO COMPARE VALUES HERE
		std::cout << date << std::endl;
		std::cout << value << std::endl;
	}
}

void BitcoinExchange::readData()
{
	for (std::map<std::string, std::string>::iterator it = _data.begin(); it != _data.end(); ++it)
		std::cout << it->first << " *** " << it->second << std::endl;
}
