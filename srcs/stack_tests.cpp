/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_tests.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pohl <pohl@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 11:01:45 by pohl              #+#    #+#             */
/*   Updated: 2022/01/31 11:50:32 by pohl             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* #include <iostream> */

#include <typeinfo>
#include "CppUTest/TestHarness.h"
#include "CppUTest/UtestMacros.h"
#include <list>
#include <stack>
#include "stack.hpp"

TEST_GROUP(StackConstructor)
{
};

TEST(StackConstructor, EmptyConstructor)
{
	std::stack<int> std_int_stack;
	ft::stack<int> int_stack;
	std::stack<std::string> std_string_stack;
	ft::stack<std::string> string_stack;
	std::stack<int, std::list<int> > std_list_stack;
	ft::stack<int, std::list<int> > list_stack;
	CHECK_TRUE( typeid(std::stack<int, std::list<int> >::container_type) == typeid(ft::stack<int, std::list<int> >::container_type) );
}

TEST(StackConstructor, ContainerConstructor)
{
	std::list<int> std_list(10, 2);
	std::stack<int, std::list<int> > std_int_stack(std_list);
	ft::stack<int, std::list<int> > int_stack(std_list);
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
