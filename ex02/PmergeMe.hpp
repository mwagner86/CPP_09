/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwagner <mwagner@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 17:35:10 by mwagner           #+#    #+#             */
/*   Updated: 2023/09/25 17:35:12 by mwagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef EX02_PMERGEME_HPP
#define EX02_PMERGEME_HPP

#ifndef VERBOSE
#define VERBOSE 0
#endif

#include <iostream>
#include <algorithm>
#include <sstream>
#include <ctime>
#include <iterator>

#include <vector>
#include <deque>
#include <list>
#include <set>

#define THRESHOLD 5

class PmergeMe {
public:
	PmergeMe();
	PmergeMe(const PmergeMe &src);
	PmergeMe &operator=(const PmergeMe &rhs);
	~PmergeMe();

	void parseAndPopulate(char *sequence[], int n);
	void performSorting();

	template <typename T>
	void mergeInsertSortContainer(T &container);

	class InvalidInputException : public std::exception {
	public:
		const char *what() const throw() {
			return "Invalid Input";
		}
	};

	class InvalidUsageException : public std::exception {
	public:
		const char *what() const throw() {
			return "Usage: ./PmergeMe sequence of positive ints";
		}
	};

	class DuplicateElementException : public std::exception {
	public:
		const char *what() const throw() {
			return "Duplicate elements detected";
		}
	};

private:
	std::vector<int> _vector;
	std::deque<int> _deque;
	void _printVectorContainer();
	void _printDequeContainer();
};

#endif // EX02_PMERGEME_HPP
