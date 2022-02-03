/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_tests.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pohl <pohl@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 09:47:15 by pohl              #+#    #+#             */
/*   Updated: 2022/02/03 10:12:19 by pohl             ###   ########.fr       */
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

TEST(VectorMemberFunctions, ValueConstructorSizeOnly)
{
	std::vector<int>			std_int_vector(21);
	ft::vector<int>				ft_int_vector(21);
	std::vector<std::string>	std_string_vector(21);
	ft::vector<std::string>		ft_string_vector(21);

	CHECK_EQUAL(std_int_vector.size(), ft_int_vector.size());
	CHECK_EQUAL(std_string_vector.size(), ft_string_vector.size());
	CHECK_EQUAL(std_int_vector.front(), ft_int_vector.front());
	CHECK_EQUAL(std_string_vector.front(), ft_string_vector.front());
}

TEST(VectorMemberFunctions, ValueConstructorSizeWithValue)
{
	std::vector<int>			std_int_vector(21, 4);
	ft::vector<int>				ft_int_vector(21, 4);
	std::vector<std::string>	std_string_vector(21, "ft");
	ft::vector<std::string>		ft_string_vector(21, "ft");

	CHECK_EQUAL(std_int_vector.size(), ft_int_vector.size());
	CHECK_EQUAL(std_string_vector.size(), ft_string_vector.size());
	CHECK_EQUAL(std_int_vector.front(), ft_int_vector.front());
	CHECK_EQUAL(std_string_vector.front(), ft_string_vector.front());
	CHECK_EQUAL(std_int_vector.back(), ft_int_vector.back());
	CHECK_EQUAL(std_string_vector.back(), ft_string_vector.back());
}

TEST(VectorMemberFunctions, ValueConstructorIteratorRange)
{
	std::list<int>				int_list(21, 42);
	std::list<std::string>		string_list(21, "ft");
	std::vector<int>			std_int_vector(int_list.begin(), int_list.end());
	ft::vector<int>				ft_int_vector(int_list.begin(), int_list.end());
	std::vector<std::string>	std_string_vector(string_list.begin(), string_list.end());
	ft::vector<std::string>		ft_string_vector(string_list.begin(), string_list.end());

	CHECK_EQUAL(std_int_vector.size(), ft_int_vector.size());
	CHECK_EQUAL(std_string_vector.size(), ft_string_vector.size());
	CHECK_EQUAL(std_int_vector.front(), ft_int_vector.front());
	CHECK_EQUAL(std_string_vector.front(), ft_string_vector.front());
	CHECK_EQUAL(std_int_vector.back(), ft_int_vector.back());
	CHECK_EQUAL(std_string_vector.back(), ft_string_vector.back());
}

TEST(VectorMemberFunctions, CopyConstructor)
{
	std::vector<int>			std_int_vector(21, 4);
	ft::vector<int>				ft_int_vector(21, 4);
	std::vector<std::string>	std_string_vector(21, "ft");
	ft::vector<std::string>		ft_string_vector(21, "ft");

	std::vector<int>			std_int_copy_vector(std_int_vector);
	ft::vector<int>				ft_int_copy_vector(ft_int_vector);
	std::vector<std::string>	std_string_copy_vector(std_string_vector);
	ft::vector<std::string>		ft_string_copy_vector(ft_string_vector);

	CHECK_EQUAL(std_int_copy_vector.size(), ft_int_copy_vector.size());
	CHECK_EQUAL(std_string_copy_vector.size(), ft_string_copy_vector.size());
	CHECK_EQUAL(std_int_copy_vector.front(), ft_int_copy_vector.front());
	CHECK_EQUAL(std_string_copy_vector.front(), ft_string_copy_vector.front());
	CHECK_EQUAL(std_int_copy_vector.back(), ft_int_copy_vector.back());
	CHECK_EQUAL(std_string_copy_vector.back(), ft_string_copy_vector.back());

	std_int_vector.pop_back();
	ft_int_vector.pop_back();
	std_string_vector.pop_back();
	ft_string_vector.pop_back();

	CHECK_EQUAL(std_int_copy_vector.size(), ft_int_copy_vector.size());
	CHECK_EQUAL(std_string_copy_vector.size(), ft_string_copy_vector.size());
	CHECK_EQUAL(std_int_copy_vector.front(), ft_int_copy_vector.front());
	CHECK_EQUAL(std_string_copy_vector.front(), ft_string_copy_vector.front());
	CHECK_EQUAL(std_int_copy_vector.back(), ft_int_copy_vector.back());
	CHECK_EQUAL(std_string_copy_vector.back(), ft_string_copy_vector.back());
}

TEST(VectorMemberFunctions, ValueConstructorTricky)
{
	std::vector<int>			std_int_vector(0, 4);
	ft::vector<int>				ft_int_vector(0, 4);
	std::vector<std::string>	std_string_vector(21, "42");
	ft::vector<std::string>		ft_string_vector(21, "42");
	std::vector<std::string>	std_string_copy_vector(std_string_vector.begin(), std_string_vector.end());
	ft::vector<std::string>		ft_string_copy_vector(ft_string_vector.begin(), ft_string_vector.end());

	CHECK_EQUAL(std_int_vector.size(), ft_int_vector.size());
	CHECK_EQUAL(std_string_copy_vector.size(), ft_string_copy_vector.size());
	CHECK_EQUAL(std_string_copy_vector.front(), ft_string_copy_vector.front());
	CHECK_EQUAL(std_string_copy_vector.back(), ft_string_copy_vector.back());
}
