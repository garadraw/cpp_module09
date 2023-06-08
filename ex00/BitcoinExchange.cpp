#include "BitcoinExchange.hpp"

std::map<std::string, double> read_in_csv()
{
	std::string line;
	std::map<std::string, double> _data_csv;
	std::ifstream csv_stream("data.csv");

	if (!csv_stream)
	{
		std::cerr << "error: data.csv can't be found\n";
	}

	std::getline(csv_stream, line);

	while (std::getline(csv_stream, line))
	{
		std::stringstream ss(line);
		std::string date;
		std::string ex_rate;
		std::getline(ss, date, ',');
		std::getline(ss, ex_rate);
		_data_csv[date] = std::atof(ex_rate.c_str());
	}
	return(_data_csv);
}



void compare_csv_to_input(std::string input_file, std::map<std::string, double> data_csv)
{
	std::string line;
	std::ifstream input_stream(input_file);

	if (!input_stream)
	{
		std::cerr << "Can not Open" << input_file << "\n";
	}
	std::getline(input_stream, line);
	if (line.compare("date | value") != 0)
	{
		std::cerr << "first line is not 'date | value' \n ";
	}

	while (std::getline(input_stream, line))
	{
		std::stringstream ss_input_file(line);
		std::string date;
		std::string value;
		std::string delim;

		ss_input_file >> date >> delim >> value;
		
		if (delim != "|" || date.empty() || value.empty())
			std::cerr << "Error: bad input => " << date << "\n";

		else if (valid_date(date) == 1 || vaid_value(value, date, data_csv) == 1)
			std::cerr << "Error: bad input => " << date << "\n";
	}
}

