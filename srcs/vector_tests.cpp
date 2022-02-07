/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_tests.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pohl <pohl@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 09:47:15 by pohl              #+#    #+#             */
/*   Updated: 2022/02/07 15:12:25 by pohl             ###   ########.fr       */
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

TEST(VectorReverseIterators, Const)
{
	std::vector<int>::const_reverse_iterator	std_const_rit, std_const_rite;
	ft::vector<int>::const_reverse_iterator		ft_const_rit, ft_const_rite;
	std::vector<int>::const_reverse_iterator	std_const_rit_copy(std_int_vector_rit);
	ft::vector<int>::const_reverse_iterator		ft_const_rit_copy(ft_int_vector_rit);

	std_const_rit = std_int_vector.rbegin();
	std_const_rite = std_int_vector.rend();
	ft_const_rit = ft_int_vector.rbegin();
	ft_const_rite = ft_int_vector.rend();

	CHECK_EQUAL(std_int_vector.size(), ft_int_vector.size());
	while (ft_const_rit != ft_const_rite)
	{
		CHECK_EQUAL(*std_const_rit, *ft_const_rit);
		CHECK_EQUAL(*std_const_rit_copy, *ft_const_rit_copy);
		CHECK_EQUAL((std_const_rit == std_const_rite), (ft_const_rit == ft_const_rite));
		std_const_rit++;
		ft_const_rit++;
	}
}

TEST(VectorReverseIterators, EqualOperator)
{
	std_int_vector_rit = std_int_vector_rite - 1;
	ft_int_vector_rit = ft_int_vector_rite - 1;
	std_string_vector_rit = std_string_vector_rite - 1;
	ft_string_vector_rit = ft_string_vector_rite - 1;

}

