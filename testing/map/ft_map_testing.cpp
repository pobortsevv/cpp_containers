#include <iostream>
#include <vector>
#include <map>

#include "ft_map.hpp"
#include "testing.hpp"

template <class KEY, class VAL>
void print_map(ft::map<int, Test> & map) {
	typename ft::map<int, Test>::iterator it(map.begin());

	std::cout
			<< "empty: " << map.empty()
			<< " size: "  << map.size() << "\n"
			<< "map:\n";
	size_t i = 0;
	while (it != map.end()) {
		if (i != 0 && i % 8 == 0) {
			std::cout << "\n";
		}
		std::cout << "key: "  << (*it).first
				  << " val: " << (*it).second.some_ << " | ";
		++i;
		++it;
	}
	std::cout << std::endl;
}

void default_constructor() {
	std::cout << "default_constructor" << std::endl;
	ft::map<int, Test> def;

	print_map<int, Test>(def);
}

void constructor_first_last() {
	std::cout << "constructor_first_last" << std::endl;
	std::vector<std::pair<int, Test> > src;

	for (int i = 0; i < 20; ++i) {
		src.push_back(std::pair<int, Test>(i, i));
		src.push_back(std::pair<int, Test>(i, i));
	}

	ft::map<int, Test> def(src.begin(), src.end());

	print_map<int, Test>(def);

}

void copy_constructor() {
	std::cout << "copy_constructor" << std::endl;
	std::vector<std::pair<int, Test> > src;

	for (int i = 0; i < 20; ++i) {
		src.push_back(std::pair<int, Test>(i, i));
		src.push_back(std::pair<int, Test>(i, i));
	}

	ft::map<int, Test> def(src.begin(), src.end());
	ft::map<int, Test> copy_def(def);

	print_map<int, Test>(copy_def);
}

void brackets() {
	std::cout << "brackets" << std::endl;
	std::vector<std::pair<int, Test> > src;

	for (int i = 0; i < 20; ++i) {
		src.push_back(std::pair<int, Test>(i, i));
		src.push_back(std::pair<int, Test>(i, i));
	}

	ft::map<int, Test> def(src.begin(), src.end());

	for (size_t i = 0; i < def.size(); ++i) {
		std::cout << def[i].some_ << " ";
	}
	std::cout << std::endl;

}

void insert_val() {
	std::cout << "insert_val" << std::endl;
	ft::map<int, Test>           def;
	ft::map<int, Test>::iterator it;

	for (int i = 0; i < 20; ++i) {
		if (i != 0 && i % 8 == 0) {
			std::cout << std::endl;
		}
		it = def.insert(std::pair<int, Test>(i, i)).first;
		std::cout
		<< "key: "  <<  (*it).first
		<< " val: " << (*it).second.some_ << " | ";
		def.insert(std::pair<int, Test>(i, i));
	}
	std::cout << std::endl;

	print_map<int, Test>(def);
}

void insert_position_val() {
	std::cout << "insert_position_val" << std::endl;
	ft::map<int, Test>           def;
	ft::map<int, Test>::iterator it;

	for (int i = 0; i < 20; ++i) {
		if (i != 0 && i % 8 == 0) {
			std::cout << std::endl;
		}
		it = def.insert(def.begin(), std::pair<int, Test>(i, i));
		it = def.insert(def.begin(), std::pair<int, Test>(i, i));
		std::cout
				<< "key: "  <<  (*it).first
				<< " val: " << (*it).second.some_ << " | ";
		def.insert(std::pair<int, Test>(i, i));
	}
	std::cout << std::endl;

	print_map<int, Test>(def);

}

void insert_first_last() {
	std::cout << "insert_first_last" << std::endl;
	std::vector<std::pair<int, Test> > src;

	for (int i = 0; i < 20; ++i) {
		src.push_back(std::pair<int, Test>(i, i));
		src.push_back(std::pair<int, Test>(i, i));
	}

	ft::map<int, Test> def;

	def.insert(src.begin(), src.end());
	print_map<int, Test>(def);
}

void erase_position() {
	std::cout << "erase_position" << std::endl;
	std::vector<std::pair<int, Test> > src;

	for (int i = 0; i < 20; ++i) {
		src.push_back(std::pair<int, Test>(i, i));
		src.push_back(std::pair<int, Test>(i, i));
	}

	ft::map<int, Test>           def(src.begin(), src.end());

	def.erase(def.begin());

	ft::map<int, Test>::iterator it(def.begin());

	++it; ++it; ++it;
	def.erase(it);
	it = def.end();
	--it;
	def.erase(it);
	print_map<int, Test>(def);
}

void erase_key() {
	std::cout << "erase_key" << std::endl;
	std::vector<std::pair<int, Test> > src;

	for (int i = 0; i < 20; ++i) {
		src.push_back(std::pair<int, Test>(i, i));
		src.push_back(std::pair<int, Test>(i, i));
	}

	ft::map<int, Test>           def(src.begin(), src.end());

	for (int i = 0; i < 20 ; i += 2) {
		std::cout << def.erase(i) << std::endl;
	}
	std::cout << def.erase(100) << std::endl;
	print_map<int, Test>(def);

}

void erase_firts_last() {
	std::cout << "erase_firts_last" << std::endl;
	std::vector<std::pair<int, Test> > src;

	for (int i = 0; i < 20; ++i) {
		src.push_back(std::pair<int, Test>(i, i));
		src.push_back(std::pair<int, Test>(i, i));
	}

	ft::map<int, Test>           def(src.begin(), src.end());
	ft::map<int, Test>::iterator first(def.begin());
	ft::map<int, Test>::iterator last(def.end());

	++first; ++first; ++first; ++first;
	--last; --last; --last; --last;

	def.erase(first, last);
	print_map<int, Test>(def);
	def.erase(def.begin(), def.end());
	print_map<int, Test>(def);

}

