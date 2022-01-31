/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_tests.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pohl <pohl@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 11:01:45 by pohl              #+#    #+#             */
/*   Updated: 2022/01/31 13:29:43 by pohl             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

#include <typeinfo>
#include "CppUTest/TestHarness.h"
#include "CppUTest/UtestMacros.h"
#include <list>
#include <stack>
#include "stack.hpp"

TEST_GROUP(StackMemberFunctions)
{
};

TEST(StackMemberFunctions, EmptyConstructor)
{
	std::stack<int>	std_int_stack;
	ft::stack<int>	int_stack;
	std::stack<std::string>	std_string_stack;
	ft::stack<std::string>	string_stack;
	std::stack<int, std::list<int> >	std_list_stack;
	ft::stack<int, std::list<int> >		list_stack;

	CHECK_TRUE( typeid(std::stack<int, std::list<int> >::container_type) == typeid(ft::stack<int, std::list<int> >::container_type) );
}

TEST(StackMemberFunctions, ContainerConstructor)
{
	std::list<int>	std_int_list(10, 2);

	std::stack<int, std::list<int> >	std_int_stack(std_int_list);
	ft::stack<int, std::list<int> >		int_stack(std_int_list);


	std::list<std::string>	std_string_list(10, "hi");

	std::stack<std::string, std::list<std::string> >	std_string_stack(std_string_list);
	ft::stack<std::string, std::list<std::string> >		string_stack(std_string_list);
}

TEST(StackMemberFunctions, CopyConstructor)
{
	std::stack<int>	std_int_stack;
	std::stack<int> std_copy_stack(std_int_stack);
	ft::stack<int>	int_stack;
	ft::stack<int>	int_copy_stack(int_stack);
}

TEST(StackMemberFunctions, EqualOperator)
{
	std::stack<int>	std_int_stack;
	std::stack<int> std_copy_stack;
	std_int_stack = std_copy_stack;
	ft::stack<int>	int_stack;
	ft::stack<int>	int_copy_stack;
	int_stack = int_copy_stack;
}

TEST_GROUP(StackMemberTypes)
{
};

TEST(StackMemberTypes, TestTypes)
{
	CHECK_TRUE( (typeid(std::stack<int>::container_type) == typeid(ft::stack<int>::container_type)) );
	CHECK_TRUE( (typeid(std::stack<int>::value_type) == typeid(ft::stack<int>::value_type)) );
	CHECK_TRUE( (typeid(std::stack<int>::size_type) == typeid(ft::stack<int>::size_type)) );
	CHECK_TRUE( (typeid(std::stack<int>::reference) == typeid(ft::stack<int>::reference)) );
	CHECK_TRUE( (typeid(std::stack<int>::const_reference) == typeid(ft::stack<int>::const_reference)) );
	CHECK_TRUE( (typeid(std::stack<std::string>::container_type) == typeid(ft::stack<std::string>::container_type)) );
	CHECK_TRUE( (typeid(std::stack<std::string>::value_type) == typeid(ft::stack<std::string>::value_type)) );
	CHECK_TRUE( (typeid(std::stack<std::string>::size_type) == typeid(ft::stack<std::string>::size_type)) );
	CHECK_TRUE( (typeid(std::stack<std::string>::reference) == typeid(ft::stack<std::string>::reference)) );
	CHECK_TRUE( (typeid(std::stack<std::string>::const_reference) == typeid(ft::stack<std::string>::const_reference)) );
}

TEST_GROUP(StackAccessors)
{
	std::list<int>			int_list;
	std::list<std::string>	string_list;

	void	setup()
	{
		for (int i = 0; i <= 48; i += 7)
			int_list.push_back(i);
		string_list.push_back("Hi");
		string_list.push_back("How are you?");
		string_list.push_back("I'm fine and you?");
		string_list.push_back("Really good thanks. And you?");
		string_list.push_back("Amazing, I just finished ft_services!");
		string_list.push_back("That's cool! Me too");
	}
};

TEST(StackAccessors, Top)
{
	std::stack<int, std::list<int> >					std_int_stack(int_list);
	std::stack<std::string, std::list<std::string> >	std_string_stack(string_list);
	ft::stack<int, std::list<int> >						ft_int_stack(int_list);
	ft::stack<std::string, std::list<std::string> >		ft_string_stack(string_list);

	CHECK_EQUAL(std_int_stack.top(), ft_int_stack.top());
	CHECK_EQUAL(std_string_stack.top(), ft_string_stack.top());
}
