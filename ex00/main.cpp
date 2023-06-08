#include "BitcoinExchange.hpp"

int main (int argc, char** argv)
{
	if (argc != 2)
	{
		std::cerr << "incorrect number of input parameters\n";
		return (1);
	}
	
	 std::string input_file;
	 input_file.assign(argv[1]);
	
	 std::map<std::string, double> data_csv = read_in_csv();
	
     compare_csv_to_input(input_file, data_csv);

	 return (0);
}
	//  std::map<std::string, double>::iterator start = data_csv.begin();
	//  std::map<std::string, double>::iterator end = data_csv.end();
	//  while (start != end)
	//  {
	// 	std::cout << "string: " << start->first << " value: " << start->second << std::endl;
	// 	start++;
	//  }