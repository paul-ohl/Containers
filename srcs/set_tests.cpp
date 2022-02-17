/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_tests.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pohl <pohl@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 08:59:01 by pohl              #+#    #+#             */
/*   Updated: 2022/02/17 10:39:55 by pohl             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <typeinfo>
#include <list>
#include <set>
#include "set.hpp"
#include "CppUTest/TestHarness.h"
#include "CppUTest/UtestMacros.h"

template< typename StdIt, typename FtIt >
void	compareIterators( StdIt stdIt, FtIt ftIt, bool print = false )
{
		if (print)
			std::cout << *stdIt << " | " << *ftIt << std::endl;
		else
		{
			CHECK_EQUAL(*stdIt, *ftIt);
		}
}

template< typename StdSet, typename FtSet >
void	compareContent( StdSet& stdSet, FtSet& ftSet, bool print = false )
{
	typename StdSet::iterator	std_begin, std_end;
	typename FtSet::iterator	ft_begin, ft_end;

	std_begin = stdSet.begin();
	std_end = stdSet.end();
	ft_begin = ftSet.begin();
	ft_end = ftSet.end();
	if (print)
		std::cout << "std | ft" << std::endl;
	else
	{
		CHECK_EQUAL_TEXT(stdSet.size(), ftSet.size(), "Size");
		CHECK_EQUAL_TEXT(stdSet.max_size() , ftSet.max_size(), "Max Size");
	}
	while (std_begin != std_end)
		compareIterators(std_begin++, ft_begin++, print);
}

TEST_GROUP(SetMemberFunctions)
{
	std::list<char>			list_char;
	std::list<std::string>	list_string;

	void setup()
	{
		list_char.push_back('a');
		list_char.push_back('b');
		list_char.push_back('c');
		list_char.push_back('d');
		list_char.push_back('e');
		list_char.push_back('f');
		list_char.push_back('g');
		list_char.push_back('h');
		list_char.push_back('i');
		list_string.push_back("Bonjour");
		list_string.push_back("Hello");
		list_string.push_back("Guten Tag");
		list_string.push_back("Hola");
		list_string.push_back("Buongiorno???");
		list_string.push_back("Fuck");
		list_string.push_back("I'm not great");
		list_string.push_back("with languages");
		list_string.push_back("after all");
	}
};

TEST(SetMemberFunctions, EmptyConstructor)
{
	std::set<char>			std_char_set;
	ft::set<char>			ft_char_set;
	std::set<std::string>	std_string_set;
	ft::set<std::string>	ft_string_set;
}

TEST(SetMemberFunctions, InputIteratorConstructor)
{
	std::set<char>			std_char_set(list_char.begin(), list_char.end());
	ft::set<char>			ft_char_set(list_char.begin(), list_char.end());
	std::set<std::string>	std_string_set(list_string.begin(), list_string.end());
	ft::set<std::string>	ft_string_set(list_string.begin(), list_string.end());

	compareContent(std_char_set, ft_char_set);
	compareContent(std_string_set, ft_string_set);
}

TEST(SetMemberFunctions, CopyConstructor)
{
	std::set<char>			std_char_set(list_char.begin(), list_char.end());
	ft::set<char>			ft_char_set(list_char.begin(), list_char.end());
	std::set<std::string>	std_string_set(list_string.begin(), list_string.end());
	ft::set<std::string>	ft_string_set(list_string.begin(), list_string.end());

	std::set<char>			std_char_set_copy(std_char_set);
	ft::set<char>			ft_char_set_copy(ft_char_set);
	std::set<std::string>	std_string_set_copy(std_string_set);
	ft::set<std::string>	ft_string_set_copy(ft_string_set);

	std_char_set.insert('x');
	ft_char_set.insert('x');

	compareContent(std_char_set, ft_char_set);
	compareContent(std_string_set, ft_string_set);
	compareContent(std_char_set_copy, ft_char_set_copy);
	compareContent(std_string_set_copy, ft_string_set_copy);
}

TEST(SetMemberFunctions, EqualOperator)
{
	std::set<char>			std_char_set(list_char.begin(), list_char.end());
	ft::set<char>			ft_char_set(list_char.begin(), list_char.end());
	std::set<std::string>	std_string_set(list_string.begin(), list_string.end());
	ft::set<std::string>	ft_string_set(list_string.begin(), list_string.end());

	std::set<char>			std_char_set_copy;
	ft::set<char>			ft_char_set_copy;
	std::set<std::string>	std_string_set_copy;
	ft::set<std::string>	ft_string_set_copy;

	std_char_set_copy = std_char_set;
	ft_char_set_copy = ft_char_set;
	ft_string_set_copy = ft_string_set;
	std_string_set_copy = std_string_set;

	std_char_set.insert('x');
	ft_char_set.insert('x');

	compareContent(std_char_set, ft_char_set);
	compareContent(std_string_set, ft_string_set);
	compareContent(std_char_set_copy, ft_char_set_copy);
	compareContent(std_string_set_copy, ft_string_set_copy);
}

TEST_GROUP(SetIterators)
{
	std::list<char>			list_char;
	std::list<std::string>	list_string;

	std::set<char>			std_char_set;
	ft::set<char>			ft_char_set;
	std::set<std::string>	std_string_set;
	ft::set<std::string>	ft_string_set;

	std::set<char>::iterator			std_char_set_it, std_char_set_ite;
	ft::set<char>::iterator				ft_char_set_it, ft_char_set_ite;
	std::set<std::string>::iterator		std_string_set_it, std_string_set_ite;
	ft::set<std::string>::iterator		ft_string_set_it, ft_string_set_ite;

	void setup()
	{
		list_char.push_back('a');
		list_char.push_back('b');
		list_char.push_back('c');
		list_char.push_back('d');
		list_char.push_back('e');
		list_char.push_back('f');
		list_char.push_back('g');
		list_char.push_back('h');
		list_char.push_back('i');
		list_string.push_back("Bonjour");
		list_string.push_back("Hello");
		list_string.push_back("Guten Tag");
		list_string.push_back("Hola");
		list_string.push_back("Buongiorno???");
		list_string.push_back("Fuck");
		list_string.push_back("I'm not great");
		list_string.push_back("with languages");
		list_string.push_back("after all");
		list_char.push_back('a');
		list_char.push_back('b');
		list_char.push_back('c');
		list_char.push_back('d');
		list_char.push_back('e');
		list_char.push_back('f');
		list_char.push_back('g');
		list_char.push_back('h');
		list_char.push_back('i');
		list_string.push_back("Bonjour");
		list_string.push_back("Hello");
		list_string.push_back("Guten Tag");
		list_string.push_back("Hola");
		list_string.push_back("Buongiorno???");
		list_string.push_back("Fuck");
		list_string.push_back("I'm not great");
		list_string.push_back("with languages");
		list_string.push_back("after all");
		std_char_set.insert(list_char.begin(), list_char.end());
		ft_char_set.insert(list_char.begin(), list_char.end());
		std_string_set.insert(list_string.begin(), list_string.end());
		ft_string_set.insert(list_string.begin(), list_string.end());
	}
};

TEST(SetIterators, Arithmetics)
{
	std_char_set_it = std_char_set.begin();
	std_char_set_ite = std_char_set.end();
	ft_char_set_it = ft_char_set.begin();
	ft_char_set_ite = ft_char_set.end();
	std_string_set_it = std_string_set.begin();
	std_string_set_ite = std_string_set.end();
	ft_string_set_it = ft_string_set.begin();
	ft_string_set_ite = ft_string_set.end();

	compareIterators(std_char_set_it, ft_char_set_it);
	compareIterators(std_string_set_it, ft_string_set_it);

	std_char_set_it++;
	ft_char_set_it++;
	std_string_set_it++;
	ft_string_set_it++;

	compareIterators(std_char_set_it, ft_char_set_it);
	compareIterators(std_string_set_it, ft_string_set_it);

	std_char_set_it--;
	ft_char_set_it--;
	std_string_set_it--;
	ft_string_set_it--;

	compareIterators(std_char_set_it, ft_char_set_it);
	compareIterators(std_string_set_it, ft_string_set_it);

	compareIterators(std_char_set_it++, ft_char_set_it++);
	compareIterators(std_string_set_it++, ft_string_set_it++);
	compareIterators(++std_char_set_it, ++ft_char_set_it);
	compareIterators(++std_string_set_it, ++ft_string_set_it);
	compareIterators(std_char_set_it--, ft_char_set_it--);
	compareIterators(std_string_set_it--, ft_string_set_it--);
	compareIterators(--std_char_set_it, --ft_char_set_it);
	compareIterators(--std_string_set_it, --ft_string_set_it);

	CHECK_EQUAL((std_char_set_it == std_char_set_ite), (ft_char_set_it == ft_char_set_ite));
	CHECK_EQUAL((std_string_set_it == std_string_set_ite), (ft_string_set_it == ft_string_set_ite));
	CHECK_EQUAL((std_char_set_it != std_char_set_ite), (ft_char_set_it != ft_char_set_ite));
	CHECK_EQUAL((std_string_set_it != std_string_set_ite), (ft_string_set_it != ft_string_set_ite));
	/* std::cout << "SetIterators.Arithmetics END" << std::endl; */
}

