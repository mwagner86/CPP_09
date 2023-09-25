//
// Created by max on 9/25/23.
//

#include "RPN.hpp"

RPN::RPN() {
	if (VERBOSE)
		std::cout << "Default Constructor called" << std::endl;
}

RPN::RPN(const RPN &src) {
	if (VERBOSE)
		std::cout << "Copy constructor called" << std::endl;
	*this = src;
}

RPN &	RPN::operator=(RPN const &rhs) {
	if (VERBOSE)
		std::cout << "Assignment operator overload called" << std::endl;
	if (this != &rhs) {
		this->_input = rhs._input;
		this->_operand = rhs._operand;
		this->_operator = rhs._operator;
	}
	return (*this);
}

RPN::~RPN() {
	if (VERBOSE)
		std::cout << "Destructor called" << std::endl;
}

int RPN::calculate(const std::string &input) {
	if (isValidRPNExpression(input) == -1) {
		return 0;
	}
	// Clear the operand and operator stacks
	while (!this->_operand.empty()) {
		this->_operand.pop();
	}
	while (!this->_operator.empty()) {
		this->_operator.pop();
	}

	int i = 0;
	int size = input.size();
	while (i < size) {
		char currentChar = input[i];

		if (currentChar >= '0' && currentChar <= '9') {
			this->_operand.push(static_cast<int>(currentChar - '0'));
		} else if (currentChar != ' ') {
			this->_operator.push(currentChar);
		}
		if (this->_operand.size() >= 2 && !this->_operator.empty()) {
			if (operate() == -1) {
				return 0;
			}
		}
		i++;
	}
	if (!this->_operator.empty()) {
		std::cout << "Error: Stack _operator needs to be empty!" << std::endl;
		return 0;
	}
	printResult();
	return this->_operand.top();
}

int RPN::isValidRPNExpression(const std::string &input) {
	const int size = input.size();
	int countNumbers = 0;
	int countOperators = 0;

	for (int i = 0; i < size; i++) {
		char currentChar = input[i];

		if (isdigit(currentChar)) {
			countNumbers++;
		} else if (currentChar == '+' || currentChar == '-' || currentChar == '*' || currentChar == '/') {
			countOperators++;
		} else if (currentChar != ' ') {
			// Invalid character found
			std::cout << "Error: Invalid character '" << currentChar << "' at position " << i << std::endl;
			return -1;
		}
		// Check for space between values and operators
		if (i < size - 1 && (currentChar >= '0' && currentChar <= '9') &&
			input[i + 1] != ' ') {
			std::cout << "Error: Missing space between value and operator at position " << i << std::endl;
			return -1;
		}
	}
	// Check for empty input
	if (input.empty()) {
		std::cout << "Error: Empty input!" << std::endl;
		return -1;
	}
	// Check for more operators than numbers
	if (countOperators >= countNumbers) {
		std::cout << "Error: More operators than numbers!" << std::endl;
		return -1;
	}
	// Check for unnecessary operators
	if (countOperators > countNumbers - 1) {
		std::cout << "Error: Unnecessary operators!" << std::endl;
		return -1;
	}
	// Check if there are no operators
	if (countOperators == 0) {
		std::cout << "Error: No operators found!" << std::endl;
		return -1;
	}
	// Check for the correct number of operators and operands
	if (countOperators != countNumbers - 1) {
		std::cout << "Error: Mismatch between the number of operators and operands." << std::endl;
		return -1;
	}
	return 0; // Input is valid
}



int	RPN::operate()
{
	if (_operand.size() < 2)	{
		std::cout << "Error: Only one operand or wrong operator position" << std::endl;
		return (-1);
	}
	int	second_op = (int)this->_operand.top();
	this->_operand.pop();     // remove element from top of stack.
	int	first_op = (int)this->_operand.top();
	this->_operand.pop();     // remove element from top of stack.
	if (this->_operator.top() == '+')	{
		this->_operand.push(first_op + second_op);
		this->_operator.pop();
	}
	else if (this->_operator.top() == '-')	{
		this->_operand.push(first_op - second_op);
		this->_operator.pop();
	}
	else if (this->_operator.top() == '*')	{
		this->_operand.push(first_op * second_op);
		this->_operator.pop();
	}
	else if (this->_operator.top() == '/')	{
		this->_operand.push(first_op / second_op);
		this->_operator.pop();
	}
	return (0);
}

void	RPN::printResult()	{
	std::cout << (this->_operand.top()) << std::endl; // only result is left in stack.
}
