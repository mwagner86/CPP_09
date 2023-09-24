#include "BitcoinExchange.hpp"
#include "colors.hpp"

int main(int argc, char **argv) {
	if (argc != 2) {
		std::cerr	<< COLOR_RED << "Error: No input file or too many arguments.\n" << COLOR_DEFAULT
					<< "Usage: ./btc file.name" << std::endl;
		exit(EXIT_FAILURE);
	}
	BitcoinExchange *btc;
	btc = new BitcoinExchange(std::string(argv[1]));
	delete btc;
	return 0;

}