TEST_GROUP(SetReverseIterators)
{
	std::list<char>			list_char;
	std::list<std::string>	list_string;

	std::set<char>			std_char_set;
	ft::set<char>			ft_char_set;
	std::set<std::string>	std_string_set;
	ft::set<std::string>	ft_string_set;

	std::set<char>::reverse_iterator			std_char_set_it, std_char_set_ite;
	ft::set<char>::reverse_iterator			ft_char_set_it, ft_char_set_ite;
	std::set<std::string>::reverse_iterator	std_string_set_it, std_string_set_ite;
	ft::set<std::string>::reverse_iterator		ft_string_set_it, ft_string_set_ite;

	void setup()
	{
		list_char.push_back('a');
		list_char.push_back('b');
		list_char.push_back('c');
		list_char.push_back('d');
		list_char.push_back('e');
		list_char.push_back('f');
		list_char.push_back('g');
		list_char.push_back('h');
		list_char.push_back('i');
		list_string.push_back("Bonjour");
		list_string.push_back("Hello");
		list_string.push_back("Guten Tag");
		list_string.push_back("Hola");
		list_string.push_back("Buongiorno???");
		list_string.push_back("Fuck");
		list_string.push_back("I'm not great");
		list_string.push_back("with languages");
		list_string.push_back("after all");
		list_char.push_back('a');
		list_char.push_back('b');
		list_char.push_back('c');
		list_char.push_back('d');
		list_char.push_back('e');
		list_char.push_back('f');
		list_char.push_back('g');
		list_char.push_back('h');
		list_char.push_back('i');
		list_string.push_back("Bonjour");
		list_string.push_back("Hello");
		list_string.push_back("Guten Tag");
		list_string.push_back("Hola");
		list_string.push_back("Buongiorno???");
		list_string.push_back("Fuck");
		list_string.push_back("I'm not great");
		list_string.push_back("with languages");
		list_string.push_back("after all");
		std_char_set.insert(list_char.begin(), list_char.end());
		ft_char_set.insert(list_char.begin(), list_char.end());
		std_string_set.insert(list_string.begin(), list_string.end());
		ft_string_set.insert(list_string.begin(), list_string.end());
	}
};

