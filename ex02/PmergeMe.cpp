#include "PmergeMe.hpp"

// K = size of a group; r = elements -1 becasue for insertion sort we split in sorted (= 1)
// and unsorted part (=the rest) , q = num of groups, p = 0; r = elements - 1 for insertion sort
/*
* K = 
*/
void merge_insert_vec(std::vector<int>& int_vec, int p, int r)
{
	if (r - p > K) // divide into paired groups until num of groups wanted reached
	{
		int q = (p + r) / 2;
		merge_insert_vec(int_vec, p, q);
		merge_insert_vec(int_vec, q + 1, r); 
		merge_vec(int_vec, p, q, r); // merge sort
	}
	else // if vector is smaller or equal to K (size of a group) we use insetion sort only
	{
		insertion_sort_vec(int_vec, p, r);
	}
}

void insertion_sort_vec(std::vector<int>& int_vec, int p, int q)
{
    for (int i = p; i < q; i++)
	{
        int tempVal = int_vec[i + 1];
        int j = i + 1;
        while (j > p && int_vec[j - 1] > tempVal) // if curr pos is bigger than next pos
		{
            int_vec[j] = int_vec[j - 1];
            j--; // count down till 0
        }
        int_vec[j] = tempVal;
	}
}

/*
* mergesort splits array into 2 parts until not possible anymore (=1)
* then sorts them and then merges them together
*/
void merge_vec(std::vector<int>& int_vec, int p, int q, int r)
{
	int n1 = q - p + 1; // num of groups + 1
	int n2 = r - q; // elements - num of groups

	std::vector<int> Left(n1); // two arrays for sorting
	std::vector<int> Right(n2);

	// fill the halfes with the numbers
	for (int i = 0; i < n1; i++)
	{
		Left[i] = int_vec[p + i];
	}

	for (int i = 0; i < n2; i++)
	{
		Right[i] = int_vec[q + 1 + i];
	}

	int RIDX = 0;
	int LIDX = 0;

	for (int i = p; i <= r; i++) // sorting+merging the split arrays into int_vec, starts each round at 0
	{
		if (RIDX == n2)
		{
			int_vec[i] = Left[LIDX];
			LIDX++;
		}
		else if (LIDX == n1)
		{
			int_vec[i] = Right[RIDX];
			RIDX++;
		}
		else if (Right[RIDX] > Left[LIDX])
		{
			int_vec[i] = Left[LIDX];
			LIDX++;
		}
		else
		{
			int_vec[i] = Right[RIDX];
			RIDX++;
		}
	}
}

//------ list-------------

void merge_insert_list(std::list<int>& int_list, int p, int r)
{
	if (r - p > K) // divide into paired groups until num of groups wanted reached
	{
		int q = (p + r) / 2;
		merge_insert_list(int_list, p, q);
		merge_insert_list(int_list, q + 1, r); 
		merge_list(int_list, p, q, r); // merge sort
	}
	else
	{
		insertion_sort_list(int_list, p, r);
	}
}

// std::next own implementation, advance basically does the same thing just doesnt return an iterator
std::list<int>::iterator my_next(/*std::list<int>& int_list*/std::list<int>::iterator it, int n)
{
	//std::list<int>::iterator it = int_list.begin();
	std::advance(it, n);
	return it;
}

// begin() returns iterator to the first element, end() returns iterator next to the last element
void merge_list(std::list<int>& int_list, int p, int q, int r)
{
	int n1 = q - p + 1; // num of groups + 1
	int n2 = r - q; // elements - num of groups

	std::list<int> Left; // two arrays for sorting
	std::list<int> Right;

	// fill the halfes with the numbers (0 till half and half till end)
	for (int i = 0; i < n1; i++)
	{ 
		Left.push_back(*my_next(int_list.begin(), p + i)); // std:next : gives next iterator, at pos n after the start pos
	}

	for (int i = 0; i < n2; i++)
	{
		Right.push_back(*my_next(int_list.begin(), q + 1 + i));
	}

	int RIDX = 0;
	int LIDX = 0;

	for (int i = p; i <= r; i++) // sorting+merging the split arrays into int_vec, starts each round at 0
	{
		if (RIDX == n2)
		{
			*my_next(int_list.begin(), i) = Left.front(); // front returns reference to first element in the list
			Left.pop_front();
			LIDX++;
		}
		else if (LIDX == n1)
		{
			*my_next(int_list.begin(), i) = Right.front();
			Right.pop_front();
			RIDX++;
		}
		else if (Right.front() > Left.front())
		{
			*my_next(int_list.begin(), i) = Left.front(); // insert front element from left array into int_list at post after i;
			Left.pop_front(); // then take it out
			LIDX++;
		}
		else
		{
			*my_next(int_list.begin(), i) = Right.front();
			Right.pop_front();
			RIDX++;
		}
	}
}

void insertion_sort_list(std::list<int>& int_list, int p, int q)
{
	for (int i = p; i < q; i++)
	{
        int tempVal = *my_next(int_list.begin(), i + 1);
        int j = i + 1;
        while (j > p && *my_next(int_list.begin(), j - 1) > tempVal) // if curr pos is bigger than next pos
		{
            *my_next(int_list.begin(), j) = *my_next(int_list.begin(), j - 1);
            j--; // count down till 0
        }
        *my_next(int_list.begin(), j) = tempVal; //insert element at correct position
	}
}
