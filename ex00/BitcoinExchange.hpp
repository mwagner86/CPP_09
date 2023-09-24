/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwagner <mwagner@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 17:06:52 by mwagner           #+#    #+#             */
/*   Updated: 2023/09/24 17:06:54 by mwagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef EX00_BITCOINEXCHANGE_HPP
#define EX00_BITCOINEXCHANGE_HPP

# ifndef DATABASE
# define DATABASE "data.csv"
# endif

# ifndef VERBOSE
#  define VERBOSE 0
# endif

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
	void parseFile(const std::string& filename);

	static bool isVerticalBar(std::string line);
	static bool isValidNumber(const std::string &line);
	static bool isPosNumber(const std::string &line);
	static bool isTooLargeNumber(const std::string &num);
	static bool checkFormatAndDate(std::string line);
	static bool isValidDate(const std::string &dateString);
	static bool isLeapYear(unsigned int year);
};

#endif //EX00_BITCOINEXCHANGE_HPP
