/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwagner <mwagner@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 17:06:20 by mwagner           #+#    #+#             */
/*   Updated: 2023/09/24 17:06:24 by mwagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include "colors.hpp"

BitcoinExchange::BitcoinExchange() {
	if (VERBOSE)
		std::cout << "Default Constructor called" << std::endl;
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &src) {
	if (VERBOSE)
		std::cout << "Copy constructor called" << std::endl;
	*this = src;
}

BitcoinExchange &	BitcoinExchange::operator=(BitcoinExchange const &rhs) {
	if (VERBOSE)
		std::cout << "Assignment operator overload called" << std::endl;
	if (this != &rhs) // NO relevant data members from rhs to this
		(void) rhs;
	return (*this);
}

BitcoinExchange::BitcoinExchange(const std::string &filename) {
	initMapData();
	parseFile(filename);
}

BitcoinExchange::~BitcoinExchange() {
	if (VERBOSE)
		std::cout << "Destructor called" << std::endl;
	exchangeRates.clear(); // Erases all elements from the map container. After this call, size() returns zero.
}

void BitcoinExchange::initMapData() {
	std::string line;
	std::ifstream infile;
	infile.open(DATABASE, std::fstream::in); // initialize with provided Database
	if (infile.is_open()) {
		while (std::getline(infile, line)) {
			if (line == "date,exchange_rate")
				continue;
			exchangeRates.insert(std::make_pair(line.substr(0, 10), line.substr(11))); // Insert a date-exchange rate pair into the map
		}
		infile.close(); // Close the file after successful reading
	}
	else {
		std::cerr << COLOR_RED << "Error: could not initialize database.\n" << COLOR_DEFAULT << std::endl;
		infile.close(); // Close the file before exiting
		exit(EXIT_FAILURE); // Exit the program with a failure status
	}
}

void BitcoinExchange::parseFile(const std::string &filename) {
	double rate = 0.0; // Initialize rate
	std::string line;
	std::ifstream infile;
	std::string date;

	infile.open(filename.c_str(), std::fstream::in);
	if (!infile.is_open()) {
		std::cerr << COLOR_RED << "Error: could not open evaluation file.\n" << COLOR_DEFAULT << std::endl;
		infile.close();
		return;  // Exit the function early because the file couldn't be opened.
	}
	// Check if the file is empty
	if (infile.peek() == std::ifstream::traits_type::eof()) {
		std::cerr << COLOR_RED << "Error: evaluation file is empty.\n" << COLOR_DEFAULT << std::endl;
		infile.close();
		return;  // Exit the function early because the file is empty.
	}
	// Format Error handling
	while (std::getline(infile, line)) {
		if (line == "date | value")
			continue;
		if (!isVerticalBar(line))
			continue;
		if (!isValidNumber(line))
			continue;
		if (!checkFormatAndDate(line))
			continue;
		date = line.substr(0, 10);
		// Check if entry with date does exist
		std::map<std::string, std::string>::iterator lowerBound = exchangeRates.lower_bound(date);
		if (lowerBound != exchangeRates.end()) {
			if (lowerBound->first == exchangeRates.upper_bound(date)->first) {
				date = (--exchangeRates.upper_bound(date))->first;
			}
		} else {
			date = (--exchangeRates.end())->first;
		}
		char* endptr_rate;
		rate = strtod(exchangeRates.lower_bound(date)->second.c_str(), &endptr_rate);
		if (*endptr_rate != '\0') {
			std::cerr << COLOR_RED << "Error: invalid exchange rate format => " << exchangeRates.lower_bound(date)->second << COLOR_DEFAULT << std::endl;
			continue;
		}
		// Convert the value from the line to double using strtod
		char* endptr_value;
		double value = strtod(line.substr(13).c_str(), &endptr_value);
		if (*endptr_value != '\0') {
			std::cerr << COLOR_RED << "Error: invalid value format => " << line.substr(13) << COLOR_DEFAULT << std::endl;
			continue;
		}
		std::cout << line << " => ";
		std::cout << std::fixed << std::setprecision(2) << rate * value;
		std::cout << std::endl;
	}
	infile.close();
}

bool BitcoinExchange::isVerticalBar(std::string line) {
	if (line.find('|') == std::string::npos || line.find('|') != line.rfind('|') ||
		line.size() < 14 || line.at(11) != '|') {
		std::cout << COLOR_YELLOW "Error: bad input => " << line << COLOR_DEFAULT << std::endl;
		return false;
	}
	return true;
}

bool BitcoinExchange::isValidNumber(const std::string& line) {
	size_t i = line.find('|');
	std::string numString = line.substr(++i);
	if (numString.empty() || numString.at(0) != ' ') {
		std::cout << COLOR_YELLOW << "Error: line must have format \"YYYY-MM-DD | value\" => " << line << COLOR_DEFAULT << std::endl;
		return false;
	}
	// check for right characters!!
	if (!isPosNumber(numString))
		return false;
	if (isTooLargeNumber(numString))
		return false;
	return true;
}

bool BitcoinExchange::isPosNumber(const std::string& line) {
	size_t numStart = line.find('|');
	numStart += 2;
	if (line.substr(numStart).find('-') != std::string::npos) {
		std::cout << COLOR_YELLOW << "Error: not a positive number" << COLOR_DEFAULT << std::endl;
		return false;
	}
	return true;
}

bool BitcoinExchange::isTooLargeNumber(const std::string &num) {
	if (atof(num.c_str()) > 1000.0) {
		std::cout << COLOR_YELLOW << "Error: too large a number" << COLOR_DEFAULT << std::endl;
		return true;
	}
	return false;
}

bool BitcoinExchange::checkFormatAndDate(std::string line) {
	// First Bitcoin January 3rd 2009
	line += "";
	if (line.size() < 11 || line.at(10) != ' ' || line.at(4) != '-' || line.at(7) != '-') {
		std::cout << COLOR_YELLOW << "Error: line must have format \"YYYY-MM-DD | value\" => " << line << COLOR_DEFAULT << std::endl;
		return false;
	}
	unsigned int year = static_cast<unsigned int>(strtol(line.substr(0, 4).c_str(), 0, 10));
	if (year < 2009) {
		std::cout << COLOR_YELLOW << "Error: invalid year. Valid later than 2008 and format YYYY => " << line << COLOR_DEFAULT << std::endl;
		return false;
	}
	if (line.substr(0, 10) == "2009-01-01" || line.substr(0, 10) == "2009-01-02") {
		std::cout << COLOR_YELLOW << "Error: invalid date. First Bitcoin January 3rd 2009 => " << line << COLOR_DEFAULT << std::endl;
		return false;
	}
	unsigned int month = static_cast<unsigned int>(strtol(line.substr(5, 2).c_str(), 0, 10));
	if (month < 1 || month > 12) {
		std::cout << COLOR_YELLOW << "Error: invalid month. Valid between 01 and 12 and format MM => " << line << COLOR_DEFAULT << std::endl;
		return false;
	}
	if (!isValidDate(line.substr(0, 10)))
		return false;
	return true;
}

// takes date in format "YYYY-MM-DD" and checks if it is a valid day
bool BitcoinExchange::isValidDate(const std::string& dateString) {
	unsigned int year = static_cast<unsigned int>(strtol(dateString.substr(0, 4).c_str(), 0, 10));
	unsigned int month = static_cast<unsigned int>(strtol(dateString.substr(5, 2).c_str(), 0, 10));
	unsigned int day = static_cast<unsigned int>(strtol(dateString.substr(8, 2).c_str(), 0, 10));

	bool isValid = true;

	if ((month < 1 || month > 12 || day < 1 || day > 31) ||
		(month == 2 && ((isLeapYear(year) && day > 29) || (!isLeapYear(year) && day > 28))) ||
		((month == 4 || month == 6 || month == 9 || month == 11) && day > 30)) {
		std::cout << COLOR_YELLOW << "Error: invalid date => " << dateString << COLOR_DEFAULT << std::endl;
		isValid = false;
	}
	return isValid;
}

bool BitcoinExchange::isLeapYear(unsigned int year) {
	if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
		return true; // It's a leap year
	} else {
		return false; // It's not a leap year
	}
}
