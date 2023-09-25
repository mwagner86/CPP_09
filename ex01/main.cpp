#include "RPN.hpp"

int	main(int argc, char **argv)
{
	if (argc != 2) {
		std::cerr	<< COLOR_RED << "Error: Wrong input or no arguments.\n" << COLOR_DEFAULT
					<< "Usage: ./RPN \"operands operators\"" << std::endl;
		exit(EXIT_FAILURE);
	}
	else	{
		RPN	rpn;
		rpn.calculate(argv[1]);
	}
	return 0;
}