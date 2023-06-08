#ifndef BITCOIN
#define BITCOIN

#include <iostream>
#include <sstream>
#include <fstream>
#include <map>
#include <string>
#include <vector>


std::map<std::string, double> read_in_csv();
void compare_csv_to_input(std::string input_file, std::map<std::string, double>);




#endif