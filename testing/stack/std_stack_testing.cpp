#include <iostream>

#include <stack>

void std_stack_testing() {
	std::stack<int> cont;

	std::cout << cont.empty() << std::endl;
	std::cout << cont.size() << std::endl;

	for (int i = 0; i < 10; ++i) {
		cont.push(i);
	}

	std::cout << cont.empty() << std::endl;
	std::cout << cont.size() << std::endl;
	for (int i = 0; i < 10; ++i) {
		std::cout << cont.top() << " ";
		cont.pop();
	}

	std::cout << cont.empty() << std::endl;
	std::cout << cont.size() << std::endl;
}

int main(void) {
	std_stack_testing();

	return 0;
}
