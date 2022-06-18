/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabra <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 00:28:30 by sabra             #+#    #+#             */
/*   Updated: 2022/06/18 00:28:32 by sabra            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <vector>
#include "ft_vector.hpp"
#include "red_black_tree.hpp"
#include "testing.hpp"
#include <map>
#include <bitset>

int main(void) {
	std::cout << "\n================FT================\n" << std::endl;
	ft_stack_testing();

	std::cout << "\n================STD================\n" << std::endl;
	std_stack_testing();

	return 0;
}
