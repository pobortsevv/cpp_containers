#include <iostream>
#include <vector>
#include "ft_vector.hpp"
#include <map>

int main(void)
{
	ft::vector<int> vect;
	vect.push_back(1);
	vect.push_back(1);
	vect.push_back(1);
	vect.push_back(1);
	vect.push_back(1);
	vect.push_back(1);
	std::cout << vect.size() << std::endl;
	return 0;
}
