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
		std::cerr << "Can not Open" << input_file << "\n";
	std::getline(input_stream, line);
	if (line.compare("date | value") != 0)
		std::cerr << "first line is not 'date | value' \n ";

	while (std::getline(input_stream, line))
	{
		std::stringstream ss_input_file(line);
		std::string date;
		std::string value;
		std::string delim;

		ss_input_file >> date >> delim >> value;
		
		if (delim != "|" || date.empty() || value.empty())
			std::cerr << "Error: bad input => " << date << "\n";

		else if (valid_date(date) == 1 || valid_value(value, date, data_csv) == 1)
			std::cerr << "Error: bad input => " << date << "\n";
	}
}


int valid_date(const std::string& date)
{
	if (date.length() != 10)
	{
		return (1);
	}

	std::stringstream date_stream(date);

	std::string year, month, day;

	std::getline(date_stream, year, '-');
	std::getline(date_stream, month, '-');
	std::getline(date_stream, day);

	if (std::atoi(year.c_str()) < 0 || std::atoi(month.c_str()) > 12 || \
		std::atoi(month.c_str()) < 0 || std::atoi(day.c_str()) > 31 || std::atoi(day.c_str()) < 0)
	{
			return (1);
	}
	int num_year = std::atoi(year.c_str()); // std::atoi(year.c_str());
	int num_month = std::atoi(month.c_str());
	int num_day = std::atoi(day.c_str());

	bool leap_year = ((num_year % 4 == 0) && (num_year % 100 != 0)) || (num_year % 400 == 0);
	if (num_month == 2 && leap_year && num_day > 29)
	{
		return (1);
	}
	else if (num_month == 2 && !leap_year && num_day > 28)
	{
		return (1);
	}

	if ((num_month == 4 || num_month == 6 || num_month == 9 || num_month == 11) && num_day > 30)
	{
		return (1);

	}

	if ((num_month == 1 || num_month == 3 || num_month == 5 || num_month == 7 || num_month == 8 || num_month == 10 || num_month == 12) && num_day > 31)
	{
		return (1);
	}
	return (0);
}



int valid_value(const std::string& value, const std::string& date, std::map<std::string, double> data_csv)
{
	double value_double;

	try
	{
		value_double = std::atof(value.c_str());

		if (value_double < 0)
		{
			std::cerr << "Error: not a positive number.\n";
		}
		else if ( value_double > 1000)
		{
			std::cerr << "Error: too large a number.(1000max)\n";
		}
		else
		{
			double res = value_double * find_ex_rate(date, data_csv);
			std::cout << date << " => " << value << " = " << res << std::endl;
		}
	}
	catch(const std::exception& e)
	{
		return (1);
	}
	
	return (0);
}

/*
* recursively calling find_ex_rate until date found or date below 2009
*/
double find_ex_rate(const std::string& date, std::map<std::string, double> data_csv)
{
	// find the date in csv and return the element of it (=it->second)
	std::map<std::string, double>::iterator it = data_csv.find(date);
	if (it != data_csv.end())
	{
		return (it->second);
	}
	else
	{
		// find closest lowest date
		std::string closest_date = find_closest_date(date);
		if (closest_date.compare("invalid date\n") == 0)
		{
			std::cerr << "invalid date\n";
			return (0);
		}
		return find_ex_rate(closest_date, data_csv);
	}
}

std::string find_closest_date(const std::string& cur_date)
{
	std::string closest_date, year, month, day;

	std::stringstream cur_date_stream(cur_date);

	std::getline(cur_date_stream, year, '-');
	std::getline(cur_date_stream, month, '-');
	std::getline(cur_date_stream, day);

	int num_year = std::atoi(year.c_str());
	int num_month = std::atoi(month.c_str());
	int num_day = std::atoi(day.c_str());

	int prev_year = num_year;
	int prev_month = num_month;
	int prev_day = num_day -1;

	if (prev_day == 0)
	{
		prev_month = num_month - 1;
		if (prev_month == 0)
		{
			prev_month = 12;
			prev_year = num_year - 1;
			if (prev_year < 2009)
			{
				return ("invalid date\n");
			}
		}
		else if (prev_month != 0)
		{
			if (prev_month == 2)
			{
				if (prev_year % 4 == 0 && (prev_year % 100 != 0 || prev_year % 400 == 0))
				{
                    prev_day = 29;
                }
				else
				{
                    prev_day = 28;
                }
			}
			else if (prev_month == 11 || prev_month == 4 || prev_month == 6 || prev_month == 9)
			{
				prev_day = 30;
			}
			else
			{
				prev_day = 31;
			}
		}
	}

	closest_date = std::to_string(prev_year);
	closest_date += "-";
	if (prev_month < 10)
	{
		closest_date += "0";
		closest_date += std::to_string(prev_month);
		closest_date += "-";
	}
	else
	{
		closest_date += std::to_string(prev_month);
	}

	if (prev_day < 10)
	{
		closest_date += "0";
		closest_date += std::to_string(prev_day);
	}
	else
	{
		closest_date += std::to_string(prev_day);
	}

	return (closest_date);
}