TEST_GROUP(VectorCapacity)
{
	std::list<std::string>		string_list;
	std::vector<int>			std_int_vector;
	ft::vector<int>				ft_int_vector;
	std::vector<std::string>	std_string_vector;
	ft::vector<std::string>		ft_string_vector;

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

TEST(VectorCapacity, Size)
{
	CHECK_EQUAL(std_int_vector.size(), ft_int_vector.size());
	CHECK_EQUAL(std_string_vector.size(), ft_string_vector.size());
}

TEST(VectorCapacity, MaxSize)
{
	CHECK_EQUAL(std_int_vector.max_size(), ft_int_vector.max_size());
	CHECK_EQUAL(std_string_vector.max_size(), ft_string_vector.max_size());
}

TEST(VectorCapacity, Resize)
{
	compareContent(std_int_vector, ft_int_vector);
	compareContent(std_string_vector, ft_string_vector);
	std_int_vector.resize(4);
	ft_int_vector.resize(4);
	std_string_vector.resize(4);
	ft_string_vector.resize(4);
	compareContent(std_int_vector, ft_int_vector);
	compareContent(std_string_vector, ft_string_vector);
	std_int_vector.resize(4);
	ft_int_vector.resize(4);
	std_string_vector.resize(4);
	ft_string_vector.resize(4);
	compareContent(std_int_vector, ft_int_vector);
	compareContent(std_string_vector, ft_string_vector);
	std_int_vector.resize(8, 1234);
	ft_int_vector.resize(8, 1234);
	std_string_vector.resize(8, "super cool");
	ft_string_vector.resize(8, "super cool");
	compareContent(std_int_vector, ft_int_vector);
	compareContent(std_string_vector, ft_string_vector);
	std_int_vector.resize(4, 32);
	ft_int_vector.resize(4, 32);
	std_string_vector.resize(4, "43");
	ft_string_vector.resize(4, "43");
	compareContent(std_int_vector, ft_int_vector);
	compareContent(std_string_vector, ft_string_vector);
	std_int_vector.resize(12);
	ft_int_vector.resize(12);
	std_string_vector.resize(12);
	ft_string_vector.resize(12);
	compareContent(std_int_vector, ft_int_vector);
	compareContent(std_string_vector, ft_string_vector);
}

TEST(VectorCapacity, Empty)
{
	CHECK_EQUAL(std_int_vector.empty(), ft_int_vector.empty());
	CHECK_EQUAL(std_string_vector.empty(), ft_string_vector.empty());

	std_int_vector.resize(0);
	ft_int_vector.resize(0);
	std_string_vector.resize(0);
	ft_string_vector.resize(0);

	CHECK_EQUAL(std_int_vector.empty(), ft_int_vector.empty());
	CHECK_EQUAL(std_string_vector.empty(), ft_string_vector.empty());
}

TEST(VectorCapacity, Reserve)
{
	compareContent(std_int_vector, ft_int_vector);
	compareContent(std_string_vector, ft_string_vector);
	std_int_vector.reserve(0);
	ft_int_vector.reserve(0);
	std_string_vector.reserve(0);
	ft_string_vector.reserve(0);
	compareContent(std_int_vector, ft_int_vector);
	compareContent(std_string_vector, ft_string_vector);
	std_int_vector.reserve(1234);
	ft_int_vector.reserve(1234);
	std_string_vector.reserve(1234);
	ft_string_vector.reserve(1234);
	compareContent(std_int_vector, ft_int_vector);
	compareContent(std_string_vector, ft_string_vector);
	std_int_vector.reserve(2);
	ft_int_vector.reserve(2);
	std_string_vector.reserve(2);
	ft_string_vector.reserve(2);
	compareContent(std_int_vector, ft_int_vector);
	compareContent(std_string_vector, ft_string_vector);
}

TEST(VectorCapacity, GetAllocator)
{
	CHECK_TRUE(typeid(std_int_vector.get_allocator())
			== typeid(ft_int_vector.get_allocator()));
	CHECK_TRUE(typeid(std_string_vector.get_allocator())
			== typeid(ft_string_vector.get_allocator()));
}

TEST_GROUP(VectorAccess)
{
	std::list<std::string>		string_list;
	std::vector<int>			std_int_vector;
	ft::vector<int>				ft_int_vector;
	std::vector<std::string>	std_string_vector;
	ft::vector<std::string>		ft_string_vector;

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

TEST(VectorAccess, SquareBracket)
{
	CHECK_EQUAL(std_int_vector[0], ft_int_vector[0]);
	CHECK_EQUAL(std_string_vector[0], ft_string_vector[0]);
	std_int_vector[0] = 1234;
	ft_int_vector[0] = 1234;
	std_string_vector[0] = "1234";
	ft_string_vector[0] = "1234";
	CHECK_EQUAL(std_int_vector[0], ft_int_vector[0]);
	CHECK_EQUAL(std_string_vector[0], ft_string_vector[0]);
}

TEST(VectorAccess, At)
{
	CHECK_EQUAL(std_int_vector.at(0), ft_int_vector.at(0));
	CHECK_EQUAL(std_string_vector.at(0), ft_string_vector.at(0));
	std_int_vector.at(0) = 1234;
	ft_int_vector.at(0) = 1234;
	std_string_vector.at(0) = "1234";
	ft_string_vector.at(0) = "1234";
	CHECK_EQUAL(std_int_vector.at(0), ft_int_vector.at(0));
	CHECK_EQUAL(std_string_vector.at(0), ft_string_vector.at(0));
	try
	{
		ft_int_vector.at(9872) = 12;
	}
	catch( std::out_of_range &e )
	{
		CHECK(true);
	}
	catch( std::exception &e )
	{
		FAIL("Wrong exception handling for out_of_range at()");
	}
}

TEST(VectorAccess, Front)
{
	CHECK_EQUAL(std_int_vector.front(), ft_int_vector.front());
	CHECK_EQUAL(std_string_vector.front(), ft_string_vector.front());
	std_int_vector.front() = 1234;
	ft_int_vector.front() = 1234;
	std_string_vector.front() = "1234";
	ft_string_vector.front() = "1234";
	CHECK_EQUAL(std_int_vector.front(), ft_int_vector.front());
	CHECK_EQUAL(std_string_vector.front(), ft_string_vector.front());
}

TEST(VectorAccess, Back)
{
	CHECK_EQUAL(std_int_vector.back(), ft_int_vector.back());
	CHECK_EQUAL(std_string_vector.back(), ft_string_vector.back());
	std_int_vector.back() = 1234;
	ft_int_vector.back() = 1234;
	std_string_vector.back() = "1234";
	ft_string_vector.back() = "1234";
	CHECK_EQUAL(std_int_vector.back(), ft_int_vector.back());
	CHECK_EQUAL(std_string_vector.back(), ft_string_vector.back());
}

TEST_GROUP(VectorModifiers)
{
	std::list<std::string>		string_list;
	std::vector<int>			std_int_vector;
	ft::vector<int>				ft_int_vector;
	std::vector<std::string>	std_string_vector;
	ft::vector<std::string>		ft_string_vector;

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

TEST(VectorModifiers, Assign)
{
	std::list<int>	int_list;

	compareContent(std_int_vector, ft_int_vector);
	compareContent(std_string_vector, ft_string_vector);
	std_int_vector.assign(4, 42);
	ft_int_vector.assign(4, 42);
	std_string_vector.assign(4, "42");
	ft_string_vector.assign(4, "42");
	compareContent(std_int_vector, ft_int_vector);
	compareContent(std_string_vector, ft_string_vector);
	for (int i = 0; i < 12; i++)
		int_list.push_back(i * i);
	std_int_vector.assign(int_list.begin(), int_list.end());
	ft_int_vector.assign(int_list.begin(), int_list.end());
	std_string_vector.assign(string_list.begin(), string_list.end());
	ft_string_vector.assign(string_list.begin(), string_list.end());
	compareContent(std_int_vector, ft_int_vector);
	compareContent(std_string_vector, ft_string_vector);
}

TEST(VectorModifiers, PushBack)
{
	compareContent(std_int_vector, ft_int_vector);
	compareContent(std_string_vector, ft_string_vector);
	std_int_vector.push_back(42);
	ft_int_vector.push_back(42);
	std_string_vector.push_back("42");
	ft_string_vector.push_back("42");
	compareContent(std_int_vector, ft_int_vector);
	compareContent(std_string_vector, ft_string_vector);
}

TEST(VectorModifiers, PopBack)
{
	compareContent(std_int_vector, ft_int_vector);
	compareContent(std_string_vector, ft_string_vector);
	std_int_vector.pop_back();
	ft_int_vector.pop_back();
	std_string_vector.pop_back();
	ft_string_vector.pop_back();
	compareContent(std_int_vector, ft_int_vector);
	compareContent(std_string_vector, ft_string_vector);
}

TEST(VectorModifiers, Insert)
{
	std::list<int>	int_list;
	std_int_it		std_int_iterator;
	ft_int_it		ft_int_iterator;
	std_string_it	std_string_iterator;
	ft_string_it	ft_string_iterator;

	for (int i = 0; i < 12; i++)
		int_list.push_back(i * i);
	compareContent(std_int_vector, ft_int_vector);
	compareContent(std_string_vector, ft_string_vector);
	std_int_iterator = std_int_vector.insert(std_int_vector.begin(), 4);
	ft_int_iterator = ft_int_vector.insert(ft_int_vector.begin(), 4);
	std_string_iterator = std_string_vector.insert(std_string_vector.begin(), "YUCK");
	ft_string_iterator = ft_string_vector.insert(ft_string_vector.begin(), "YUCK");
	CHECK_EQUAL(*std_int_iterator, *ft_int_iterator);
	CHECK_EQUAL(*std_string_iterator, *ft_string_iterator);
	CHECK_EQUAL(std_int_iterator - std_int_vector.begin(), ft_int_iterator - ft_int_vector.begin());
	CHECK_EQUAL(std_string_iterator - std_string_vector.begin(), ft_string_iterator - ft_string_vector.begin());
	compareContent(std_int_vector, ft_int_vector);
	compareContent(std_string_vector, ft_string_vector);
	std_int_vector.insert(std_int_vector.begin() + 3, 4, 3);
	ft_int_vector.insert(ft_int_vector.begin() + 3, 4, 3);
	std_string_vector.insert(std_string_vector.begin() + 3, 2, "HI");
	ft_string_vector.insert(ft_string_vector.begin() + 3, 2, "HI");
	compareContent(std_int_vector, ft_int_vector);
	compareContent(std_string_vector, ft_string_vector);
	std_int_vector.insert(std_int_vector.begin() + 2, int_list.begin(), int_list.end());
	ft_int_vector.insert(ft_int_vector.begin() + 2, int_list.begin(), int_list.end());
	std_string_vector.insert(std_string_vector.begin() + 2, string_list.begin(), string_list.end());
	ft_string_vector.insert(ft_string_vector.begin() + 2, string_list.begin(), string_list.end());
	compareContent(std_int_vector, ft_int_vector);
	compareContent(std_string_vector, ft_string_vector);
}

TEST(VectorModifiers, Erase)
{
	std_int_it		std_int_iterator;
	ft_int_it		ft_int_iterator;
	std_string_it	std_string_iterator;
	ft_string_it	ft_string_iterator;

	compareContent(std_int_vector, ft_int_vector);
	compareContent(std_string_vector, ft_string_vector);
	std_int_iterator = std_int_vector.erase(std_int_vector.begin() + 3);
	ft_int_iterator = ft_int_vector.erase(ft_int_vector.begin() + 3);
	std_string_iterator = std_string_vector.erase(std_string_vector.begin() + 3);
	ft_string_iterator = ft_string_vector.erase(ft_string_vector.begin() + 3);
	CHECK_EQUAL(*std_int_iterator, *ft_int_iterator);
	CHECK_EQUAL(*std_string_iterator, *ft_string_iterator);
	CHECK_EQUAL(std_int_iterator - std_int_vector.begin(), ft_int_iterator - ft_int_vector.begin());
	CHECK_EQUAL(std_string_iterator - std_string_vector.begin(), ft_string_iterator - ft_string_vector.begin());
	compareContent(std_int_vector, ft_int_vector);
	compareContent(std_string_vector, ft_string_vector);
	std_int_vector.erase(std_int_vector.begin());
	ft_int_vector.erase(ft_int_vector.begin());
	std_string_vector.erase(std_string_vector.begin());
	ft_string_vector.erase(ft_string_vector.begin());
	compareContent(std_int_vector, ft_int_vector);
	compareContent(std_string_vector, ft_string_vector);
	std_int_vector.erase(std_int_vector.end() - 1);
	ft_int_vector.erase(ft_int_vector.end() - 1);
	std_string_vector.erase(std_string_vector.end() - 1);
	ft_string_vector.erase(ft_string_vector.end() - 1);
	compareContent(std_int_vector, ft_int_vector);
	compareContent(std_string_vector, ft_string_vector);
	std_int_iterator = std_int_vector.erase(std_int_vector.begin() + 2, std_int_vector.begin() + 8);
	ft_int_iterator = ft_int_vector.erase(ft_int_vector.begin() + 2, ft_int_vector.begin() + 8);
	std_string_iterator = std_string_vector.erase(std_string_vector.begin() + 1, std_string_vector.begin() + 3);
	ft_string_iterator = ft_string_vector.erase(ft_string_vector.begin() + 1, ft_string_vector.begin() + 3);
	CHECK_EQUAL(std_int_iterator - std_int_vector.begin(), ft_int_iterator - ft_int_vector.begin());
	CHECK_EQUAL(std_string_iterator - std_string_vector.begin(), ft_string_iterator - ft_string_vector.begin());
	compareContent(std_int_vector, ft_int_vector);
	compareContent(std_string_vector, ft_string_vector);
}

TEST(VectorModifiers, Clear)
{
	compareContent(std_int_vector, ft_int_vector);
	compareContent(std_string_vector, ft_string_vector);
	std_int_vector.clear();
	ft_int_vector.clear();
	std_string_vector.clear();
	ft_string_vector.clear();
	compareContent(std_int_vector, ft_int_vector);
	compareContent(std_string_vector, ft_string_vector);
}

TEST(VectorModifiers, Swap)
{
	std::vector<int>			other_std_int_v;
	ft::vector<int>				other_ft_int_v;
	std::vector<std::string>	other_std_string_v;
	ft::vector<std::string>		other_ft_string_v;

	std_int_it					std_int_iterator;
	ft_int_it					ft_int_iterator;
	std_string_it				std_string_iterator;
	ft_string_it				ft_string_iterator;

	for (int i = 0; i < 5; i++)
	{
		other_std_int_v.push_back(i * 9);
		other_ft_int_v.push_back(i * 9);
	}
	other_std_string_v.push_back("qwer");
	other_std_string_v.push_back("asdf");
	other_std_string_v.push_back(";lkj");
	other_std_string_v.push_back("zxcv");
	other_std_string_v.push_back("poiu");
	other_std_string_v.push_back("vbnm");
	other_ft_string_v.push_back("qwer");
	other_ft_string_v.push_back("asdf");
	other_ft_string_v.push_back(";lkj");
	other_ft_string_v.push_back("zxcv");
	other_ft_string_v.push_back("poiu");
	other_ft_string_v.push_back("vbnm");

	compareContent(std_int_vector, ft_int_vector);
	compareContent(std_string_vector, ft_string_vector);
	compareContent(other_std_int_v, other_ft_int_v);
	compareContent(other_std_string_v, other_ft_string_v);
	ft_int_iterator = ft_int_vector.begin();
	ft_string_iterator = ft_string_vector.begin();

	std_int_vector.swap(other_std_int_v);
	ft_int_vector.swap(other_ft_int_v);
	std_string_vector.swap(other_std_string_v);
	ft_string_vector.swap(other_ft_string_v);

	compareContent(std_int_vector, ft_int_vector);
	compareContent(std_string_vector, ft_string_vector);
	compareContent(other_std_int_v, other_ft_int_v);
	compareContent(other_std_string_v, other_ft_string_v);
	POINTERS_EQUAL(&(*ft_int_iterator), &(*other_ft_int_v.begin()));
	POINTERS_EQUAL(&(*ft_string_iterator), &(*other_ft_string_v.begin()));
}
