/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_tests.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pohl <pohl@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 09:47:15 by pohl              #+#    #+#             */
/*   Updated: 2022/02/02 09:51:22 by pohl             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <list>
#include <vector>
#include "vector.hpp"
#include "CppUTest/TestHarness.h"
#include "CppUTest/UtestMacros.h"

TEST_GROUP(VectorMemberFunctions)
{
};

TEST(VectorMemberFunctions, EmptyConstructor)
{
	std::vector<int>	std_int_vector;
	ft::vector<int>		int_vector;
	std::vector<std::string>	std_string_vector;
	ft::vector<std::string>		string_vector;

	(void)std_int_vector; (void)int_vector;
	(void)std_string_vector; (void)string_vector;
}
