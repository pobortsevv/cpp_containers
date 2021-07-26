#include <iostream>
#include <vector>
#include "ft_vector.hpp"
#include <map>

int main(void)
{
	ft::vector<int> vect;
	vect.push_back(17);
	vect.push_back(2);
	vect.push_back(3);
	vect.push_back(4);
	vect.push_back(5);
	vect.push_back(6);
	vect.pop_back();

	std::vector<int> std_vect;
	std_vect.push_back(1);
	std_vect.push_back(2);
	std_vect.push_back(3);
	std_vect.push_back(4);
	std_vect.push_back(5);
	std_vect.push_back(6);
	std_vect.pop_back();

	ft::vector<int> an_vect;
	an_vect.push_back(21);

	vect.clear();

	std::cout << "std: " << an_vect.size() << std::endl;
	std::cout << "my: " << vect.size() << std::endl;
	return 0;
}
