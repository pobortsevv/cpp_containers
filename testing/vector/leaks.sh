#! /bin/zsh
mkdir logs

clang++ -Wall -Wextra -Werror -I ../../impliment -I ../../utils -I ../../testing ft_vector_testing.cpp -o logs/user_bin_for_leaks &&
leaks -atExit -- logs/user_bin_for_leaks