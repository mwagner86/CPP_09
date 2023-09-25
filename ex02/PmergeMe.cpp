/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwagner <mwagner@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 17:34:50 by mwagner           #+#    #+#             */
/*   Updated: 2023/09/25 17:34:53 by mwagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

PmergeMe::PmergeMe() {
	if (VERBOSE)
		std::cout << "Default Constructor called" << std::endl;
}

PmergeMe::PmergeMe(const PmergeMe &src) {
	if (VERBOSE)
		std::cout << "Copy constructor called" << std::endl;
	*this = src; // Fix assignment operator issue
}

PmergeMe &PmergeMe::operator=(const PmergeMe &rhs) {
	if (this != &rhs) {
		_vector = rhs._vector; // Copy the vector
		_deque = rhs._deque;   // Copy the deque
	}
	return *this;
}

PmergeMe::~PmergeMe() {
	if (VERBOSE)
		std::cout << "Destructor called" << std::endl;
}

void PmergeMe::parseAndPopulate(char *sequence[], int n) {
	std::set<int> uniqueElements;  // Use std::set to track unique elements
	_vector.clear();  // Clear the vector before populating
	_deque.clear();   // Clear the deque before populating

	for (int i = 1; i < n; ++i) {
		std::istringstream iss(sequence[i]);
		int num;
		if (!(iss >> num) || num <= 0)
			throw PmergeMe::InvalidInputException();

		// Check if the element already exists in the set
		if (uniqueElements.find(num) != uniqueElements.end())
			throw PmergeMe::DuplicateElementException(); // Throw an exception for duplicates

		uniqueElements.insert(num);  // Add the element to the set of unique elements
		_vector.push_back(num);
		_deque.push_back(num);
	}
}

void PmergeMe::performSorting() {
	std::cout << "Vector Container Before: ";
	_printVectorContainer();

	std::cout << "Deque Container Before: ";
	_printDequeContainer();

	std::clock_t start = std::clock();
	std::clock_t start2 = std::clock();

	mergeInsertSortContainer(_vector);

	std::clock_t end = std::clock();
	double durVector = 100.0 * (end - start) / CLOCKS_PER_SEC;

	mergeInsertSortContainer(_deque);

	std::clock_t end2 = std::clock();
	double durDeque = 100.0 * (end2 - start2) / CLOCKS_PER_SEC;

	std::cout << "Vector Container After: ";
	_printVectorContainer();
	std::cout << "Deque Container After: ";
	_printDequeContainer();

	std::cout << "Time to process a range of " << _vector.size() << " elements with std::vector: " << durVector
			  << " us" << std::endl;
	std::cout << "Time to process a range of " << _deque.size() << " elements with std::deque: " << durDeque << " us"
			  << std::endl;
}

void PmergeMe::_printVectorContainer() {
	std::vector<int>::iterator it = _vector.begin();
	std::vector<int>::iterator ite = _vector.end();
	while (it != ite) {
		std::cout << " " << *it;
		++it;
	}
	std::cout << std::endl;
}

void PmergeMe::_printDequeContainer() {
	std::deque<int>::iterator it = _deque.begin();
	std::deque<int>::iterator ite = _deque.end();
	while (it != ite) {
		std::cout << " " << *it;
		++it;
	}
	std::cout << std::endl;
}

template <typename T>
void PmergeMe::mergeInsertSortContainer(T &container) {
	const int size = container.size();

	if (size < 2)
		return; // Base case: Already sorted

	if (size < THRESHOLD) {
		// Insertion Sort for small containers
		for (typename T::iterator i = container.begin(); i != container.end(); ++i) {
			for (typename T::iterator j = i; j != container.begin() && *(j - 1) > *j; --j) {
				std::swap(*j, *(j - 1));
			}
		}
		return;
	}

	typename T::iterator middle = container.begin() + size / 2;
	T left(container.begin(), middle);
	T right(middle, container.end());

	mergeInsertSortContainer(left);
	mergeInsertSortContainer(right);

	// Merge the sorted left and right subcontainers
	typename T::iterator i = left.begin();
	typename T::iterator j = right.begin();
	typename T::iterator k = container.begin();

	while (i != left.end() && j != right.end()) {
		if (*i < *j) {
			*k = *i;
			++i;
		} else {
			*k = *j;
			++j;
		}
		++k;
	}

	// Copy remaining elements from left and right subcontainers, if any
	while (i != left.end()) {
		*k = *i;
		++i;
		++k;
	}
	while (j != right.end()) {
		*k = *j;
		++j;
		++k;
	}
}