TEST(SetReverseIterators, Arithmetics)
{
	std_char_set_it = std_char_set.rbegin();
	std_char_set_ite = std_char_set.rend();
	ft_char_set_it = ft_char_set.rbegin();
	ft_char_set_ite = ft_char_set.rend();
	std_string_set_it = std_string_set.rbegin();
	std_string_set_ite = std_string_set.rend();
	ft_string_set_it = ft_string_set.rbegin();
	ft_string_set_ite = ft_string_set.rend();

	compareIterators(std_char_set_it, ft_char_set_it);
	compareIterators(std_string_set_it, ft_string_set_it);

	std_char_set_it++;
	ft_char_set_it++;
	std_string_set_it++;
	ft_string_set_it++;

	compareIterators(std_char_set_it, ft_char_set_it);
	compareIterators(std_string_set_it, ft_string_set_it);

	std_char_set_it--;
	ft_char_set_it--;
	std_string_set_it--;
	ft_string_set_it--;

	compareIterators(std_char_set_it, ft_char_set_it);
	compareIterators(std_string_set_it, ft_string_set_it);

	compareIterators(std_char_set_it++, ft_char_set_it++);
	compareIterators(std_string_set_it++, ft_string_set_it++);
	compareIterators(++std_char_set_it, ++ft_char_set_it);
	compareIterators(++std_string_set_it, ++ft_string_set_it);
	compareIterators(std_char_set_it--, ft_char_set_it--);
	compareIterators(std_string_set_it--, ft_string_set_it--);
	compareIterators(--std_char_set_it, --ft_char_set_it);
	compareIterators(--std_string_set_it, --ft_string_set_it);

	CHECK_EQUAL((std_char_set_it == std_char_set_ite), (ft_char_set_it == ft_char_set_ite));
	CHECK_EQUAL((std_string_set_it == std_string_set_ite), (ft_string_set_it == ft_string_set_ite));
	CHECK_EQUAL((std_char_set_it != std_char_set_ite), (ft_char_set_it != ft_char_set_ite));
	CHECK_EQUAL((std_string_set_it != std_string_set_ite), (ft_string_set_it != ft_string_set_ite));
}

TEST(SetReverseIterators, Base)
{
	std_char_set_it = std_char_set.rbegin();
	std_char_set_ite = std_char_set.rend();
	ft_char_set_it = ft_char_set.rbegin();
	ft_char_set_ite = ft_char_set.rend();
	std_string_set_it = std_string_set.rbegin();
	std_string_set_ite = std_string_set.rend();
	ft_string_set_it = ft_string_set.rbegin();
	ft_string_set_ite = ft_string_set.rend();

	std_char_set_it++;
	ft_char_set_it++;
	std_string_set_it++;
	ft_string_set_it++;

	compareIterators(std_char_set_it.base(), ft_char_set_it.base());
	compareIterators(std_string_set_it.base(), ft_string_set_it.base());

	compareIterators(std_char_set_ite.base(), ft_char_set_ite.base());
	compareIterators(std_string_set_ite.base(), ft_string_set_ite.base());
}

