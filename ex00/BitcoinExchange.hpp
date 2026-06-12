#pragma once

#include <fstream>
#include <map>
#include <string>

class BitcoinExchange
{
private:
	std::map<std::string, std::string> _data;

public:
	BitcoinExchange();
	BitcoinExchange(const BitcoinExchange &other);
	BitcoinExchange& operator=(const BitcoinExchange &other);
	~BitcoinExchange();

	void	consumeCsv(std::ifstream &file);
	void	treatInput(std::ifstream &file);
	void	readData();

};
