#include <iostream>
#include <bitset>
#include "red_black_tree.hpp"

int main(void)
{
	ft::LLRB<int, std::string> test(1, "one");
	ft::LLRB<std::string, int> test2;

	test.insert(2, "two");
	test.insert(3, "three");
	test.insert(4, "four");

	std::cout << test.search(4) << std::endl;

	return 0;
}
