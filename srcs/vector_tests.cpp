/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_tests.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pohl <pohl@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 09:47:15 by pohl              #+#    #+#             */
/*   Updated: 2022/02/03 14:54:05 by pohl             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

#include <typeinfo>
#include <list>
#include <vector>
#include "vector.hpp"
#include "CppUTest/TestHarness.h"
#include "CppUTest/UtestMacros.h"

template< typename StdContainer, typename FtContainer >
void	compareContent( StdContainer stdVector, FtContainer ftContainer, bool print = false )
{
	typename StdContainer::iterator	std_begin, std_end;
	typename FtContainer::iterator	ft_begin, ft_end;
	std_begin = stdVector.begin();
	std_end = stdVector.end();
	ft_begin = ftContainer.begin();
	ft_end = ftContainer.end();
	if (print)
		std::cout << "std | ft" << std::endl;
	while (std_begin != std_end)
	{
		if (!print)
			CHECK_EQUAL(*std_begin, *ft_begin);
		if (print)
			std::cout << *std_begin << " | " << *ft_begin << std::endl;
		std_begin++;
		ft_begin++;
	}
}

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
	std::list<int>				int_list(5, 42);
	std::list<std::string>		string_list(3, "Poet");
	std::vector<int>			std_int_vector(int_list.begin(), int_list.end());
	ft::vector<int>				ft_int_vector(int_list.begin(), int_list.end());
	std::vector<std::string>	std_string_vector(string_list.begin(), string_list.end());
	ft::vector<std::string>		ft_string_vector(string_list.begin(), string_list.end());

	CHECK_EQUAL(std_int_vector.size(), ft_int_vector.size());
	CHECK_EQUAL(std_string_vector.size(), ft_string_vector.size());
	compareContent(std_int_vector, ft_int_vector);
	compareContent(std_string_vector, ft_string_vector);

	int_list.clear();
	string_list.clear();

	CHECK_EQUAL(std_int_vector.size(), ft_int_vector.size());
	CHECK_EQUAL(std_string_vector.size(), ft_string_vector.size());
	ft_int_vector.insert(ft_int_vector.begin(), 21);
	std_int_vector.insert(std_int_vector.begin(), 21);
	compareContent(std_int_vector, ft_int_vector);
	compareContent(std_string_vector, ft_string_vector);

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

TEST(VectorMemberFunctions, EqualOperator)
{
	std::vector<int>			std_int_vector(21, 4);
	ft::vector<int>				ft_int_vector(21, 4);
	std::vector<std::string>	std_string_vector(21, "ft");
	ft::vector<std::string>		ft_string_vector(21, "ft");

	std::vector<int>			std_int_copy_vector;
	ft::vector<int>				ft_int_copy_vector;
	std::vector<std::string>	std_string_copy_vector;
	ft::vector<std::string>		ft_string_copy_vector;

	std_int_copy_vector = std_int_vector;
	ft_int_copy_vector = ft_int_vector;
	std_string_copy_vector = std_string_vector;
	ft_string_copy_vector = ft_string_vector;

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

TEST_GROUP(VectorIterators)
{
	std::list<std::string>		string_list;
	std::vector<int>			std_int_vector;
	ft::vector<int>				ft_int_vector;
	std::vector<std::string>	std_string_vector;
	ft::vector<std::string>		ft_string_vector;

	std::vector<int>::iterator			std_int_vector_iterator;
	ft::vector<int>::iterator			ft_int_vector_iterator;
	std::vector<std::string>::iterator	std_string_vector_iterator;
	ft::vector<std::string>::iterator	ft_string_vector_iterator;

	void setup()
	{
		for (int i = 0; i < 21; i++)
		{
			std_int_vector.push_back(i * 2);
			ft_int_vector.push_back(i * 2);
		}
		string_list.push_back("Hi");
		string_list.push_back("How are you?");
		string_list.push_back("I'm fine and you?");
		string_list.push_back("Really good thanks. And you?");
		string_list.push_back("Amazing, I just finished ft_services!");
		string_list.push_back("That's cool! Me too");
		std_string_vector = std::vector<std::string>(string_list.begin(), string_list.end());
		ft_string_vector = ft::vector<std::string>(string_list.begin(), string_list.end());
	}
};

TEST(VectorIterators, Begin)
{
	std_int_vector_iterator = std_int_vector.begin();
	ft_int_vector_iterator = ft_int_vector.begin();
	std_string_vector_iterator = std_string_vector.begin();
	ft_string_vector_iterator = ft_string_vector.begin();

	CHECK_EQUAL(*std_int_vector_iterator, *ft_int_vector_iterator);
	CHECK_EQUAL(*std_string_vector_iterator, *ft_string_vector_iterator);

	std_int_vector.insert(std_int_vector.begin(), 63);
	ft_int_vector.insert(ft_int_vector.begin(), 63);
	std_string_vector.insert(std_string_vector.begin(), "asdf");
	ft_string_vector.insert(ft_string_vector.begin(), "asdf");

	std_int_vector_iterator = std_int_vector.begin();
	ft_int_vector_iterator = ft_int_vector.begin();
	std_string_vector_iterator = std_string_vector.begin();
	ft_string_vector_iterator = ft_string_vector.begin();

	CHECK_EQUAL(*std_int_vector_iterator, *ft_int_vector_iterator);
	CHECK_EQUAL(*std_string_vector_iterator, *std_string_vector_iterator);
}


/* for insertion tests */
/* 	compareContent(std_int_vector, ft_int_vector); */
/* 	std_int_vector.insert(std_int_vector.begin(), 4, 3); */
/* 	ft_int_vector.insert(ft_int_vector.begin(), 4, 3); */
/* 	compareContent(std_int_vector, ft_int_vector); */
/* 	std_int_vector.insert(std_int_vector.begin(), 4); */
/* 	ft_int_vector.insert(ft_int_vector.begin(), 4); */
/* 	compareContent(std_int_vector, ft_int_vector); */
/* 	std_int_vector.insert(std_int_vector.begin(), 5); */
/* 	ft_int_vector.insert(ft_int_vector.begin(), 5); */
/* 	compareContent(std_int_vector, ft_int_vector); */
/* 	ft_string_vector.insert(ft_string_vector.begin(), "HI"); */
/* 	std_string_vector.insert(std_string_vector.begin(), "HI"); */
/* 	compareContent(std_string_vector, ft_string_vector); */
/* 	ft_string_vector.insert(ft_string_vector.begin(), "FUCK"); */
/* 	std_string_vector.insert(std_string_vector.begin(), "FUCK"); */
/* 	compareContent(std_string_vector, ft_string_vector); */