TEST_GROUP(SetCapacity)
{
	std::list<char>			list_char;
	std::list<std::string>	list_string;

	std::set<char>			std_char_set;
	ft::set<char>			ft_char_set;
	std::set<std::string>	std_string_set;
	ft::set<std::string>	ft_string_set;

	void setup()
	{
		list_char.push_back('a');
		list_char.push_back('b');
		list_char.push_back('c');
		list_char.push_back('d');
		list_char.push_back('e');
		list_char.push_back('f');
		list_char.push_back('g');
		list_char.push_back('h');
		list_char.push_back('i');
		list_string.push_back("Bonjour");
		list_string.push_back("Hello");
		list_string.push_back("Guten Tag");
		list_string.push_back("Hola");
		list_string.push_back("Buongiorno???");
		list_string.push_back("Fuck");
		list_string.push_back("I'm not great");
		list_string.push_back("with languages");
		list_string.push_back("after all");
		list_char.push_back('a');
		list_char.push_back('b');
		list_char.push_back('c');
		list_char.push_back('d');
		list_char.push_back('e');
		list_char.push_back('f');
		list_char.push_back('g');
		list_char.push_back('h');
		list_char.push_back('i');
		list_string.push_back("Bonjour");
		list_string.push_back("Hello");
		list_string.push_back("Guten Tag");
		list_string.push_back("Hola");
		list_string.push_back("Buongiorno???");
		list_string.push_back("Fuck");
		list_string.push_back("I'm not great");
		list_string.push_back("with languages");
		list_string.push_back("after all");
		std_char_set.insert(list_char.begin(), list_char.end());
		ft_char_set.insert(list_char.begin(), list_char.end());
		std_string_set.insert(list_string.begin(), list_string.end());
		ft_string_set.insert(list_string.begin(), list_string.end());
	}
};

TEST(SetCapacity, Empty)
{
	/* std::cout << "SetCapacity.Empty" << std::endl; */
	CHECK_EQUAL(std_char_set.empty(), ft_char_set.empty());
	CHECK_EQUAL(std_string_set.empty(), ft_string_set.empty());

	std_char_set.clear();
	ft_char_set.clear();
	std_string_set.clear();
	ft_string_set.clear();

	CHECK_EQUAL(std_char_set.size(), ft_char_set.size());
	CHECK_EQUAL(std_string_set.size(), ft_string_set.size());
	CHECK_EQUAL(std_char_set.empty(), ft_char_set.empty());
	CHECK_EQUAL(std_string_set.empty(), ft_string_set.empty());

	std_char_set.insert('a');
	ft_char_set.insert('a');
	std_string_set.insert("a");
	ft_string_set.insert("a");

	CHECK_EQUAL(std_char_set.empty(), ft_char_set.empty());
	CHECK_EQUAL(std_string_set.empty(), ft_string_set.empty());
	/* std::cout << "SetCapacity.Empty END" << std::endl; */
}

TEST_GROUP(SetModifiers)
{
	std::list<char>			list_char;
	std::list<std::string>	list_string;

	std::set<char>			std_char_set;
	ft::set<char>			ft_char_set;
	std::set<std::string>	std_string_set;
	ft::set<std::string>	ft_string_set;

	void setup()
	{
		list_char.push_back('a');
		list_char.push_back('b');
		list_char.push_back('c');
		list_char.push_back('d');
		list_char.push_back('e');
		list_char.push_back('f');
		list_char.push_back('g');
		list_char.push_back('h');
		list_char.push_back('i');
		list_string.push_back("Bonjour");
		list_string.push_back("Hello");
		list_string.push_back("Guten Tag");
		list_string.push_back("Hola");
		list_string.push_back("Buongiorno???");
		list_string.push_back("Fuck");
		list_string.push_back("I'm not great");
		list_string.push_back("with languages");
		list_string.push_back("after all");
		list_char.push_back('a');
		list_char.push_back('b');
		list_char.push_back('c');
		list_char.push_back('d');
		list_char.push_back('e');
		list_char.push_back('f');
		list_char.push_back('g');
		list_char.push_back('h');
		list_char.push_back('i');
		list_string.push_back("Bonjour");
		list_string.push_back("Hello");
		list_string.push_back("Guten Tag");
		list_string.push_back("Hola");
		list_string.push_back("Buongiorno???");
		list_string.push_back("Fuck");
		list_string.push_back("I'm not great");
		list_string.push_back("with languages");
		list_string.push_back("after all");
		std_char_set.insert(list_char.begin(), list_char.end());
		ft_char_set.insert(list_char.begin(), list_char.end());
		std_string_set.insert(list_string.begin(), list_string.end());
		ft_string_set.insert(list_string.begin(), list_string.end());
	}
};

