#include "PmergeMe.hpp"


int main(int ac, char** av)
{
	if (ac < 2)
	{
		std::cerr << "incorrect number of arguments\n";
		return (1);
	}

	std::vector<int> int_vec;
	std::list<int> int_list;
	// check if input is valid and store in vector and list
	for (int i = 1; i < ac; i++)
	{
		for (int j = 0; av[i][j] != '\0'; j++)
		{
			if (av[i][j] < '0' || av[i][j] > '9')
			{
				std::cerr << "incorrect input: only positive numbers\n";
				return (1);
			}
		}
		int num = std::atoi(av[i]);
		int_vec.push_back(num);
		int_list.push_back(num);
	}

	// display vector before sorting
	std::vector<int>::iterator start_v = int_vec.begin();
	std::vector<int>::iterator end_v = int_vec.end();

	std::cout << "int_vec before: ";
	while (start_v != end_v)
	{
		std::cout << *start_v << " ";
		start_v++;
	}
	std::cout << std::endl;

	// display list before sorting

	std::list<int>::iterator start_list = int_list.begin();
	std::list<int>::iterator end_list = int_list.end();

	std::cout << "int_list before: ";
	while (start_list != end_list)
	{
		std::cout << *start_list << " ";
		start_list++;
	}
	std::cout << std::endl;

	// sorting the vector and computing the time needed

	std::clock_t vec_start_time = std::clock(); // returns the processor time
	merge_insert_vec(int_vec, 0, int_vec.size() - 1); // -1 because last element is unpaired
	std::clock_t vec_end_time = std::clock();
	double time_needed_vec = double(vec_end_time - vec_start_time) / CLOCKS_PER_SEC * 1000000; // number of clock ticks per second
																							  // used to calc. amount of seconds passed
	// sorting the list and computing the time needed

	std::clock_t list_start_time = std::clock();
	// -1 nur wenn %2 = 0 ?
	merge_insert_list(int_list, 0, int_list.size() - 1); // -1 because last element is unpaired in insertion sort
	std::clock_t list_end_time = std::clock();
	double time_needed_list = double(list_end_time - list_start_time) / CLOCKS_PER_SEC * 1000000;

	// display sorted vector and time needed

	std::vector<int>::iterator start_v_2 = int_vec.begin();
	std::vector<int>::iterator end_v_2 = int_vec.end();

	std::cout << "int_vec after: ";
	while (start_v_2 != end_v_2)
	{
		std::cout << *start_v_2 << " ";
		start_v_2++;
	}
	std::cout << std::endl;

	// display sorted list and time needed

	std::list<int>::iterator start_list_2 = int_list.begin();
	std::list<int>::iterator end_list_2 = int_list.end();

	std::cout << "int_list after: ";
	while (start_list_2 != end_list_2)
	{
		std::cout << *start_list_2 << " ";
		start_list_2++;
	}
	std::cout << std::endl;

	std::cout << "Time to process a range of " << int_vec.size() << "elements with std::vector : " << time_needed_vec << " us" << std::endl;
	std::cout << "Time to process a range of " << int_list.size() << "elements with std::list : " << time_needed_list << " us" << std::endl;

	return (0);
}