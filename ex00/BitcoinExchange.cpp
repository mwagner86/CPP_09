//
// Created by max on 9/24/23.
//

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
	processInputFile(filename);
}

BitcoinExchange::~BitcoinExchange() {
	if (VERBOSE)
		std::cout << "Destructor called" << std::endl;
	exchangeRates.clear(); // Erases all elements from the map container. After this call, size() returns zero.
}

void BitcoinExchange::initMapData() {
	std::string line;
	std::ifstream infile;
	infile.open("data.csv", std::fstream::in); // initialize with provided Database
	if (infile.is_open()) {
		while (std::getline(infile, line)) {
			if (line == "date,exchange_rate")
				continue;
			exchangeRates.insert(std::make_pair(line.substr(0, 10), line.substr(11))); // Insert a date-exchange rate pair into the map
		}
		infile.close(); // Close the file after successful reading
	}
	else {
		std::cerr << COLOR_RED << "Error: Could not initialize Database.\n" << COLOR_DEFAULT << std::endl;
		infile.close(); // Close the file before exiting
		exit(EXIT_FAILURE); // Exit the program with a failure status
	}
}

void BitcoinExchange::processInputFile(const std::string& filename) {
	double rate = 1.0;
	std::string line;
	std::ifstream infile;
	std::string date;
	infile.open(filename.c_str(), std::fstream::in);
	if (infile.is_open()) {
		while (std::getline(infile, line)) {
			if (line == "date | value")
				continue;
			if (!isVerticalBar(line))
				continue;
			if (!isValidNumber(line))
				continue;
			if (!checkFormatAndDate(line))
				continue;
			date = line.substr(0,10);
			// check if entry with date does exist, i.e. lowerbound != upperbound); if lowerbound == upperbound
			// take date before the actual date (also if iterator is the end == date after last date in database)
			if (exchangeRates.lower_bound(date) != exchangeRates.end()) {
				if (exchangeRates.lower_bound(line.substr(0,10))->first == exchangeRates.upper_bound(line.substr(0,10))->first)
					date = (--exchangeRates.upper_bound(line.substr(0,10)))->first;
			} else {
				date = (--exchangeRates.end())->first;
			}
			//std::cout << "===> Date after check:       " << date << std::endl;
			rate = atof(exchangeRates.lower_bound(date)->second.c_str());
			std::cout << line << " => ";
			std::cout << std::fixed << std::setprecision(2) << (rate * atof(line.substr(13).c_str()));
			std::cout << std::endl;
		}
	}
	else {
		std::cerr << COLOR_RED << "Error: Could not open evaluation file.\n" << COLOR_DEFAULT << std::endl;
		infile.close(); // Close the file before exiting
	}
}

bool BitcoinExchange::isVerticalBar(std::string line) {
	if (line.find('|') == std::string::npos || line.find('|') != line.rfind('|') ||
		line.size() < 14 || line.at(11) != '|') {
		std::cout << "Error: bad input => " << line << std::endl;
		return false;
	}
	return true;
}

bool BitcoinExchange::isValidNumber(std::string line) {
	size_t i = line.find('|');
	std::string numString = line.substr(++i);
	if (numString.size() <= 0 || numString.at(0) != ' ') {
		std::cout << "Error: Line must have format \"YYYY-MM-DD | value\" => " << line << std::endl;
		return false;
	}
	// check for right characters!!
	if (!isPosNumber(numString))
		return false;
	if (isTooLargeNumber(numString))
		return false;
	return true;
}

bool BitcoinExchange::isPosNumber(std::string line) {
	size_t numStart = line.find('|');
	numStart += 2;
	if (line.substr(numStart).find('-') != std::string::npos) {
		std::cout << "Error: not a positive number." << std::endl;
		return false;
	}
	return true;
}

bool BitcoinExchange::isTooLargeNumber(std::string numline) {
	if (atof(numline.c_str()) > 1000.0) {
		std::cout << "Error: too large a number." << std::endl;
		return true;
	}
	return false;
}

bool BitcoinExchange::checkFormatAndDate(std::string line) {
	// Das Bitcoin-Netzwerk entstand am 3. Januar 2009 mit der Schöpfung der ersten 50 Bitcoin und der Generierung von „Block 0“, dem sogenannten Genesisblock. (Wikipedia)
	line +="";
	if (line.size() < 11 || line.at(10) != ' ' || line.at(4) != '-' || line.at(7) != '-') {
		std::cout << "Error: Line must have format \"YYYY-MM-DD | value\" => " << line << std::endl;
		return false;
	}
	if ( atoi(line.substr(0,4).c_str()) < 2009) {
		std::cout << "Error: Invalid year (must be later than 2008 and of format YYYY) => " << line << std::endl;
		return false;
	}
	if (line.substr(0,10) == "2009-01-01" || line.substr(0,10) == "2009-01-02") {
		std::cout << "Error: Invalid date, first bitcoins were created on January 3rd, 2009 => " << line << std::endl;
		return false;
	}
	if (atoi(line.substr(5,2).c_str()) < 1 || atoi(line.substr(5,2).c_str()) > 12) {
		std::cout << "Error: Invalid month (must be 01 .. 12 and of format MM) => " << line << std::endl;
		return false;
	}
	if (!isValidDayOfMonth(line.substr(0,10)))
		return false;
	return true;
}

// takes date in format "YYYY-MM-DD" and checks if it is a valid day
bool BitcoinExchange::isValidDayOfMonth(std::string dateString) {
	bool result = true;
	unsigned int year = atoi(dateString.substr(0,4).c_str());
	unsigned int month = atoi(dateString.substr(5,2).c_str());
	unsigned int day = atoi(dateString.substr(8,2).c_str());

	if (month == 2 && isLeapYear(year)) {
		if (day < 1 || day > 29)
			result = false;
	} else if (month == 2 && !isLeapYear(year)) {
		if (day < 1 || day > 28)
			result = false;
	} else if (month == 4 || month == 6 || month == 9 || month == 11) {
		if (day < 1 || day > 30)
			result = false;
	} else {
		if (day < 1 || day > 31)
			result = false;
	}
	if (result == false)
		std::cout << "Error: date does not exist => " << dateString << std::endl;
	return result;
}

bool BitcoinExchange::isLeapYear(unsigned int year) {
	if (year % 4 == 0 && year % 100 == 0 && year % 400 == 0)
		return true;
	else if (year % 4 == 0 && year % 100 == 0)
		return false;
	else if (year % 4 == 0)
		return true;
	return false;
}
