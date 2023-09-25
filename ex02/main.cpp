/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwagner <mwagner@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 17:12:46 by mwagner           #+#    #+#             */
/*   Updated: 2023/09/25 17:12:50 by mwagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

int main(int argc, char **argv) {
	try {
		if (argc < 2) {
			std::cerr << "Usage: " << argv[0] << " sequence of positive integers" << std::endl;
			return 1; // Return a non-zero exit code to indicate an error
		}
		PmergeMe merger;
		merger.parseAndPopulate(argv, argc);
		merger.performSorting();
	} catch (const std::exception &e) {
		std::cerr << "Error: " << e.what() << '\n';
		return 1; // Return a non-zero exit code to indicate an error
	}
	return 0; // Return 0 to indicate success
}