template< typename StdIt, typename FtIt >
void	compareInsertionReturn( std::pair<StdIt, bool> std_res,  std::pair<FtIt, bool> ft_res )
{
	CHECK_EQUAL(std_res.second, ft_res.second);
	compareIterators(std_res.first, ft_res.first, false);
}

TEST(SetModifiers, SetBasicInsertion)
{
	std::pair<std::set<char>::iterator, bool>			std_char_result;
	std::pair<ft::set<char>::iterator, bool>			ft_char_result;
	std::pair<std::set<std::string>::iterator, bool>	std_string_result;
	std::pair<ft::set<std::string>::iterator, bool>		ft_string_result;

	compareContent(std_char_set, ft_char_set);
	compareContent(std_string_set, ft_string_set);

	std_char_result = std_char_set.insert('x');
	ft_char_result = ft_char_set.insert('x');
	std_string_result = std_string_set.insert("x");
	ft_string_result = ft_string_set.insert("x");

	compareInsertionReturn(std_char_result, ft_char_result);
	compareInsertionReturn(std_string_result, ft_string_result);

	std_char_result = std_char_set.insert('x');
	ft_char_result = ft_char_set.insert('x');
	std_string_result = std_string_set.insert("x");
	ft_string_result = ft_string_set.insert("x");

	compareInsertionReturn(std_char_result, ft_char_result);
	compareInsertionReturn(std_string_result, ft_string_result);

	std_char_result = std_char_set.insert('x');
	ft_char_result = ft_char_set.insert('x');
	std_string_result = std_string_set.insert("x");
	ft_string_result = ft_string_set.insert("x");

	compareInsertionReturn(std_char_result, ft_char_result);
	compareInsertionReturn(std_string_result, ft_string_result);

	compareContent(std_char_set, ft_char_set);
	compareContent(std_string_set, ft_string_set);
}

TEST(SetModifiers, SetIteratorInsertion)
{
	list_char.push_back('a');
	list_char.push_back('x');
	list_char.push_back('a');
	list_char.push_back('x');
	list_string.push_back("asdf");
	list_string.push_back("xcvv");
	list_string.push_back("asdf");
	list_string.push_back("xcvv");

	std_char_set.insert(++(++list_char.begin()), list_char.end());
	ft_char_set.insert(++(++list_char.begin()), list_char.end());
	std_string_set.insert(++(++list_string.begin()), list_string.end());
	ft_string_set.insert(++(++list_string.begin()), list_string.end());

	compareContent(std_char_set, ft_char_set);
	compareContent(std_string_set, ft_string_set);
}

TEST(SetModifiers, SetHintInsertion)
{
	std::set<char>::iterator			std_char_it = --std_char_set.end();
	ft::set<char>::iterator			ft_char_it = --ft_char_set.end();
	std::set<std::string>::iterator	std_string_it = --std_string_set.end();
	ft::set<std::string>::iterator		ft_string_it = --ft_string_set.end();

	std_char_set.insert(std_char_it, 'j');  // max efficiency inserting
	ft_char_set.insert(ft_char_it, 'j');  // max efficiency inserting
	std_string_set.insert(std_string_it, "j");  // max efficiency inserting
	ft_string_set.insert(ft_string_it, "j");  // max efficiency inserting

	std_char_set.insert(std_char_it, 'o');  // max efficiency inserting
	ft_char_set.insert(ft_char_it, 'o');  // max efficiency inserting
	std_string_set.insert(std_string_it, "o");  // max efficiency inserting
	ft_string_set.insert(ft_string_it, "o");  // max efficiency inserting

	compareContent(std_char_set, ft_char_set);
	compareContent(std_string_set, ft_string_set);
}

TEST(SetModifiers, SetErase)
{
	std_char_set.erase(--std_char_set.end());
	ft_char_set.erase(--ft_char_set.end());
	std_string_set.erase(--std_string_set.end());
	ft_string_set.erase(--ft_string_set.end());

	std_char_set.erase(std_char_set.begin());
	ft_char_set.erase(ft_char_set.begin());
	std_string_set.erase(std_string_set.begin());
	ft_string_set.erase(ft_string_set.begin());

	std_char_set.erase('c');
	ft_char_set.erase('c');
	std_string_set.erase("Hello");
	ft_string_set.erase("Hello");

	std_char_set.erase(++std_char_set.begin(), ++(++(++std_char_set.begin())));
	ft_char_set.erase(++ft_char_set.begin(), ++(++(++ft_char_set.begin())));
	std_string_set.erase(++std_string_set.begin(), ++(++(++std_string_set.begin())));
	ft_string_set.erase(++ft_string_set.begin(), ++(++(++ft_string_set.begin())));

	compareContent(std_char_set, ft_char_set);
	compareContent(std_string_set, ft_string_set);

	std_char_set.erase(std_char_set.begin(), std_char_set.begin());
	ft_char_set.erase(ft_char_set.begin(), ft_char_set.begin());
	std_string_set.erase(std_string_set.begin(), std_string_set.begin());
	ft_string_set.erase(ft_string_set.begin(), ft_string_set.begin());

	compareContent(std_char_set, ft_char_set);
	compareContent(std_string_set, ft_string_set);
}

