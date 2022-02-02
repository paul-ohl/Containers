/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_tests.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pohl <pohl@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 09:47:15 by pohl              #+#    #+#             */
/*   Updated: 2022/02/02 14:28:28 by pohl             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

#include <typeinfo>
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
	std::vector<int>			std_int_vector;
	ft::vector<int>				ft_int_vector;
	std::vector<std::string>	std_string_vector;
	ft::vector<std::string>		ft_string_vector;

	CHECK_EQUAL(std_int_vector.empty(), ft_int_vector.empty());
	CHECK_EQUAL(std_string_vector.empty(), ft_string_vector.empty());
	CHECK_EQUAL(std_int_vector.capacity(), ft_int_vector.capacity());
	CHECK_EQUAL(std_string_vector.capacity(), ft_string_vector.capacity());
	CHECK_TRUE( typeid(std::vector<int>::allocator_type)
			== typeid(ft::vector<int>::allocator_type) );
}

TEST(VectorMemberFunctions, ValueConstructor1)
{
	std::vector<int>			std_int_vector(12);
	ft::vector<int>				ft_int_vector(12);
	std::vector<std::string>	std_string_vector(12);
	ft::vector<std::string>		ft_string_vector(12);

	CHECK_EQUAL(std_int_vector.size(), ft_int_vector.size());
	CHECK_EQUAL(std_string_vector.size(), ft_string_vector.size());
	CHECK_EQUAL(std_int_vector.front(), ft_int_vector.front());
	CHECK_EQUAL(std_string_vector.front(), ft_string_vector.front());
}

TEST(VectorMemberFunctions, ValueConstructor2)
{
	std::vector<int>			std_int_vector(12, 4);
	ft::vector<int>				ft_int_vector(12, 4);
	std::vector<std::string>	std_string_vector(12, "Bonjour");
	ft::vector<std::string>		ft_string_vector(12, "Bonjour");

	CHECK_EQUAL(std_int_vector.size(), ft_int_vector.size());
	CHECK_EQUAL(std_string_vector.size(), ft_string_vector.size());
	CHECK_EQUAL(std_int_vector.front(), ft_int_vector.front());
	CHECK_EQUAL(std_string_vector.front(), ft_string_vector.front());
	CHECK_EQUAL(std_int_vector.back(), ft_int_vector.back());
	CHECK_EQUAL(std_string_vector.back(), ft_string_vector.back());
}

TEST(VectorMemberFunctions, ValueConstructorTricky)
{
	std::vector<int>			std_int_vector(0, 4);
	ft::vector<int>				ft_int_vector(0, 4);

	CHECK_EQUAL(std_int_vector.size(), ft_int_vector.size());
}
