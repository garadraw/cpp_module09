#include "BitcoinExchange.hpp"

char int_to_char(int value)
{
	if (value < 0 || value > 9)
	{
		std::cerr << "cant convert: outside range\n";
		return;
	}

	return (char (value + 48));
}

std::string my_to_string(int value)
{
	std::string num_string;

	std::vector<int> digits;

	while (true)
	{
		digits.insert(digits.begin(), value % 10);
		value = value / 10;

		if (value == 0)
		{
			break;
		}
	}

	for (int i = 0; i < digits.size(); i++)
	{
		num_string += int_to_char(digits[i]);
	}

	digits.clear();

	return (num_string);
}