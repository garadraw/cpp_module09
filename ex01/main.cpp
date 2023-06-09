#include <iostream>
#include <stack>
#include <sstream>
#include <stdlib.h>
#include <string>
#include <cstring>

int main(int ac, char **av)
{
	if (ac < 2)
	{
		std::cout << "This program only takes 2 parameters\n";
		return (1);
	}

	std::string input = av[1]; 

	std::stack<int> input_nums;

	std::stringstream input_stream(input);

	std::string token;

	// read in token separated by space
	while (input_stream >> token)
	{
		int result = 0;
		// if its a sign but we havent read out at least to numbers to perform the operation on -> error
		// else execute the operation
		if (token == "+" || token == "-" || token == "*" || token == "/")
		{
			if (input_nums.size() < 2)
			{
				std::cerr << "not enough numbers to execute calculation\n";
			}

			int num1 = input_nums.top();
			input_nums.pop();
			int num2 = input_nums.top();
			input_nums.pop();

			if (token == "+")
			{
				result = num1 + num2;
			}
			else if (token == "-")
			{
				result = num2  - num1;
			}
			else if (token == "*")
			{
				result = num1 * num2;
			}
			else if (token == "/")
			{
				if (num2 == 0)
				{
					std::cerr << "can't divide by 0\n";
					return (1);
				}
				result = num1 / num2;
			}
			std::cout << "result is: " << result << std::endl;
			input_nums.push(result);
		}
		else // if its not a sign, verify that token is only numbers and then push the number into the stack
		{
			for (int i = 0; i < (int)token.size(); i++)
			{
				if (token[i] < '0' || token[i] > '9')
				{
					std::cerr << "invalid token at: " << token[i] << std::endl;
					return (1);
				}
			}
			std::cout << "token is: " << token << std::endl;
			input_nums.push(std::atoi(token.c_str()));
		}

	}

	// in case we have only numbers and more than one number(=the result), we cant do this operation because operand is missing
	if (input_nums.size() != 1)
	{
		std::cerr << "cant execute this operation\n";
		return (1);
	}

	std::cout << "Result of this RPN-operation is: " << input_nums.top() << std::endl;

	return (0);
}