TEST(SetModifiers, SetSwap)
{
	std::set<char>			other_std_char_set;
	ft::set<char>			other_ft_char_set;
	std::set<std::string>	other_std_string_set;
	ft::set<std::string>	other_ft_string_set;

	std::set<char>::iterator		std_char_set_it;
	ft::set<char>::iterator			ft_char_set_it;
	std::set<std::string>::iterator	std_string_set_it;
	ft::set<std::string>::iterator	ft_string_set_it;

	for (int i = 0; i < 5; i++)
	{
		other_std_char_set.insert(i + 64);
		other_ft_char_set.insert(i + 64);
	}
	other_std_string_set.insert("qwer");
	other_std_string_set.insert("asdf");
	other_std_string_set.insert("zxcv");
	other_std_string_set.insert("hjkl");
	other_std_string_set.insert("yuio");
	other_ft_string_set.insert("qwer");
	other_ft_string_set.insert("asdf");
	other_ft_string_set.insert("zxcv");
	other_ft_string_set.insert("hjkl");
	other_ft_string_set.insert("yuio");

	compareContent(std_char_set, ft_char_set);
	compareContent(std_string_set, ft_string_set);
	compareContent(other_std_char_set, other_ft_char_set);
	compareContent(other_std_string_set, other_ft_string_set);

	ft_char_set_it = ft_char_set.begin();
	ft_string_set_it = ft_string_set.begin();

	std_char_set.swap(other_std_char_set);
	ft_char_set.swap(other_ft_char_set);
	std_string_set.swap(other_std_string_set);
	ft_string_set.swap(other_ft_string_set);

	compareContent(std_char_set, ft_char_set);
	compareContent(std_string_set, ft_string_set);
	compareContent(other_std_char_set, other_ft_char_set);
	compareContent(other_std_string_set, other_ft_string_set);

	POINTERS_EQUAL(&(*ft_char_set_it), &(*other_ft_char_set.begin()));
	POINTERS_EQUAL(&(*ft_string_set_it), &(*other_ft_string_set.begin()));
}

TEST(SetModifiers, SetClear)
{
	std_char_set.clear();
	ft_char_set.clear();
	std_string_set.clear();
	ft_string_set.clear();

	compareContent(std_char_set, ft_char_set);
	compareContent(std_string_set, ft_string_set);
}

TEST_GROUP(SetMiscellaneous)
{
};

TEST(SetMiscellaneous, SetGetAllocator)
{
	ft::set<char>	ftset;

	ft::set<char>::allocator_type ft_allocator = ftset.get_allocator();
}

TEST_GROUP(SetOperations)
{
	std::list<char>			list_char;
	std::list<std::string>	list_string;

	std::set<char>			std_char_set;
	ft::set<char>			ft_char_set;
	std::set<std::string>	std_string_set;
	ft::set<std::string>	ft_string_set;

	std::set<char>::iterator			std_char_set_it, std_char_set_ite;
	ft::set<char>::iterator			ft_char_set_it, ft_char_set_ite;
	std::set<std::string>::iterator	std_string_set_it, std_string_set_ite;
	ft::set<std::string>::iterator		ft_string_set_it, ft_string_set_ite;

	void setup()
	{
		list_char.push_back('a');
		list_char.push_back('b');
		list_char.push_back('c');
		list_char.push_back('d');
		list_char.push_back('e');
		list_char.push_back('f');
		list_char.push_back('g');
		list_char.push_back('h');
		list_char.push_back('i');
		list_string.push_back("Bonjour");
		list_string.push_back("Hello");
		list_string.push_back("Guten Tag");
		list_string.push_back("Hola");
		list_string.push_back("Buongiorno???");
		list_string.push_back("Fuck");
		list_string.push_back("I'm not great");
		list_string.push_back("with languages");
		list_string.push_back("after all");
		list_char.push_back('a');
		list_char.push_back('b');
		list_char.push_back('c');
		list_char.push_back('d');
		list_char.push_back('e');
		list_char.push_back('f');
		list_char.push_back('g');
		list_char.push_back('h');
		list_char.push_back('i');
		list_string.push_back("Bonjour");
		list_string.push_back("Hello");
		list_string.push_back("Guten Tag");
		list_string.push_back("Hola");
		list_string.push_back("Buongiorno???");
		list_string.push_back("Fuck");
		list_string.push_back("I'm not great");
		list_string.push_back("with languages");
		list_string.push_back("after all");
		std_char_set.insert(list_char.begin(), list_char.end());
		ft_char_set.insert(list_char.begin(), list_char.end());
		std_string_set.insert(list_string.begin(), list_string.end());
		ft_string_set.insert(list_string.begin(), list_string.end());
		std_char_set_ite = std_char_set.end();
		ft_char_set_ite = ft_char_set.end();
		std_string_set_ite = std_string_set.end();
		ft_string_set_ite = ft_string_set.end();
	}
};

