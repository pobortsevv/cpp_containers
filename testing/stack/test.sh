#! /bin/zsh

rm logs/user.output 2> /dev/null
rm logs/std.output 2> /dev/null
rm -rf logs 
mkdir logs

	clang++ -Wall -Wextra -Werror -I ../../impliment -I ../../utils -I ../ -fsanitize=address ./ft_stack_testing.cpp -o logs/user_bin &&
	./logs/user_bin > logs/user.output &&
	clang++ -Wall -Wextra -Werror -I -fsanitize=address std_stack_testing.cpp -o logs/bin &&
	./logs/bin > logs/std.output &&
	diff logs/user.output logs/std.output