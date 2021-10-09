#include <iostream>
#include <vector>
#include "ft_vector.hpp"
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
	std::vector<int> foo (3,100);   // three ints with a value of 100
	std::vector<int> bar (2,200);   // two ints with a value of 200

	if (foo==bar) std::cout << "foo and bar are equal\n";
	if (foo!=bar) std::cout << "foo and bar are not equal\n";
	if (foo< bar) std::cout << "foo is less than bar\n";
	if (foo> bar) std::cout << "foo is greater than bar\n";
	if (foo<=bar) std::cout << "foo is less than or equal to bar\n";
	if (foo>=bar) std::cout << "foo is greater than or equal to bar\n";

	std::cout << "My:" << std::endl;

	ft::vector<int> foo2 (3,100);   // three ints with a value of 100
	ft::vector<int> bar2 (2,200);   // two ints with a value of 200

	if (foo2==bar2) std::cout << "foo and bar are equal\n";
	if (foo2!=bar2) std::cout << "foo and bar are not equal\n";
	if (foo2< bar2) std::cout << "foo is less than bar\n";
	if (foo2> bar2) std::cout << "foo is greater than bar\n";
	if (foo2<=bar2) std::cout << "foo is less than or equal to bar\n";
	if (foo2>=bar2) std::cout << "foo is greater than or equal to bar\n";

	return 0;
}
