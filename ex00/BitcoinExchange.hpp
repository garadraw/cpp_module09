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

int valid_value(const std::string& value, const std::string& date, std::map<std::string, double> data_csv);
double find_ex_rate(const std::string& date, std::map<std::string, double> data_csv);
std::string find_closest_date(const std::string& cur_date);
int valid_date(const std::string& date);

std::string my_to_string(int value);
char int_to_char(int value);


#endif