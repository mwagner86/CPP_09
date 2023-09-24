//
// Created by max on 9/24/23.
//

#ifndef EX00_BITCOINEXCHANGE_HPP
#define EX00_BITCOINEXCHANGE_HPP

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <iomanip>
#include <sstream>
#include <map>



class BitcoinExchange {

public:
	explicit BitcoinExchange(const std::string &filename);
	~BitcoinExchange(); // has to be public to be called in main

private:
	BitcoinExchange();
	BitcoinExchange(const BitcoinExchange & src);
	BitcoinExchange & operator=(const BitcoinExchange & rhs);

	std::map<std::string, std::string> exchangeRates;

	void initMapData();
	void processInputFile(const std::string& filename);

	bool isVerticalBar(std::string line);
	bool isValidNumber(std::string line);
	bool isPosNumber(std::string line);
	bool isTooLargeNumber(std::string numline);
	bool checkFormatAndDate(std::string line);
	bool isValidDayOfMonth(std::string dateString);
	bool isLeapYear(unsigned int year);
};


#endif //EX00_BITCOINEXCHANGE_HPP
