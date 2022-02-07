/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_tests.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pohl <pohl@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 09:47:15 by pohl              #+#    #+#             */
/*   Updated: 2022/02/07 10:27:13 by pohl             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

#include <typeinfo>
#include <list>
#include <vector>
#include "vector.hpp"
#include "CppUTest/TestHarness.h"
#include "CppUTest/UtestMacros.h"

typedef std::vector<int>::iterator			std_int_it;
typedef ft::vector<int>::iterator			ft_int_it;
typedef std::vector<std::string>::iterator	std_string_it;
typedef ft::vector<std::string>::iterator	ft_string_it;

template< typename StdVector, typename FtVector >
void	compareContent( StdVector stdVector, FtVector ftVector, bool print = false )
{
	typename StdVector::iterator	std_begin, std_end;
	typename FtVector::iterator	ft_begin, ft_end;
	std_begin = stdVector.begin();
	std_end = stdVector.end();
	ft_begin = ftVector.begin();
	ft_end = ftVector.end();
	if (print)
		std::cout << "std | ft" << std::endl;
	else
	{
		CHECK_EQUAL(stdVector.size(), ftVector.size());
		CHECK_EQUAL(stdVector.max_size() , ftVector.max_size());
	}
	while (std_begin != std_end)
	{
		if (print)
			std::cout << *std_begin << " | " << *ft_begin << std::endl;
		else
			CHECK_EQUAL(*std_begin, *ft_begin);
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

	compareContent(std_int_vector, ft_int_vector);
	compareContent(std_string_vector, ft_string_vector);
}

TEST(VectorMemberFunctions, ValueConstructorSizeWithValue)
{
	std::vector<int>			std_int_vector(21, 4);
	ft::vector<int>				ft_int_vector(21, 4);
	std::vector<std::string>	std_string_vector(21, "ft");
	ft::vector<std::string>		ft_string_vector(21, "ft");

	compareContent(std_int_vector, ft_int_vector);
	compareContent(std_string_vector, ft_string_vector);
}

TEST(VectorMemberFunctions, ValueConstructorIteratorRange)
{
	std::list<int>				int_list(5, 42);
	std::list<std::string>		string_list(3, "Poet");
	std::vector<int>			std_int_vector(int_list.begin(), int_list.end());
	ft::vector<int>				ft_int_vector(int_list.begin(), int_list.end());
	std::vector<std::string>	std_string_vector(string_list.begin(), string_list.end());
	ft::vector<std::string>		ft_string_vector(string_list.begin(), string_list.end());

	compareContent(std_int_vector, ft_int_vector);
	compareContent(std_string_vector, ft_string_vector);

	int_list.clear();
	string_list.clear();

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

	compareContent(std_int_copy_vector, ft_int_copy_vector);
	compareContent(std_string_copy_vector, ft_string_copy_vector);

	std_int_vector.pop_back();
	ft_int_vector.pop_back();
	std_string_vector.pop_back();
	ft_string_vector.pop_back();

	compareContent(std_int_copy_vector, ft_int_copy_vector);
	compareContent(std_string_copy_vector, ft_string_copy_vector);
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
	compareContent(std_string_copy_vector, ft_string_copy_vector);
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

	std_int_it		std_int_vector_it, std_int_vector_ite;
	ft_int_it		ft_int_vector_it, ft_int_vector_ite;
	std_string_it	std_string_vector_it, std_string_vector_ite;
	ft_string_it	ft_string_vector_it, ft_string_vector_ite;

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

		std_int_vector_it = std_int_vector.begin();
		ft_int_vector_it = ft_int_vector.begin();
		std_string_vector_it = std_string_vector.begin();
		ft_string_vector_it = ft_string_vector.begin();
		std_int_vector_ite = std_int_vector.end();
		ft_int_vector_ite = ft_int_vector.end();
		std_string_vector_ite = std_string_vector.end();
		ft_string_vector_ite = ft_string_vector.end();
	}
};

TEST(VectorIterators, Begin)
{
	CHECK_EQUAL(*std_int_vector_it, *ft_int_vector_it);
	CHECK_EQUAL(*std_string_vector_it, *ft_string_vector_it);

	std_int_vector.insert(std_int_vector.begin(), 63);
	ft_int_vector.insert(ft_int_vector.begin(), 63);
	std_string_vector.insert(std_string_vector.begin(), "asdf");
	ft_string_vector.insert(ft_string_vector.begin(), "asdf");

	std_int_vector_it = std_int_vector.begin();
	ft_int_vector_it = ft_int_vector.begin();
	std_string_vector_it = std_string_vector.begin();
	ft_string_vector_it = ft_string_vector.begin();

	CHECK_EQUAL(*std_int_vector_it, *ft_int_vector_it);
	CHECK_EQUAL(*std_string_vector_it, *std_string_vector_it);
}

TEST(VectorIterators, CopyConstructors)
{
	std_int_it	std_copy_it(std_int_vector_it);
	ft_int_it	ft_copy_it(ft_int_vector_it);

	CHECK_EQUAL(*std_copy_it, *ft_copy_it);
	std_int_vector_it++;
	ft_int_vector_it++;
	CHECK_EQUAL(*std_copy_it, *ft_copy_it);
}

TEST(VectorIterators, IteratorArithmetics)
{
	CHECK_EQUAL(*std_int_vector_it, *ft_int_vector_it);
	CHECK_EQUAL(*std_string_vector_it, *ft_string_vector_it);

	std_int_vector_it++;
	std_string_vector_it++;
	ft_int_vector_it++;
	ft_string_vector_it++;

	CHECK_EQUAL(*std_int_vector_it, *ft_int_vector_it);
	CHECK_EQUAL(*std_string_vector_it, *ft_string_vector_it);

	std_int_vector_it--;
	std_string_vector_it--;
	ft_int_vector_it--;
	ft_string_vector_it--;

	CHECK_EQUAL(*std_int_vector_it, *ft_int_vector_it);
	CHECK_EQUAL(*std_string_vector_it, *ft_string_vector_it);

	std_int_vector_it += 4;
	std_string_vector_it += 4;
	ft_int_vector_it += 4;
	ft_string_vector_it += 4;

	CHECK_EQUAL(*std_int_vector_it, *ft_int_vector_it);
	CHECK_EQUAL(*std_string_vector_it, *ft_string_vector_it);

	std_int_vector_it -= 2;
	std_string_vector_it -= 2;
	ft_int_vector_it -= 2;
	ft_string_vector_it -= 2;

	CHECK_EQUAL(*std_int_vector_it, *ft_int_vector_it);
	CHECK_EQUAL(*std_string_vector_it, *ft_string_vector_it);

	CHECK_EQUAL(*(++std_int_vector_it), *(++ft_int_vector_it));
	CHECK_EQUAL(*(++std_string_vector_it), *(++ft_string_vector_it));

	CHECK_EQUAL(*(--std_int_vector_it), *(--ft_int_vector_it));
	CHECK_EQUAL(*(--std_string_vector_it), *(--ft_string_vector_it));

	CHECK_EQUAL(*(std_int_vector_it++), *(ft_int_vector_it++));
	CHECK_EQUAL(*(std_string_vector_it++), *(ft_string_vector_it++));

	CHECK_EQUAL(*(std_int_vector_it--), *(ft_int_vector_it--));
	CHECK_EQUAL(*(std_string_vector_it--), *(ft_string_vector_it--));

	CHECK_EQUAL(*(3 + std_int_vector_it), *(3 + ft_int_vector_it));
	CHECK_EQUAL(*(3 + std_string_vector_it), *(3 + ft_string_vector_it));

	CHECK_EQUAL(*(std_int_vector_it + 3), *(ft_int_vector_it + 3));
	CHECK_EQUAL(*(std_string_vector_it + 3), *(ft_string_vector_it + 3));

	CHECK_EQUAL(*(std_int_vector_it - 1), *(ft_int_vector_it - 1));
	CHECK_EQUAL(*(std_string_vector_it - 1), *(ft_string_vector_it - 1));

	CHECK_EQUAL(std_int_vector_it[2], ft_int_vector_it[2]);
	CHECK_EQUAL(std_string_vector_it[2], ft_string_vector_it[2]);
}

TEST(VectorIterators, EqualOperator)
{
	std_int_vector_it = std_int_vector_ite - 1;
	ft_int_vector_it = ft_int_vector_ite - 1;
	std_string_vector_it = std_string_vector_ite - 1;
	ft_string_vector_it = ft_string_vector_ite - 1;

	CHECK_EQUAL(*std_int_vector_it, *ft_int_vector_it);
	CHECK_EQUAL(*std_string_vector_it, *ft_string_vector_it);
}

TEST(VectorIterators, Const)
{
	std::vector<int>::const_iterator	std_const_it, std_const_ite;
	ft::vector<int>::const_iterator		ft_const_it, ft_const_ite;
	std::vector<int>::const_iterator	std_const_it_copy(std_int_vector_it);
	ft::vector<int>::const_iterator		ft_const_it_copy(ft_int_vector_it);

	std_const_it = std_int_vector.begin();
	std_const_ite = std_int_vector.end();
	ft_const_it = ft_int_vector.begin();
	ft_const_ite = ft_int_vector.end();

	CHECK_EQUAL(std_int_vector.size(), ft_int_vector.size());
	while (ft_const_it != ft_const_ite)
	{
		CHECK_EQUAL(*std_const_it, *ft_const_it);
		CHECK_EQUAL(*std_const_it_copy, *ft_const_it_copy);
		CHECK_EQUAL((std_const_it == std_int_vector_ite), (ft_const_it == ft_int_vector_ite));
		std_const_it++;
		ft_const_it++;
	}
}

TEST_GROUP(VectorReverseIterators)
{
	std::list<std::string>		string_list;
	std::vector<int>			std_int_vector;
	ft::vector<int>				ft_int_vector;
	std::vector<std::string>	std_string_vector;
	ft::vector<std::string>		ft_string_vector;

	std::vector<int>::reverse_iterator			std_int_vector_rit, std_int_vector_rite;
	ft::vector<int>::reverse_iterator			ft_int_vector_rit, ft_int_vector_rite;
	std::vector<std::string>::reverse_iterator	std_string_vector_rit, std_string_vector_rite;
	ft::vector<std::string>::reverse_iterator	ft_string_vector_rit, ft_string_vector_rite;

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
		std_int_vector_rit = std_int_vector.rbegin();
		ft_int_vector_rit = ft_int_vector.rbegin();
		std_string_vector_rit = std_string_vector.rbegin();
		ft_string_vector_rit = ft_string_vector.rbegin();

		std_int_vector_rite = std_int_vector.rend();
		ft_int_vector_rite = ft_int_vector.rend();
		std_string_vector_rite = std_string_vector.rend();
		ft_string_vector_rite = ft_string_vector.rend();
	}
};

TEST(VectorReverseIterators, RBeginREnd)
{
	CHECK_EQUAL(std_int_vector.size(), ft_int_vector.size());
	while (ft_int_vector_rit != ft_int_vector_rite)
	{
		CHECK_EQUAL(*std_int_vector_rit, *ft_int_vector_rit);
		std_int_vector_rit++;
		ft_int_vector_rit++;
	}
	CHECK(std_int_vector_rit == std_int_vector_rite);

	CHECK_EQUAL(std_string_vector.size(), ft_string_vector.size());
	while (ft_string_vector_rit != ft_string_vector_rite)
	{
		CHECK_EQUAL(*std_string_vector_rit, *ft_string_vector_rit);
		std_string_vector_rit++;
		ft_string_vector_rit++;
	}
	CHECK(std_string_vector_rit == std_string_vector_rite);
}

TEST(VectorReverseIterators, IteratorArithmetics)
{
	CHECK_EQUAL(*std_int_vector_rit, *ft_int_vector_rit);
	CHECK_EQUAL(*std_string_vector_rit, *ft_string_vector_rit);

	std_int_vector_rit++;
	std_string_vector_rit++;
	ft_int_vector_rit++;
	ft_string_vector_rit++;

	CHECK_EQUAL(*std_int_vector_rit, *ft_int_vector_rit);
	CHECK_EQUAL(*std_string_vector_rit, *ft_string_vector_rit);

	std_int_vector_rit--;
	std_string_vector_rit--;
	ft_int_vector_rit--;
	ft_string_vector_rit--;

	CHECK_EQUAL(*std_int_vector_rit, *ft_int_vector_rit);
	CHECK_EQUAL(*std_string_vector_rit, *ft_string_vector_rit);

	std_int_vector_rit += 4;
	std_string_vector_rit += 4;
	ft_int_vector_rit += 4;
	ft_string_vector_rit += 4;

	CHECK_EQUAL(*std_int_vector_rit, *ft_int_vector_rit);
	CHECK_EQUAL(*std_string_vector_rit, *ft_string_vector_rit);

	std_int_vector_rit -= 2;
	std_string_vector_rit -= 2;
	ft_int_vector_rit -= 2;
	ft_string_vector_rit -= 2;

	CHECK_EQUAL(*std_int_vector_rit, *ft_int_vector_rit);
	CHECK_EQUAL(*std_string_vector_rit, *ft_string_vector_rit);

	CHECK_EQUAL(*(++std_int_vector_rit), *(++ft_int_vector_rit));
	CHECK_EQUAL(*(++std_string_vector_rit), *(++ft_string_vector_rit));

	CHECK_EQUAL(*(--std_int_vector_rit), *(--ft_int_vector_rit));
	CHECK_EQUAL(*(--std_string_vector_rit), *(--ft_string_vector_rit));

	CHECK_EQUAL(*(std_int_vector_rit++), *(ft_int_vector_rit++));
	CHECK_EQUAL(*(std_string_vector_rit++), *(ft_string_vector_rit++));

	CHECK_EQUAL(*(std_int_vector_rit--), *(ft_int_vector_rit--));
	CHECK_EQUAL(*(std_string_vector_rit--), *(ft_string_vector_rit--));

	CHECK_EQUAL(*(std_int_vector_rit + 3), *(ft_int_vector_rit + 3));
	CHECK_EQUAL(*(std_string_vector_rit + 3), *(ft_string_vector_rit + 3));

	CHECK_EQUAL(*(std_int_vector_rit - 1), *(ft_int_vector_rit - 1));
	CHECK_EQUAL(*(std_string_vector_rit - 1), *(ft_string_vector_rit - 1));

	CHECK_EQUAL(std_int_vector_rit[2], ft_int_vector_rit[2]);
	CHECK_EQUAL(std_string_vector_rit[2], ft_string_vector_rit[2]);
}

TEST(VectorReverseIterators, EqualOperator)
{
	std_int_vector_rit = std_int_vector_rite - 1;
	ft_int_vector_rit = ft_int_vector_rite - 1;
	std_string_vector_rit = std_string_vector_rite - 1;
	ft_string_vector_rit = ft_string_vector_rite - 1;

}

/* /1* for insertion tests *1/ */
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
