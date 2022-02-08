/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_tests.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pohl <pohl@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 08:59:01 by pohl              #+#    #+#             */
/*   Updated: 2022/02/08 13:07:33 by pohl             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <typeinfo>
#include <list>
#include <map>
#include "map.hpp"
#include "CppUTest/TestHarness.h"
#include "CppUTest/UtestMacros.h"

TEST_GROUP(MapMemberFunctions)
{
};

TEST(MapMemberFunctions, EmptyConstructor)
{
	std::map<int, char>			std_char_map;
	ft::map<int, char>			ft_char_map;
	std::map<std::string, int>	std_string_map;
	ft::map<std::string, int>	string_map;
	(void)std_char_map; (void)ft_char_map;
	(void)std_string_map; (void)string_map;
}
