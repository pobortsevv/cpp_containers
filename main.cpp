#include <iostream>
#include <vector>
#include "ft_vector.hpp"
#include "red_black_tree.hpp"
#include <map>
#include <bitset>


struct my 
{
	int _n;
	my(int n) : _n(n)
	{
		std::cout << "Мы вызвали конструктор " << _n <<  std::endl;
	}
	~my(void)
	{
		std::cout << "Смэрть " << _n << std::endl;
	}
};

int main(void)
{
	ft::LLRB<int, int> hello(1, 1);

	hello.insert(2, 2);
	hello.insert(-1, -1);
	hello.delete_(2);


	std::cout << *hello.min() << std::endl;

	return 0;
}
