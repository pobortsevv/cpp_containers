#include <iostream>
#include <vector>
#include "ft_vector.hpp"
#include <map>

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
	// ft::vector<int> first;                                // empty vector of ints
	// ft::vector<int> second;// four ints with value 100
	// // ft::vector<int> fourth (third);                       // a copy of third

	// // the iterator constructor can also be used to construct from arrays:
	// // int myints[] = {16,2,77,29};
	// // std::vector<int> fifth (myints, myints + sizeof(myints) / sizeof(int) );

	// ft::vector<int> vect;

	// vect.push_back(2);
	// vect.push_back(3);
	// vect.push_back(4);
	// vect.push_back(5);
	// vect.push_back(6);
	// // vect.insert (vect.end() -3,300);
	// vect.insert(vect.begin() + 2, 3, 200);
	// // // // vect.resize(5);
	// // // // vect.resize(8,100);
	// // // // vect.resize(12);
	// ft::vector<int>::iterator it(vect.begin());
	// for (;it != vect.end(); it++)
	// 	std::cout << *it << std::endl;
	// vect.erase(it + 1);

	// // ft::vector<int> third(vect.begin(),vect.end());  // iterating through second
	// second.assign(4, 200);

	// std::cout << "The contents of vector are:";
	// for (ft::vector<int>::iterator it = second.begin(); it != second.end(); ++it)
	// 	std::cout << ' ' << *it;
	// std::cout << '\n';
	// std::vector<int> std_vect;
	// std_vect.push_back(2);
	// std_vect.push_back(3);
	// std_vect.push_back(4);
	// std_vect.push_back(5);
	// std_vect.push_back(6);
	// // std_vect.assign(-1, 20);
	// std_vect.insert (std_vect.begin() + 1,std_vect.begin() + 2, std_vect.begin() + 3);

	// for (std::vector<int>::iterator it = std_vect.begin(); it != std_vect.end(); it++)
	// 	std::cout << *it << std::endl;
	// std::cout << "my: " << vect[1] << std::endl;
	// std::cout << "std: " << std_vect[1] << std::endl;

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
