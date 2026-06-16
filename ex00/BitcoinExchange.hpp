#pragma once

#include <fstream>
#include <iostream>
#include <map>
#include <string>

class BitcoinExchange
{
private:
	std::map<std::string, double> _data;

public:
	BitcoinExchange();
	BitcoinExchange(const BitcoinExchange &other);
	BitcoinExchange& operator=(const BitcoinExchange &other);
	~BitcoinExchange();

	void	consumeCsv(std::ifstream &file);
	void	treatInput(std::ifstream &file);

	void	readData() {
		for (std::map<std::string, double>::iterator it = _data.begin(); it != _data.end(); ++it) {
			std::cout << it->first << " - "<< it->second << std::endl;
		}
	}
};