void swap() {
	std::cout << "swap" << std::endl;
	std::vector<std::pair<int, Test> > src;
	std::vector<std::pair<int, Test> > src2;

	for (int i = 0; i < 20; i += 2) {
		src.push_back(std::pair<int, Test>(i, i));
		src.push_back(std::pair<int, Test>(i, i));
	}

	for (int i = 1; i < 20; i += 2) {
		src2.push_back(std::pair<int, Test>(i, i));
		src2.push_back(std::pair<int, Test>(i, i));
	}

	ft::map<int, Test>           def(src.begin(), src.end());
	ft::map<int, Test>           def2(src2.begin(), src2.end());

	def.swap(def2);
	print_map<int, Test>(def);
	print_map<int, Test>(def2);

}

void clear() {
	std::cout << "clear" << std::endl;
	std::vector<std::pair<int, Test> > src;

	for (int i = 0; i < 20; ++i) {
		src.push_back(std::pair<int, Test>(i, i));
		src.push_back(std::pair<int, Test>(i, i));
	}

	ft::map<int, Test> def(src.begin(), src.end());

	def.clear();
	print_map<int, Test>(def);

}

void find() {
	std::cout << "find" << std::endl;
	std::vector<std::pair<int, Test> > src;

	for (int i = 0; i < 20; ++i) {
		src.push_back(std::pair<int, Test>(i, i));
		src.push_back(std::pair<int, Test>(i, i));
	}

	ft::map<int, Test> def(src.begin(), src.end());

	std::cout << (*def.find(0)).second.some_ << std::endl;
	std::cout << (*def.find(15)).second.some_ << std::endl;
	std::cout << (def.end() == def.find(99)) << std::endl;

}

void count() {
	std::cout << "count" << std::endl;
	std::vector<std::pair<int, Test> > src;
	for (int i = 0; i < 20; ++i) {
		src.push_back(std::pair<int, Test>(i, i));
		src.push_back(std::pair<int, Test>(i, i));
	}

	ft::map<int, Test> def(src.begin(), src.end());

	std::cout << def.count(0) << std::endl;
	std::cout << def.count(15) << std::endl;
	std::cout << def.count(99) << std::endl;
}

void lower_bound() {
	std::cout << "lower_bound" << std::endl;
	std::vector<std::pair<int, Test> > src;
	for (int i = 0; i < 20; ++i) {
		src.push_back(std::pair<int, Test>(i, i));
		src.push_back(std::pair<int, Test>(i, i));
	}

	ft::map<int, Test> def(src.begin(), src.end());

	std::cout << (*def.lower_bound(0)).second.some_ << std::endl;
	std::cout << (*def.lower_bound(15)).second.some_ << std::endl;
	std::cout << (def.lower_bound(99) == def.end()) << std::endl;

}

void upper_bound() {
	std::cout << "upper_bound" << std::endl;
	std::vector<std::pair<int, Test> > src;
	for (int i = 0; i < 20; ++i) {
		src.push_back(std::pair<int, Test>(i, i));
		src.push_back(std::pair<int, Test>(i, i));
	}

	ft::map<int, Test> def(src.begin(), src.end());

	std::cout << (*def.upper_bound(0)).second.some_ << std::endl;
	std::cout << (*def.upper_bound(15)).second.some_ << std::endl;
	std::cout << (def.upper_bound(99) == def.end()) << std::endl;
}

void equal_range() {
	std::cout << "equal_range" << std::endl;
	std::vector<std::pair<int, Test> > src;
	for (int i = 0; i < 20; ++i) {
		src.push_back(std::pair<int, Test>(i, i));
		src.push_back(std::pair<int, Test>(i, i));
	}

	ft::map<int, Test> def(src.begin(), src.end());

	std::pair<ft::map<int, Test>::iterator, ft::map<int, Test>::iterator>
	        pair1(def.equal_range(5));

	while (pair1.first != pair1.second) {
		std::cout << (*(pair1.first)).second.some_ << std::endl;
		++pair1.first;
	}

	std::pair<ft::map<int, Test>::iterator, ft::map<int, Test>::iterator>
			pair2(def.equal_range(99));

	while (pair2.first != pair2.second) {
		std::cout << (*(pair2.first)).second.some_ << std::endl;
		++pair2.first;
	}
}

void reverse_iterator() {
	std::cout << "reverse_iterator" << std::endl;
	std::vector<std::pair<int, Test> > src;
	for (int i = 0; i < 20; ++i) {
		src.push_back(std::pair<int, Test>(i, i));
		src.push_back(std::pair<int, Test>(i, i));
	}

	ft::map<int, Test>                   def(src.begin(), src.end());
	ft::map<int, Test>::reverse_iterator rit(def.rbegin());

	while (rit != def.rend()) {
		std::cout << (*rit).second.some_ << " ";
		++rit;
	}
	std::cout << std::endl;
}

int main() {
	// Constructors
	default_constructor();
	constructor_first_last();
	copy_constructor();
	// ------------

	// Element access
	brackets();
	// ------------

	//Modifiers
	insert_val();
	insert_position_val();
	insert_first_last();
	erase_position();
	erase_key();
	erase_firts_last();
	swap();
	clear();
	// ------------

	// Operations
	find();
	count();
	lower_bound();
	upper_bound();
	equal_range();
	// ------------
	reverse_iterator();
	return 0;
}
