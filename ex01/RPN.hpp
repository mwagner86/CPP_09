/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwagner <mwagner@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 12:41:37 by mwagner           #+#    #+#             */
/*   Updated: 2023/09/25 12:41:42 by mwagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EX01_RPN_HPP
#define EX01_RPN_HPP

# ifndef VERBOSE
#  define VERBOSE 0
# endif

#include <iostream>
#include <cstdlib>
#include <stack>
#include "colors.hpp"


class RPN {

public:
	RPN();
	~RPN();
	int	calculate(const std::string& input);

private:
	RPN(const RPN & src);
	RPN & operator=(const RPN & rhs);

	std::stack<int>		_operand;
	std::stack<char>	_operator;
	std::string			_input;

	static int		isValidRPNExpression(const std::string& input);
	int		operate();
	void	printResult();

};

#endif //EX01_RPN_HPP
