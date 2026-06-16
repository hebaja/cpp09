#include "BitcoinExchange.hpp"
#include <cstddef>
#include <iostream>
#include <sstream>
#include <string>

BitcoinExchange::BitcoinExchange() : _data() {}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &other) : _data(other._data) {}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange &other)
{
	if (this != &other)
		_data = other._data;
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
	
	pos = date.find("-");
	if (pos != std::string::npos)
	{
		str_year = date.substr(0, pos);
		if (str_year.length() != 4 || str_year.find_last_not_of("0123456789") != std::string::npos)
		{
			std::cerr << "Error: malformed year: " << date << std::endl;
			return (-1);
		}
		std::istringstream iss(str_year);
		if (iss >> num_year)
			return (num_year);
	}
	std::cerr << "Error: problem parsing year: " << date <<std::endl;
	return (-1);
}

int	parseMonth(std::string date)
{
	int			num_mon;
	std::string	str_mon;
	std::size_t	pos;

	pos = date.find("-");
	if (pos != std::string::npos)
	{
		str_mon = date.substr(pos + 1, 2);
		if (date.at(pos + 3) != '-')
		{
			std::cerr << "Error: malformed month: " << date << std::endl;
			return (-1);
		}
		std::istringstream iss(str_mon);
		if (iss >> num_mon)
		{
			if (num_mon >= 1 && num_mon <= 12)
				return (num_mon);
		}
	}
	std::cerr << "Error: problem parsing month: " << date << std::endl;
	return (-1);
}

bool	isLeapYear(int year)
{
	if ((year % 400 == 0) || ((year % 4 == 0) && (year % 100 != 0)))
		return (true);
	return (false);
}

int	parseDay(std::string date, int year, int month)
{
	int			num_day;
	std::string	str_day;
	std::size_t	pos;

	pos = date.find("-");
	if (pos != std::string::npos)
	{
		str_day = date.substr(pos + 4, date.length() - (pos + 4));
		std::istringstream iss(str_day);
		if (iss >> num_day)
		{
			if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)
			{
				if (num_day >= 1 && num_day <= 31)
					return (num_day);
			}
			else if (month == 2)
			{
				if (isLeapYear(year))
				{
					if (num_day >= 1 && num_day <= 29)
						return (num_day);
					else
						std::cerr << "Error: wrong day for leap year: " << date << std::endl;
				}
				else
				{
					if (num_day >= 1 && num_day <= 28)
						return (num_day);
					else
						std::cerr << "Error: wrong day: " << date << std::endl;
				}
			}
			else if (num_day >= 1 && num_day <= 30)
				return (num_day);
			else
				std::cerr << "Error: wrong day: " << date << std::endl;
		}
	}
	return (-1);
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
	if (day < 0)
		return (false);
	
	return (true);
}

double	parseValue(std::string value)
{
	double	num_value;

	std::istringstream iss(value);
	if (iss >> num_value)
	{
		if (num_value < 0.0)
			std::cerr << "Error: Not a positive number." << std::endl;
		else if (num_value > 1000.0)
			std::cerr << "Error: too large a number." << std::endl;
		else
			return (num_value);
	}
	std::cerr << "Error: problem parsing value: " << value << std::endl;
	return (-1);
}

void	BitcoinExchange::treatInput(std::ifstream &file)
{
	std::string	line;
	std::string	date;
	std::string	value;
	double		num_value;

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
				continue ;
			num_value = parseValue(value);
			if (num_value < 0)
				continue ;
		}
		else
		{
			std::cerr << "Error: bad input => " << line << std::endl;
			continue ;
		}

		std::map<std::string, std::string>::iterator it = _data.upper_bound(date);
		if (it != _data.begin())
		{
			--it;
			double f;
			std::istringstream iss(it->second);
			if (iss >> f)
				std::cout << it->first << " => " << num_value << " = " << f * num_value << std::endl;
			else
				std::cerr << "Error: value too complex: " << it->second << std::endl;
		}
		else
			std::cerr << "Error: too far a date => " << date << std::endl;
	}
}