TEST(SetOperations, SetFind)
{
	std_char_set_it = std_char_set.find('c');
	ft_char_set_it = ft_char_set.find('c');
	std_string_set_it = std_string_set.find("Hello");
	ft_string_set_it = ft_string_set.find("Hello");

	compareIterators(std_char_set_it, ft_char_set_it);
	compareIterators(std_string_set_it, ft_string_set_it);
	CHECK_EQUAL((std_char_set_it == std_char_set_ite), (ft_char_set_it == ft_char_set_ite));
	CHECK_EQUAL((std_string_set_it == std_string_set_ite), (ft_string_set_it == ft_string_set_ite));

	std_char_set_it = std_char_set.find('x');
	ft_char_set_it = ft_char_set.find('x');
	std_string_set_it = std_string_set.find("I do not exist");
	ft_string_set_it = ft_string_set.find("I do not exist");

	CHECK_EQUAL((std_char_set_it == std_char_set_ite), (ft_char_set_it == ft_char_set_ite));
	CHECK_EQUAL((std_string_set_it == std_string_set_ite), (ft_string_set_it == ft_string_set_ite));

	std::set<char>::const_iterator			const_std_char_set_it = std_char_set.find('c');
	ft::set<char>::const_iterator			const_ft_char_set_it = ft_char_set.find('c');
	std::set<std::string>::const_iterator	const_std_string_set_it = std_string_set.find("Hello");
	ft::set<std::string>::const_iterator	const_ft_string_set_it = ft_string_set.find("Hello");

	compareIterators(const_std_char_set_it, const_ft_char_set_it);
	compareIterators(const_std_string_set_it, const_ft_string_set_it);
}

TEST(SetOperations, SetCount)
{
	CHECK_EQUAL(std_char_set.count('c'), ft_char_set.count('c'));
	CHECK_EQUAL(std_string_set.count("Hello"), ft_string_set.count("Hello"));
	CHECK_EQUAL(std_char_set.count('x'), ft_char_set.count('x'));
	CHECK_EQUAL(std_string_set.count("No"), ft_string_set.count("No"));
}

TEST(SetOperations, SetLowerBound)
{
	std_char_set_it = std_char_set.lower_bound('c');
	ft_char_set_it = ft_char_set.lower_bound('c');
	std_string_set_it = std_string_set.lower_bound("Hello");
	ft_string_set_it = ft_string_set.lower_bound("Hello");

	compareIterators(std_char_set_it, ft_char_set_it);
	compareIterators(std_string_set_it, ft_string_set_it);
	CHECK_EQUAL((std_char_set_it == std_char_set_ite), (ft_char_set_it == ft_char_set_ite));
	CHECK_EQUAL((std_string_set_it == std_string_set_ite), (ft_string_set_it == ft_string_set_ite));

	std_char_set.erase('c');
	ft_char_set.erase('c');
	std_string_set.erase("Hello");
	ft_string_set.erase("Hello");

	std_char_set_it = std_char_set.lower_bound('c');
	ft_char_set_it = ft_char_set.lower_bound('c');
	std_string_set_it = std_string_set.lower_bound("Hello");
	ft_string_set_it = ft_string_set.lower_bound("Hello");

	compareIterators(std_char_set_it, ft_char_set_it);
	compareIterators(std_string_set_it, ft_string_set_it);
	CHECK_EQUAL((std_char_set_it == std_char_set_ite), (ft_char_set_it == ft_char_set_ite));
	CHECK_EQUAL((std_string_set_it == std_string_set_ite), (ft_string_set_it == ft_string_set_ite));

	std_char_set_it = std_char_set.lower_bound('x');
	ft_char_set_it = ft_char_set.lower_bound('x');
	std_string_set_it = std_string_set.lower_bound("I do not exist");
	ft_string_set_it = ft_string_set.lower_bound("I do not exist");

	CHECK_EQUAL((std_char_set_it == std_char_set_ite), (ft_char_set_it == ft_char_set_ite));
	CHECK_EQUAL((std_string_set_it == std_string_set_ite), (ft_string_set_it == ft_string_set_ite));
}

