/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwagner <mwagner@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 12:38:10 by mwagner           #+#    #+#             */
/*   Updated: 2023/09/25 12:38:35 by mwagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

int	main(int argc, char **argv)
{
	if (argc != 2) {
		std::cerr	<< COLOR_RED << "Error: Wrong input or no arguments.\n" << COLOR_DEFAULT
					<< "Usage: ./RPN \"2 operands per operators\"" << std::endl;
		exit(EXIT_FAILURE);
	}
	else	{
		RPN	rpn;
		rpn.calculate(argv[1]);
	}
	return 0;
}
