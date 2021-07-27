#include <iostream>
#include <vector>
#include "ft_vector.hpp"
#include <map>

int main(void)
{
	// ft::vector<int> first;                                // empty vector of ints
	// ft::vector<int> second (4,100);                       // four ints with value 100
	// ft::vector<int> fourth (third);                       // a copy of third

	// the iterator constructor can also be used to construct from arrays:
	// int myints[] = {16,2,77,29};
	// std::vector<int> fifth (myints, myints + sizeof(myints) / sizeof(int) );

	ft::vector<int> vect;
	vect.push_back(17);
	vect.push_back(2);
	vect.push_back(3);
	vect.push_back(4);
	vect.push_back(5);
	vect.push_back(6);
	vect.resize(5);
	vect.resize(8,100);
	vect.resize(12);
	ft::vector<int>::iterator it(vect.begin());
	// for (;it != vect.end(); it++)
	// 	std::cout << *it << std::endl;
	vect.erase(it + 1);

	ft::vector<int> third(vect.begin(),vect.end());  // iterating through second
	std::cout << "The contents of fifth are:";
	for (ft::vector<int>::iterator it = third.begin(); it != third.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';
	// std::vector<int> std_vect;
	// std_vect.push_back(1);
	// std_vect.push_back(2);
	// std_vect.push_back(3);
	// std_vect.push_back(4);
	// std_vect.push_back(5);
	// std_vect.push_back(6);
	// std::vector<int>::iterator sti(std_vect.begin());
	// std_vect.erase(sti + 1);

	// std::cout << "my: " << vect[1] << std::endl;
	// std::cout << "std: " << std_vect[1] << std::endl;
	return 0;
}
