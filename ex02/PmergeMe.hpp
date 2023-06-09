#ifndef PMERGE_HPP
# define PMERGE_HPP

#include <iostream>
#include <vector>
#include <list>
#include <stdlib.h>
#include <ctime>


#include <algorithm>
#include <stdexcept>
#include <cstdlib>
#include <cstdio>

# define K 5

void merge_insert_vec(std::vector<int>& int_vec, int p, int r);
void insertion_sort_vec(std::vector<int>& int_vec, int p, int r);
void merge_vec(std::vector<int>& int_vec, int p, int q, int r);

void merge_insert_list(std::list<int>& int_list, int p, int r);
void merge_list(std::list<int>& int_list, int p, int q, int r);
void insertion_sort_list(std::list<int>& int_list, int p, int q);

#endif