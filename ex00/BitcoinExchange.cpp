#include "BitcoinExchange.hpp"
#include <cstddef>
#include <iostream>
#include <sstream>
#include <string>

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

int	parseYear(std::string date)
{
	int			num_year;
	std::string	str_year;
	std::size_t	pos = date.find("-");
	
	if (pos != std::string::npos)
	{
		str_year = date.substr(0, pos);
		if (str_year.length() != 4 || str_year.find_last_not_of("0123456789") != std::string::npos)
			return (-1);
		std::istringstream iss(str_year);
		if (iss >> num_year)
			return (num_year);
	}
	return (-1);
}

int	parseMonth(std::string date)
{
	int			num_mon;
	std::size_t	pos;
	std::string	str_mon;

	pos = date.find("-");
	if (pos != std::string::npos)
	{
		if (date.at(pos + 3) != '-')
			return (false);
		str_mon = date.substr(pos + 1, 2);
		std::istringstream iss(str_mon);
		if (iss >> num_mon)
		{
			if (num_mon >= 1 && num_mon <= 12)
				return (num_mon);
		}
	}
	return (-1);
}

int	parseDay(std::string date, int year, int month)
{


}

bool	parseDate(std::string date)
{
	int	year;
	int	month;
	int	day;

	year = parseYear(date);
	if (year < 0)
		return (false);
	month = parseMonth(date);
	if (month < 0)
		return (false);
	day = parseDay(date, year, month);
		return (false);
	if (day < 0)
		return (false);
	
	std::cout << "*** " << year << " *** " << month << std::endl;




	/*
	*/
	return (true);
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
			trim(date);
			trim(value);
			if (!parseDate(date))
				std::cerr << "Error: bad input => " << line << std::endl;

			// std::cout << date << " || " << value << std::endl;
		}
		else
		{
			std::cerr << "Error: bad input => " << line << std::endl;
		}
		// TODO COMPARE VALUES HERE
		// std::cout << value << std::endl;
	}
}

void BitcoinExchange::readData()
{
	for (std::map<std::string, std::string>::iterator it = _data.begin(); it != _data.end(); ++it)
		std::cout << it->first << " *** " << it->second << std::endl;
}
