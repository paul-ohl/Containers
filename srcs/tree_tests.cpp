/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_tests.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pohl <pohl@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 13:00:50 by pohl              #+#    #+#             */
/*   Updated: 2022/02/08 17:33:44 by pohl             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <cstdlib>
#include "map.hpp"
#include "CppUTest/TestHarness.h"
#include "CppUTest/UtestMacros.h"

TEST_GROUP(TreeVisualisations)
{
	ft::map<int, char>			ft_char_map;
};

IGNORE_TEST(TreeVisualisations, OneByOne)
{
	int inputKey;
	char mapped = 'a';

	while (1)
	{
		std::cout << "Write key: ";
		std::cin >> inputKey;
		ft_char_map.insert(inputKey, mapped);
		ft_char_map.printTree();
	}
}

TEST(TreeVisualisations, RandomFill)
{
	int		amount;
	int		key;
	char	mapped;

	amount = 100;
	std::cout << "How many nodes? ";
	std::cin >> amount;
	for (int i = 0; i < amount; i++)
	{
		key = rand() % amount * 5;
		mapped = rand() % 26 + 97;
		ft_char_map.insert(key, mapped);
	}
	ft_char_map.printTree();
}
