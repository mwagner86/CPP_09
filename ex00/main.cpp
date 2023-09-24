/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwagner <mwagner@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 17:07:22 by mwagner           #+#    #+#             */
/*   Updated: 2023/09/24 17:07:32 by mwagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
