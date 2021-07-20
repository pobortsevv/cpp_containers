#include <iostream>
#include <vector>
#include <map>

int main(void)
{
	std::vector<int> vect;
	std::cout << "Hello World!" << std::endl;
	std::allocator<int> al;
	std::allocator_traits<std::allocator<int> > tr;
773323860595
	tr.allocate(al, 1);
	return 0;
}