TEST(SetOperations, SetUpperBound)
{
	std_char_set_it = std_char_set.upper_bound('c');
	ft_char_set_it = ft_char_set.upper_bound('c');
	std_string_set_it = std_string_set.upper_bound("Hello");
	ft_string_set_it = ft_string_set.upper_bound("Hello");

	compareIterators(std_char_set_it, ft_char_set_it);
	compareIterators(std_string_set_it, ft_string_set_it);
	CHECK_EQUAL((std_char_set_it == std_char_set_ite), (ft_char_set_it == ft_char_set_ite));
	CHECK_EQUAL((std_string_set_it == std_string_set_ite), (ft_string_set_it == ft_string_set_ite));

	std_char_set.erase('c');
	ft_char_set.erase('c');
	std_string_set.erase("Hello");
	ft_string_set.erase("Hello");

	std_char_set_it = std_char_set.upper_bound('c');
	ft_char_set_it = ft_char_set.upper_bound('c');
	std_string_set_it = std_string_set.upper_bound("Hello");
	ft_string_set_it = ft_string_set.upper_bound("Hello");

	compareIterators(std_char_set_it, ft_char_set_it);
	compareIterators(std_string_set_it, ft_string_set_it);
	CHECK_EQUAL((std_char_set_it == std_char_set_ite), (ft_char_set_it == ft_char_set_ite));
	CHECK_EQUAL((std_string_set_it == std_string_set_ite), (ft_string_set_it == ft_string_set_ite));

	std_char_set_it = std_char_set.upper_bound('x');
	ft_char_set_it = ft_char_set.upper_bound('x');
	std_string_set_it = std_string_set.upper_bound("I do not exist");
	ft_string_set_it = ft_string_set.upper_bound("I do not exist");

	CHECK_EQUAL((std_char_set_it == std_char_set_ite), (ft_char_set_it == ft_char_set_ite));
	CHECK_EQUAL((std_string_set_it == std_string_set_ite), (ft_string_set_it == ft_string_set_ite));
}

TEST(SetOperations, SetEqualRange)
{
	std::pair< std::set<char>::iterator, std::set<char>::iterator > std_char_range;
	std::pair< ft::set<char>::iterator, ft::set<char>::iterator > ft_char_range;
	std::pair< std::set<std::string>::iterator, std::set<std::string>::iterator > std_string_range;
	std::pair< ft::set<std::string>::iterator, ft::set<std::string>::iterator > ft_string_range;

	std_char_range = std_char_set.equal_range('c');
	ft_char_range = ft_char_set.equal_range('c');
	std_string_range = std_string_set.equal_range("Hello");
	ft_string_range = ft_string_set.equal_range("Hello");

	compareIterators(std_char_range.first, ft_char_range.first);
	compareIterators(std_string_range.first, ft_string_range.first);
	compareIterators(std_char_range.second, ft_char_range.second);
	compareIterators(std_string_range.second, ft_string_range.second);
	CHECK_EQUAL((std_char_range.first == std_char_set_ite), (ft_char_range.first == ft_char_set_ite));
	CHECK_EQUAL((std_string_range.first == std_string_set_ite), (ft_string_range.first == ft_string_set_ite));
	CHECK_EQUAL((std_char_range.second == std_char_set_ite), (ft_char_range.second == ft_char_set_ite));
	CHECK_EQUAL((std_string_range.second == std_string_set_ite), (ft_string_range.second == ft_string_set_ite));

	std_char_set.erase('c');
	ft_char_set.erase('c');
	std_string_set.erase("Hello");
	ft_string_set.erase("Hello");

	std_char_range = std_char_set.equal_range('c');
	ft_char_range = ft_char_set.equal_range('c');
	std_string_range = std_string_set.equal_range("Hello");
	ft_string_range = ft_string_set.equal_range("Hello");

	compareIterators(std_char_range.first, ft_char_range.first);
	compareIterators(std_string_range.first, ft_string_range.first);
	compareIterators(std_char_range.second, ft_char_range.second);
	compareIterators(std_string_range.second, ft_string_range.second);
	CHECK_EQUAL((std_char_range.first == std_char_set_ite), (ft_char_range.first == ft_char_set_ite));
	CHECK_EQUAL((std_string_range.first == std_string_set_ite), (ft_string_range.first == ft_string_set_ite));
	CHECK_EQUAL((std_char_range.second == std_char_set_ite), (ft_char_range.second == ft_char_set_ite));
	CHECK_EQUAL((std_string_range.second == std_string_set_ite), (ft_string_range.second == ft_string_set_ite));

	std_char_range = std_char_set.equal_range('x');
	ft_char_range = ft_char_set.equal_range('x');
	std_string_range = std_string_set.equal_range("I do not exist");
	ft_string_range = ft_string_set.equal_range("I do not exist");

	CHECK_EQUAL((std_char_range.first == std_char_set_ite), (ft_char_range.first == ft_char_set_ite));
	CHECK_EQUAL((std_string_range.first == std_string_set_ite), (ft_string_range.first == ft_string_set_ite));
	CHECK_EQUAL((std_char_range.second == std_char_set_ite), (ft_char_range.second == ft_char_set_ite));
	CHECK_EQUAL((std_string_range.second == std_string_set_ite), (ft_string_range.second == ft_string_set_ite));
}
