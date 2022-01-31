/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_tests.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pohl <pohl@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 11:01:45 by pohl              #+#    #+#             */
/*   Updated: 2022/01/31 14:20:26 by pohl             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

#include <typeinfo>
#include <list>
#include <ctime>
#include <stack>
#include "stack.hpp"
#include "CppUTest/TestHarness.h"
#include "CppUTest/UtestMacros.h"
#include "testUtils.hpp"

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
	std::stack<int>			std_empty_int_stack;
	std::stack<std::string>	std_empty_string_stack;
	ft::stack<int>			ft_empty_int_stack;
	ft::stack<std::string>	ft_empty_string_stack;


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

TEST(StackAccessors, Size)
{
	std::stack<int, std::list<int> >					std_int_stack(int_list);
	std::stack<std::string, std::list<std::string> >	std_string_stack(string_list);
	ft::stack<int, std::list<int> >						ft_int_stack(int_list);
	ft::stack<std::string, std::list<std::string> >		ft_string_stack(string_list);

	CHECK_EQUAL(std_int_stack.size(), ft_int_stack.size());
	CHECK_EQUAL(std_string_stack.size(), ft_string_stack.size());
	CHECK_EQUAL(std_empty_int_stack.size(), ft_empty_int_stack.size());
	CHECK_EQUAL(std_empty_string_stack.size(), ft_empty_string_stack.size());
}

TEST(StackAccessors, Empty)
{
	std::stack<int, std::list<int> >					std_int_stack(int_list);
	std::stack<std::string, std::list<std::string> >	std_string_stack(string_list);
	ft::stack<int, std::list<int> >						ft_int_stack(int_list);
	ft::stack<std::string, std::list<std::string> >		ft_string_stack(string_list);

	CHECK_EQUAL(std_int_stack.empty(), ft_int_stack.empty());
	CHECK_EQUAL(std_string_stack.empty(), ft_string_stack.empty());
	CHECK_EQUAL(std_empty_int_stack.empty(), ft_empty_int_stack.empty());
	CHECK_EQUAL(std_empty_string_stack.empty(), ft_empty_string_stack.empty());
}

TEST_GROUP(StackModifiers)
{
	std::stack<int>			std_int_stack;
	std::stack<std::string>	std_string_stack;
	ft::stack<int>			ft_int_stack;
	ft::stack<std::string>	ft_string_stack;
};

TEST(StackModifiers, Push)
{
	CHECK_EQUAL(std_int_stack.size(), ft_int_stack.size());
	std_int_stack.push(1);
	ft_int_stack.push(1);
	CHECK_EQUAL(std_int_stack.top(), ft_int_stack.top());
	CHECK_EQUAL(std_int_stack.size(), ft_int_stack.size());
	std_int_stack.push(2);
	ft_int_stack.push(2);
	CHECK_EQUAL(std_int_stack.top(), ft_int_stack.top());
	CHECK_EQUAL(std_int_stack.size(), ft_int_stack.size());
	std_int_stack.push(12);
	ft_int_stack.push(12);
	CHECK_EQUAL(std_int_stack.top(), ft_int_stack.top());
	CHECK_EQUAL(std_int_stack.size(), ft_int_stack.size());
	std_int_stack.push(21);
	ft_int_stack.push(21);
	CHECK_EQUAL(std_int_stack.top(), ft_int_stack.top());
	CHECK_EQUAL(std_int_stack.size(), ft_int_stack.size());
	std_int_stack.push(42);
	ft_int_stack.push(42);
	CHECK_EQUAL(std_int_stack.top(), ft_int_stack.top());
	CHECK_EQUAL(std_int_stack.size(), ft_int_stack.size());
}

TEST(StackModifiers, Pop)
{
	std_int_stack.push(1);
	ft_int_stack.push(1);
	std_int_stack.push(2);
	ft_int_stack.push(2);
	std_int_stack.push(12);
	ft_int_stack.push(12);
	std_int_stack.push(21);
	ft_int_stack.push(21);
	std_int_stack.push(42);
	ft_int_stack.push(42);
	CHECK_EQUAL(std_int_stack.top(), ft_int_stack.top());
	CHECK_EQUAL(std_int_stack.size(), ft_int_stack.size());
	std_int_stack.pop();
	ft_int_stack.pop();
	CHECK_EQUAL(std_int_stack.top(), ft_int_stack.top());
	CHECK_EQUAL(std_int_stack.size(), ft_int_stack.size());
	std_int_stack.pop();
	ft_int_stack.pop();
	CHECK_EQUAL(std_int_stack.top(), ft_int_stack.top());
	CHECK_EQUAL(std_int_stack.size(), ft_int_stack.size());
	std_int_stack.pop();
	ft_int_stack.pop();
	CHECK_EQUAL(std_int_stack.top(), ft_int_stack.top());
	CHECK_EQUAL(std_int_stack.size(), ft_int_stack.size());
	std_int_stack.pop();
	ft_int_stack.pop();
	CHECK_EQUAL(std_int_stack.top(), ft_int_stack.top());
	CHECK_EQUAL(std_int_stack.size(), ft_int_stack.size());
	std_int_stack.pop();
	ft_int_stack.pop();
	CHECK_EQUAL(std_int_stack.size(), ft_int_stack.size());
}

IGNORE_TEST(StackModifiers, BigPush)
{
	time_t	time_svg;
	double	std_time, ft_time;

	time_svg = time(NULL);
	for (int i = 0; i < 15000000; i++)
		std_int_stack.push(i);
	std_time = difftime(time(NULL), time_svg);
	time_svg = time(NULL);
	for (int i = 0; i < 15000000; i++)
		ft_int_stack.push(i);
	ft_time = difftime(time(NULL), time_svg);
	CHECK_TEXT(ft_time / std_time < MAX_TIME_DIFFERENCE, getTimeDiffAsString(std_time, ft_time).c_str());
}
