/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_tests.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pohl <pohl@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 08:59:01 by pohl              #+#    #+#             */
/*   Updated: 2022/02/15 18:21:47 by pohl             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <typeinfo>
#include <list>
#include <map>
#include "map.hpp"
#include "CppUTest/TestHarness.h"
#include "CppUTest/UtestMacros.h"

template< typename StdIt, typename FtIt >
void	checkIteratorsEqual( StdIt stdIt, FtIt ftIt, bool print = false )
{
		if (print)
			std::cout << stdIt->first << ", " << stdIt->second << " | "
				<< ftIt->first << ", " << ftIt->second << std::endl;
		else
		{
			CHECK_EQUAL(stdIt->first, ftIt->first);
			CHECK_EQUAL(stdIt->second, ftIt->second);
		}
}

template< typename StdMap, typename FtMap >
void	compareContent( StdMap& stdMap, FtMap& ftMap, bool print = false )
{
	typename StdMap::iterator	std_begin, std_end;
	typename FtMap::iterator	ft_begin, ft_end;

	std_begin = stdMap.begin();
	std_end = stdMap.end();
	ft_begin = ftMap.begin();
	ft_end = ftMap.end();
	if (print)
		std::cout << "std | ft" << std::endl;
	else
	{
		CHECK_EQUAL_TEXT(stdMap.size(), ftMap.size(), "Size");
		CHECK_EQUAL_TEXT(stdMap.max_size() , ftMap.max_size(), "Max Size");
	}
	while (std_begin != std_end)
		checkIteratorsEqual(std_begin++, ft_begin++, print);
}

TEST_GROUP(MapMemberFunctions)
{
	std::list<ft::pair<const int, char> >			ft_list_char;
	std::list<ft::pair<const int, std::string> >	ft_list_string;
	std::list<std::pair<int, char> >		std_list_char;
	std::list<std::pair<int, std::string> >	std_list_string;

	void setup()
	{
		ft_list_char.push_back(ft::make_pair(1, 'a'));
		ft_list_char.push_back(ft::make_pair(2, 'b'));
		ft_list_char.push_back(ft::make_pair(3, 'c'));
		ft_list_char.push_back(ft::make_pair(4, 'd'));
		ft_list_char.push_back(ft::make_pair(5, 'e'));
		ft_list_char.push_back(ft::make_pair(6, 'f'));
		ft_list_char.push_back(ft::make_pair(7, 'g'));
		ft_list_char.push_back(ft::make_pair(8, 'h'));
		ft_list_char.push_back(ft::make_pair(9, 'i'));
		ft_list_string.push_back(ft::make_pair(1, "Bonjour"));
		ft_list_string.push_back(ft::make_pair(2, "Hello"));
		ft_list_string.push_back(ft::make_pair(3, "Guten Tag"));
		ft_list_string.push_back(ft::make_pair(4, "Hola"));
		ft_list_string.push_back(ft::make_pair(5, "Buongiorno???"));
		ft_list_string.push_back(ft::make_pair(6, "Fuck"));
		ft_list_string.push_back(ft::make_pair(7, "I'm not great"));
		ft_list_string.push_back(ft::make_pair(8, "with languages"));
		ft_list_string.push_back(ft::make_pair(9, "after all"));
		std_list_char.push_back(std::make_pair(1, 'a'));
		std_list_char.push_back(std::make_pair(2, 'b'));
		std_list_char.push_back(std::make_pair(3, 'c'));
		std_list_char.push_back(std::make_pair(4, 'd'));
		std_list_char.push_back(std::make_pair(5, 'e'));
		std_list_char.push_back(std::make_pair(6, 'f'));
		std_list_char.push_back(std::make_pair(7, 'g'));
		std_list_char.push_back(std::make_pair(8, 'h'));
		std_list_char.push_back(std::make_pair(9, 'i'));
		std_list_string.push_back(std::make_pair(1, "Bonjour"));
		std_list_string.push_back(std::make_pair(2, "Hello"));
		std_list_string.push_back(std::make_pair(3, "Guten Tag"));
		std_list_string.push_back(std::make_pair(4, "Hola"));
		std_list_string.push_back(std::make_pair(5, "Buongiorno???"));
		std_list_string.push_back(std::make_pair(6, "Fuck"));
		std_list_string.push_back(std::make_pair(7, "I'm not great"));
		std_list_string.push_back(std::make_pair(8, "with languages"));
		std_list_string.push_back(std::make_pair(9, "after all"));
	}
};

TEST(MapMemberFunctions, EmptyConstructor)
{
	/* std::cout << "MapMemberFunctions.EmptyConstructor" << std::endl; */
	std::map<int, char>			std_char_map;
	ft::map<int, char>			ft_char_map;
	std::map<int, std::string>	std_string_map;
	ft::map<int, std::string>	ft_string_map;
	/* std::cout << "MapMemberFunctions.EmptyConstructor" << std::endl; */
}

TEST(MapMemberFunctions, InputIteratorConstructor)
{
	/* std::cout << "MapMemberFunctions.InputIteratorConstructor" << std::endl; */
	std::map<int, char>			std_char_map(std_list_char.begin(), std_list_char.end());
	ft::map<int, char>			ft_char_map(ft_list_char.begin(), ft_list_char.end());;
	std::map<int, std::string>	std_string_map(std_list_string.begin(), std_list_string.end());;
	ft::map<int, std::string>	ft_string_map(ft_list_string.begin(), ft_list_string.end());;

	compareContent(std_char_map, ft_char_map);
	compareContent(std_string_map, ft_string_map);
	/* std::cout << "MapMemberFunctions.InputIteratorConstructor" << std::endl; */
}

TEST(MapMemberFunctions, CopyConstructor)
{
	/* std::cout << "MapMemberFunctions.CopyConstructor" << std::endl; */
	std::map<int, char>			std_char_map(std_list_char.begin(), std_list_char.end());
	ft::map<int, char>			ft_char_map(ft_list_char.begin(), ft_list_char.end());;
	std::map<int, std::string>	std_string_map(std_list_string.begin(), std_list_string.end());;
	ft::map<int, std::string>	ft_string_map(ft_list_string.begin(), ft_list_string.end());;

	std::map<int, char>			std_char_map_copy(std_char_map);
	ft::map<int, char>			ft_char_map_copy(ft_char_map);;
	std::map<int, std::string>	std_string_map_copy(std_string_map);;
	ft::map<int, std::string>	ft_string_map_copy(ft_string_map);;

	std_char_map.insert(std::make_pair(42, 'x'));
	ft_char_map.insert(ft::make_pair(42, 'x'));

	compareContent(std_char_map, ft_char_map);
	compareContent(std_string_map, ft_string_map);
	compareContent(std_char_map_copy, ft_char_map_copy);
	compareContent(std_string_map_copy, ft_string_map_copy);
	/* std::cout << "MapMemberFunctions.CopyConstructor END" << std::endl; */
}

TEST(MapMemberFunctions, EqualOperator)
{
	/* std::cout << "MapMemberFunctions.EqualOperator" << std::endl; */
	std::map<int, char>			std_char_map(std_list_char.begin(), std_list_char.end());
	ft::map<int, char>			ft_char_map(ft_list_char.begin(), ft_list_char.end());;
	std::map<int, std::string>	std_string_map(std_list_string.begin(), std_list_string.end());;
	ft::map<int, std::string>	ft_string_map(ft_list_string.begin(), ft_list_string.end());;

	std::map<int, char>			std_char_map_copy;
	ft::map<int, char>			ft_char_map_copy;
	std::map<int, std::string>	std_string_map_copy;
	ft::map<int, std::string>	ft_string_map_copy;

	std_char_map_copy = std_char_map;
	ft_char_map_copy = ft_char_map;
	ft_string_map_copy = ft_string_map;
	std_string_map_copy = std_string_map;

	std_char_map.insert(std::make_pair(42, 'x'));
	ft_char_map.insert(ft::make_pair(42, 'x'));

	compareContent(std_char_map, ft_char_map);
	compareContent(std_string_map, ft_string_map);
	compareContent(std_char_map_copy, ft_char_map_copy);
	compareContent(std_string_map_copy, ft_string_map_copy);
	/* std::cout << "MapMemberFunctions.EqualOperator END" << std::endl; */
}

TEST_GROUP(MapIterators)
{
	std::list<ft::pair<const int, char> >			ft_list_char;
	std::list<ft::pair<const int, std::string> >	ft_list_string;
	std::list<std::pair<int, char> >		std_list_char;
	std::list<std::pair<int, std::string> >	std_list_string;

	std::map<int, char>			std_char_map;
	ft::map<int, char>			ft_char_map;
	std::map<int, std::string>	std_string_map;
	ft::map<int, std::string>	ft_string_map;

	std::map<int, char>::iterator			std_char_map_it, std_char_map_ite;
	ft::map<int, char>::iterator			ft_char_map_it, ft_char_map_ite;
	std::map<int, std::string>::iterator	std_string_map_it, std_string_map_ite;
	ft::map<int, std::string>::iterator		ft_string_map_it, ft_string_map_ite;

	void setup()
	{
		ft_list_char.push_back(ft::make_pair(1, 'a'));
		ft_list_char.push_back(ft::make_pair(2, 'b'));
		ft_list_char.push_back(ft::make_pair(3, 'c'));
		ft_list_char.push_back(ft::make_pair(4, 'd'));
		ft_list_char.push_back(ft::make_pair(5, 'e'));
		ft_list_char.push_back(ft::make_pair(6, 'f'));
		ft_list_char.push_back(ft::make_pair(7, 'g'));
		ft_list_char.push_back(ft::make_pair(8, 'h'));
		ft_list_char.push_back(ft::make_pair(9, 'i'));
		ft_list_string.push_back(ft::make_pair(1, "Bonjour"));
		ft_list_string.push_back(ft::make_pair(2, "Hello"));
		ft_list_string.push_back(ft::make_pair(3, "Guten Tag"));
		ft_list_string.push_back(ft::make_pair(4, "Hola"));
		ft_list_string.push_back(ft::make_pair(5, "Buongiorno???"));
		ft_list_string.push_back(ft::make_pair(6, "Fuck"));
		ft_list_string.push_back(ft::make_pair(7, "I'm not great"));
		ft_list_string.push_back(ft::make_pair(8, "with languages"));
		ft_list_string.push_back(ft::make_pair(9, "after all"));
		std_list_char.push_back(std::make_pair(1, 'a'));
		std_list_char.push_back(std::make_pair(2, 'b'));
		std_list_char.push_back(std::make_pair(3, 'c'));
		std_list_char.push_back(std::make_pair(4, 'd'));
		std_list_char.push_back(std::make_pair(5, 'e'));
		std_list_char.push_back(std::make_pair(6, 'f'));
		std_list_char.push_back(std::make_pair(7, 'g'));
		std_list_char.push_back(std::make_pair(8, 'h'));
		std_list_char.push_back(std::make_pair(9, 'i'));
		std_list_string.push_back(std::make_pair(1, "Bonjour"));
		std_list_string.push_back(std::make_pair(2, "Hello"));
		std_list_string.push_back(std::make_pair(3, "Guten Tag"));
		std_list_string.push_back(std::make_pair(4, "Hola"));
		std_list_string.push_back(std::make_pair(5, "Buongiorno???"));
		std_list_string.push_back(std::make_pair(6, "Fuck"));
		std_list_string.push_back(std::make_pair(7, "I'm not great"));
		std_list_string.push_back(std::make_pair(8, "with languages"));
		std_list_string.push_back(std::make_pair(9, "after all"));
		std_char_map.insert(std_list_char.begin(), std_list_char.end());
		ft_char_map.insert(ft_list_char.begin(), ft_list_char.end());
		std_string_map.insert(std_list_string.begin(), std_list_string.end());
		ft_string_map.insert(ft_list_string.begin(), ft_list_string.end());
	}
};

TEST(MapIterators, Arithmetics)
{
	/* std::cout << "MapIterators.Arithmetics" << std::endl; */
	std_char_map_it = std_char_map.begin();
	std_char_map_ite = std_char_map.end();
	ft_char_map_it = ft_char_map.begin();
	ft_char_map_ite = ft_char_map.end();
	std_string_map_it = std_string_map.begin();
	std_string_map_ite = std_string_map.end();
	ft_string_map_it = ft_string_map.begin();
	ft_string_map_ite = ft_string_map.end();

	checkIteratorsEqual(std_char_map_it, ft_char_map_it);
	checkIteratorsEqual(std_string_map_it, ft_string_map_it);

	std_char_map_it++;
	ft_char_map_it++;
	std_string_map_it++;
	ft_string_map_it++;

	checkIteratorsEqual(std_char_map_it, ft_char_map_it);
	checkIteratorsEqual(std_string_map_it, ft_string_map_it);

	std_char_map_it--;
	ft_char_map_it--;
	std_string_map_it--;
	ft_string_map_it--;

	checkIteratorsEqual(std_char_map_it, ft_char_map_it);
	checkIteratorsEqual(std_string_map_it, ft_string_map_it);

	checkIteratorsEqual(std_char_map_it++, ft_char_map_it++);
	checkIteratorsEqual(std_string_map_it++, ft_string_map_it++);
	checkIteratorsEqual(++std_char_map_it, ++ft_char_map_it);
	checkIteratorsEqual(++std_string_map_it, ++ft_string_map_it);
	checkIteratorsEqual(std_char_map_it--, ft_char_map_it--);
	checkIteratorsEqual(std_string_map_it--, ft_string_map_it--);
	checkIteratorsEqual(--std_char_map_it, --ft_char_map_it);
	checkIteratorsEqual(--std_string_map_it, --ft_string_map_it);

	CHECK_EQUAL((std_char_map_it == std_char_map_ite), (ft_char_map_it == ft_char_map_ite));
	CHECK_EQUAL((std_string_map_it == std_string_map_ite), (ft_string_map_it == ft_string_map_ite));
	CHECK_EQUAL((std_char_map_it != std_char_map_ite), (ft_char_map_it != ft_char_map_ite));
	CHECK_EQUAL((std_string_map_it != std_string_map_ite), (ft_string_map_it != ft_string_map_ite));
	/* std::cout << "MapIterators.Arithmetics END" << std::endl; */
}

TEST_GROUP(MapReverseIterators)
{
	std::list<ft::pair<const int, char> >			ft_list_char;
	std::list<ft::pair<const int, std::string> >	ft_list_string;
	std::list<std::pair<int, char> >		std_list_char;
	std::list<std::pair<int, std::string> >	std_list_string;

	std::map<int, char>			std_char_map;
	ft::map<int, char>			ft_char_map;
	std::map<int, std::string>	std_string_map;
	ft::map<int, std::string>	ft_string_map;

	std::map<int, char>::reverse_iterator			std_char_map_it, std_char_map_ite;
	ft::map<int, char>::reverse_iterator			ft_char_map_it, ft_char_map_ite;
	std::map<int, std::string>::reverse_iterator	std_string_map_it, std_string_map_ite;
	ft::map<int, std::string>::reverse_iterator		ft_string_map_it, ft_string_map_ite;

	void setup()
	{
		ft_list_char.push_back(ft::make_pair(1, 'a'));
		ft_list_char.push_back(ft::make_pair(2, 'b'));
		ft_list_char.push_back(ft::make_pair(3, 'c'));
		ft_list_char.push_back(ft::make_pair(4, 'd'));
		ft_list_char.push_back(ft::make_pair(5, 'e'));
		ft_list_char.push_back(ft::make_pair(6, 'f'));
		ft_list_char.push_back(ft::make_pair(7, 'g'));
		ft_list_char.push_back(ft::make_pair(8, 'h'));
		ft_list_char.push_back(ft::make_pair(9, 'i'));
		ft_list_string.push_back(ft::make_pair(1, "Bonjour"));
		ft_list_string.push_back(ft::make_pair(2, "Hello"));
		ft_list_string.push_back(ft::make_pair(3, "Guten Tag"));
		ft_list_string.push_back(ft::make_pair(4, "Hola"));
		ft_list_string.push_back(ft::make_pair(5, "Buongiorno???"));
		ft_list_string.push_back(ft::make_pair(6, "Fuck"));
		ft_list_string.push_back(ft::make_pair(7, "I'm not great"));
		ft_list_string.push_back(ft::make_pair(8, "with languages"));
		ft_list_string.push_back(ft::make_pair(9, "after all"));
		std_list_char.push_back(std::make_pair(1, 'a'));
		std_list_char.push_back(std::make_pair(2, 'b'));
		std_list_char.push_back(std::make_pair(3, 'c'));
		std_list_char.push_back(std::make_pair(4, 'd'));
		std_list_char.push_back(std::make_pair(5, 'e'));
		std_list_char.push_back(std::make_pair(6, 'f'));
		std_list_char.push_back(std::make_pair(7, 'g'));
		std_list_char.push_back(std::make_pair(8, 'h'));
		std_list_char.push_back(std::make_pair(9, 'i'));
		std_list_string.push_back(std::make_pair(1, "Bonjour"));
		std_list_string.push_back(std::make_pair(2, "Hello"));
		std_list_string.push_back(std::make_pair(3, "Guten Tag"));
		std_list_string.push_back(std::make_pair(4, "Hola"));
		std_list_string.push_back(std::make_pair(5, "Buongiorno???"));
		std_list_string.push_back(std::make_pair(6, "Fuck"));
		std_list_string.push_back(std::make_pair(7, "I'm not great"));
		std_list_string.push_back(std::make_pair(8, "with languages"));
		std_list_string.push_back(std::make_pair(9, "after all"));
		std_char_map.insert(std_list_char.begin(), std_list_char.end());
		ft_char_map.insert(ft_list_char.begin(), ft_list_char.end());
		std_string_map.insert(std_list_string.begin(), std_list_string.end());
		ft_string_map.insert(ft_list_string.begin(), ft_list_string.end());
	}
};

TEST(MapReverseIterators, Arithmetics)
{
	std_char_map_it = std_char_map.rbegin();
	std_char_map_ite = std_char_map.rend();
	ft_char_map_it = ft_char_map.rbegin();
	ft_char_map_ite = ft_char_map.rend();
	std_string_map_it = std_string_map.rbegin();
	std_string_map_ite = std_string_map.rend();
	ft_string_map_it = ft_string_map.rbegin();
	ft_string_map_ite = ft_string_map.rend();

	checkIteratorsEqual(std_char_map_it, ft_char_map_it);
	checkIteratorsEqual(std_string_map_it, ft_string_map_it);

	std_char_map_it++;
	ft_char_map_it++;
	std_string_map_it++;
	ft_string_map_it++;

	checkIteratorsEqual(std_char_map_it, ft_char_map_it);
	checkIteratorsEqual(std_string_map_it, ft_string_map_it);

	std_char_map_it--;
	ft_char_map_it--;
	std_string_map_it--;
	ft_string_map_it--;

	checkIteratorsEqual(std_char_map_it, ft_char_map_it);
	checkIteratorsEqual(std_string_map_it, ft_string_map_it);

	checkIteratorsEqual(std_char_map_it++, ft_char_map_it++);
	checkIteratorsEqual(std_string_map_it++, ft_string_map_it++);
	checkIteratorsEqual(++std_char_map_it, ++ft_char_map_it);
	checkIteratorsEqual(++std_string_map_it, ++ft_string_map_it);
	checkIteratorsEqual(std_char_map_it--, ft_char_map_it--);
	checkIteratorsEqual(std_string_map_it--, ft_string_map_it--);
	checkIteratorsEqual(--std_char_map_it, --ft_char_map_it);
	checkIteratorsEqual(--std_string_map_it, --ft_string_map_it);

	CHECK_EQUAL((std_char_map_it == std_char_map_ite), (ft_char_map_it == ft_char_map_ite));
	CHECK_EQUAL((std_string_map_it == std_string_map_ite), (ft_string_map_it == ft_string_map_ite));
	CHECK_EQUAL((std_char_map_it != std_char_map_ite), (ft_char_map_it != ft_char_map_ite));
	CHECK_EQUAL((std_string_map_it != std_string_map_ite), (ft_string_map_it != ft_string_map_ite));
}

TEST(MapReverseIterators, Base)
{
	std_char_map_it = std_char_map.rbegin();
	std_char_map_ite = std_char_map.rend();
	ft_char_map_it = ft_char_map.rbegin();
	ft_char_map_ite = ft_char_map.rend();
	std_string_map_it = std_string_map.rbegin();
	std_string_map_ite = std_string_map.rend();
	ft_string_map_it = ft_string_map.rbegin();
	ft_string_map_ite = ft_string_map.rend();

	std_char_map_it++;
	ft_char_map_it++;
	std_string_map_it++;
	ft_string_map_it++;

	checkIteratorsEqual(std_char_map_it.base(), ft_char_map_it.base());
	checkIteratorsEqual(std_string_map_it.base(), ft_string_map_it.base());

	checkIteratorsEqual(std_char_map_ite.base(), ft_char_map_ite.base());
	checkIteratorsEqual(std_string_map_ite.base(), ft_string_map_ite.base());
}

TEST_GROUP(MapCapacity)
{
	std::list<ft::pair<const int, char> >			ft_list_char;
	std::list<ft::pair<const int, std::string> >	ft_list_string;
	std::list<std::pair<int, char> >		std_list_char;
	std::list<std::pair<int, std::string> >	std_list_string;

	std::map<int, char>			std_char_map;
	ft::map<int, char>			ft_char_map;
	std::map<int, std::string>	std_string_map;
	ft::map<int, std::string>	ft_string_map;

	void setup()
	{
		ft_list_char.push_back(ft::make_pair(1, 'a'));
		ft_list_char.push_back(ft::make_pair(2, 'b'));
		ft_list_char.push_back(ft::make_pair(3, 'c'));
		ft_list_char.push_back(ft::make_pair(4, 'd'));
		ft_list_char.push_back(ft::make_pair(5, 'e'));
		ft_list_char.push_back(ft::make_pair(6, 'f'));
		ft_list_char.push_back(ft::make_pair(7, 'g'));
		ft_list_char.push_back(ft::make_pair(8, 'h'));
		ft_list_char.push_back(ft::make_pair(9, 'i'));
		ft_list_string.push_back(ft::make_pair(1, "Bonjour"));
		ft_list_string.push_back(ft::make_pair(2, "Hello"));
		ft_list_string.push_back(ft::make_pair(3, "Guten Tag"));
		ft_list_string.push_back(ft::make_pair(4, "Hola"));
		ft_list_string.push_back(ft::make_pair(5, "Buongiorno???"));
		ft_list_string.push_back(ft::make_pair(6, "Fuck"));
		ft_list_string.push_back(ft::make_pair(7, "I'm not great"));
		ft_list_string.push_back(ft::make_pair(8, "with languages"));
		ft_list_string.push_back(ft::make_pair(9, "after all"));
		std_list_char.push_back(std::make_pair(1, 'a'));
		std_list_char.push_back(std::make_pair(2, 'b'));
		std_list_char.push_back(std::make_pair(3, 'c'));
		std_list_char.push_back(std::make_pair(4, 'd'));
		std_list_char.push_back(std::make_pair(5, 'e'));
		std_list_char.push_back(std::make_pair(6, 'f'));
		std_list_char.push_back(std::make_pair(7, 'g'));
		std_list_char.push_back(std::make_pair(8, 'h'));
		std_list_char.push_back(std::make_pair(9, 'i'));
		std_list_string.push_back(std::make_pair(1, "Bonjour"));
		std_list_string.push_back(std::make_pair(2, "Hello"));
		std_list_string.push_back(std::make_pair(3, "Guten Tag"));
		std_list_string.push_back(std::make_pair(4, "Hola"));
		std_list_string.push_back(std::make_pair(5, "Buongiorno???"));
		std_list_string.push_back(std::make_pair(6, "Fuck"));
		std_list_string.push_back(std::make_pair(7, "I'm not great"));
		std_list_string.push_back(std::make_pair(8, "with languages"));
		std_list_string.push_back(std::make_pair(9, "after all"));
		std_char_map.insert(std_list_char.begin(), std_list_char.end());
		ft_char_map.insert(ft_list_char.begin(), ft_list_char.end());
		std_string_map.insert(std_list_string.begin(), std_list_string.end());
		ft_string_map.insert(ft_list_string.begin(), ft_list_string.end());
	}
};

TEST(MapCapacity, Empty)
{
	/* std::cout << "MapCapacity.Empty" << std::endl; */
	CHECK_EQUAL(std_char_map.empty(), ft_char_map.empty());
	CHECK_EQUAL(std_string_map.empty(), ft_string_map.empty());

	std_char_map.clear();
	ft_char_map.clear();
	std_string_map.clear();
	ft_string_map.clear();

	CHECK_EQUAL(std_char_map.size(), ft_char_map.size());
	CHECK_EQUAL(std_string_map.size(), ft_string_map.size());
	CHECK_EQUAL(std_char_map.empty(), ft_char_map.empty());
	CHECK_EQUAL(std_string_map.empty(), ft_string_map.empty());

	std_char_map.insert(std::make_pair(1, 'a'));
	ft_char_map.insert(ft::make_pair(1, 'a'));
	std_string_map.insert(std::make_pair(1, "a"));
	ft_string_map.insert(ft::make_pair(1, "a"));

	CHECK_EQUAL(std_char_map.empty(), ft_char_map.empty());
	CHECK_EQUAL(std_string_map.empty(), ft_string_map.empty());
	/* std::cout << "MapCapacity.Empty END" << std::endl; */
}

TEST_GROUP(MapModifiers)
{
	std::list<ft::pair<const int, char> >			ft_list_char;
	std::list<ft::pair<const int, std::string> >	ft_list_string;
	std::list<std::pair<int, char> >		std_list_char;
	std::list<std::pair<int, std::string> >	std_list_string;

	std::map<int, char>			std_char_map;
	ft::map<int, char>			ft_char_map;
	std::map<int, std::string>	std_string_map;
	ft::map<int, std::string>	ft_string_map;

	void setup()
	{
		ft_list_char.push_back(ft::make_pair(1, 'a'));
		ft_list_char.push_back(ft::make_pair(2, 'b'));
		ft_list_char.push_back(ft::make_pair(3, 'c'));
		ft_list_char.push_back(ft::make_pair(4, 'd'));
		ft_list_char.push_back(ft::make_pair(5, 'e'));
		ft_list_char.push_back(ft::make_pair(6, 'f'));
		ft_list_char.push_back(ft::make_pair(7, 'g'));
		ft_list_char.push_back(ft::make_pair(8, 'h'));
		ft_list_char.push_back(ft::make_pair(9, 'i'));
		ft_list_string.push_back(ft::make_pair(1, "Bonjour"));
		ft_list_string.push_back(ft::make_pair(2, "Hello"));
		ft_list_string.push_back(ft::make_pair(3, "Guten Tag"));
		ft_list_string.push_back(ft::make_pair(4, "Hola"));
		ft_list_string.push_back(ft::make_pair(5, "Buongiorno???"));
		ft_list_string.push_back(ft::make_pair(6, "Fuck"));
		ft_list_string.push_back(ft::make_pair(7, "I'm not great"));
		ft_list_string.push_back(ft::make_pair(8, "with languages"));
		ft_list_string.push_back(ft::make_pair(9, "after all"));
		std_list_char.push_back(std::make_pair(1, 'a'));
		std_list_char.push_back(std::make_pair(2, 'b'));
		std_list_char.push_back(std::make_pair(3, 'c'));
		std_list_char.push_back(std::make_pair(4, 'd'));
		std_list_char.push_back(std::make_pair(5, 'e'));
		std_list_char.push_back(std::make_pair(6, 'f'));
		std_list_char.push_back(std::make_pair(7, 'g'));
		std_list_char.push_back(std::make_pair(8, 'h'));
		std_list_char.push_back(std::make_pair(9, 'i'));
		std_list_string.push_back(std::make_pair(1, "Bonjour"));
		std_list_string.push_back(std::make_pair(2, "Hello"));
		std_list_string.push_back(std::make_pair(3, "Guten Tag"));
		std_list_string.push_back(std::make_pair(4, "Hola"));
		std_list_string.push_back(std::make_pair(5, "Buongiorno???"));
		std_list_string.push_back(std::make_pair(6, "Fuck"));
		std_list_string.push_back(std::make_pair(7, "I'm not great"));
		std_list_string.push_back(std::make_pair(8, "with languages"));
		std_list_string.push_back(std::make_pair(9, "after all"));
		std_char_map.insert(std_list_char.begin(), std_list_char.end());
		ft_char_map.insert(ft_list_char.begin(), ft_list_char.end());
		std_string_map.insert(std_list_string.begin(), std_list_string.end());
		ft_string_map.insert(ft_list_string.begin(), ft_list_string.end());
	}
};

template< typename StdIt, typename FtIt >
void	compareInsertionReturn( std::pair<StdIt, bool> std_res,  ft::pair<FtIt, bool> ft_res )
{
	CHECK_EQUAL(std_res.second, ft_res.second);
	checkIteratorsEqual(std_res.first, ft_res.first, false);
}

TEST(MapModifiers, MapBasicInsertion)
{
	std::pair<std::map<int, char>::iterator, bool>			std_char_result;
	ft::pair<ft::map<int, char>::iterator, bool>			ft_char_result;
	std::pair<std::map<int, std::string>::iterator, bool>	std_string_result;
	ft::pair<ft::map<int, std::string>::iterator, bool>		ft_string_result;

	compareContent(std_char_map, ft_char_map);
	compareContent(std_string_map, ft_string_map);

	std_char_result = std_char_map.insert(std::make_pair(42, 'x'));
	ft_char_result = ft_char_map.insert(ft::make_pair(42, 'x'));
	std_string_result = std_string_map.insert(std::make_pair(42, "x"));
	ft_string_result = ft_string_map.insert(ft::make_pair(42, "x"));

	compareInsertionReturn(std_char_result, ft_char_result);
	compareInsertionReturn(std_string_result, ft_string_result);

	std_char_result = std_char_map.insert(std::make_pair(2, 'x'));
	ft_char_result = ft_char_map.insert(ft::make_pair(2, 'x'));
	std_string_result = std_string_map.insert(std::make_pair(2, "x"));
	ft_string_result = ft_string_map.insert(ft::make_pair(2, "x"));

	compareInsertionReturn(std_char_result, ft_char_result);
	compareInsertionReturn(std_string_result, ft_string_result);

	std_char_result = std_char_map.insert(std::make_pair(42, 'x'));
	ft_char_result = ft_char_map.insert(ft::make_pair(42, 'x'));
	std_string_result = std_string_map.insert(std::make_pair(42, "x"));
	ft_string_result = ft_string_map.insert(ft::make_pair(42, "x"));

	compareInsertionReturn(std_char_result, ft_char_result);
	compareInsertionReturn(std_string_result, ft_string_result);

	compareContent(std_char_map, ft_char_map);
	compareContent(std_string_map, ft_string_map);
}

TEST(MapModifiers, MapIteratorInsertion)
{
	std_list_char.push_back(std::make_pair(101, 'a'));
	std_list_char.push_back(std::make_pair(102, 'x'));
	ft_list_char.push_back(ft::make_pair(101, 'a'));
	ft_list_char.push_back(ft::make_pair(102, 'x'));
	std_list_string.push_back(std::make_pair(101, "asdf"));
	std_list_string.push_back(std::make_pair(102, "xcvv"));
	ft_list_string.push_back(ft::make_pair(101, "asdf"));
	ft_list_string.push_back(ft::make_pair(102, "xcvv"));

	std_char_map.insert(++(++std_list_char.begin()), std_list_char.end());
	ft_char_map.insert(++(++ft_list_char.begin()), ft_list_char.end());
	std_string_map.insert(++(++std_list_string.begin()), std_list_string.end());
	ft_string_map.insert(++(++ft_list_string.begin()), ft_list_string.end());

	compareContent(std_char_map, ft_char_map);
	compareContent(std_string_map, ft_string_map);
}

TEST(MapModifiers, MapHintInsertion)
{
	std::map<int, char>::iterator			std_char_it = --std_char_map.end();
	ft::map<int, char>::iterator			ft_char_it = --ft_char_map.end();
	std::map<int, std::string>::iterator	std_string_it = --std_string_map.end();
	ft::map<int, std::string>::iterator		ft_string_it = --ft_string_map.end();

	std_char_map.insert(std_char_it, std::pair<int, char>(10, 'j'));  // max efficiency inserting
	ft_char_map.insert(ft_char_it, ft::pair<int, char>(10, 'j'));  // max efficiency inserting
	std_string_map.insert(std_string_it, std::pair<int, std::string>(10, "j"));  // max efficiency inserting
	ft_string_map.insert(ft_string_it, ft::pair<int, std::string>(10, "j"));  // max efficiency inserting

	std_char_map.insert(std_char_it, std::pair<int, char>(12, 'j'));  // max efficiency inserting
	ft_char_map.insert(ft_char_it, ft::pair<int, char>(12, 'j'));  // max efficiency inserting
	std_string_map.insert(std_string_it, std::pair<int, std::string>(12, "j"));  // max efficiency inserting
	ft_string_map.insert(ft_string_it, ft::pair<int, std::string>(12, "j"));  // max efficiency inserting

	compareContent(std_char_map, ft_char_map);
	compareContent(std_string_map, ft_string_map);
}

TEST(MapModifiers, MapSquareBracketOperator)
{
	CHECK_EQUAL(std_char_map[5], ft_char_map[5]);
	CHECK_EQUAL(std_string_map[5], ft_string_map[5]);

	CHECK_EQUAL(std_char_map[42], ft_char_map[42]);
	CHECK_EQUAL(std_string_map[42], ft_string_map[42]);

	std_char_map[43] = 'w';
	ft_char_map[43] = 'w';
	std_string_map[43] = "w";
	ft_string_map[43] = "w";

	std_char_map[6] = 'u';
	ft_char_map[6] = 'u';
	std_string_map[6] = "u";
	ft_string_map[6] = "u";

	compareContent(std_char_map, ft_char_map);
	compareContent(std_string_map, ft_string_map);
}

TEST(MapModifiers, MapAt)
{
	CHECK_EQUAL(std_char_map.at(5), ft_char_map.at(5));
	CHECK_EQUAL(std_string_map.at(5), ft_string_map.at(5));

	try
	{
		ft_char_map.at(42);
	}
	catch ( std::out_of_range &e )
	{
		CHECK(true);
	}
	catch ( std::exception &e )
	{
		FAIL("out of range at must throw out_of_range exception");
	}
	try
	{
		ft_string_map.at(42);
	}
	catch ( std::out_of_range &e )
	{
		CHECK(true);
	}
	catch ( std::exception &e )
	{
		FAIL("out of range at must throw out_of_range exception");
	}

	std_char_map.at(6) = 'w';
	ft_char_map.at(6) = 'w';
	std_string_map.at(6) = "w";
	ft_string_map.at(6) = "w";

	compareContent(std_char_map, ft_char_map);
	compareContent(std_string_map, ft_string_map);
}

TEST(MapModifiers, MapErase)
{
	std_char_map.erase(--std_char_map.end());
	ft_char_map.erase(--ft_char_map.end());
	std_string_map.erase(--std_string_map.end());
	ft_string_map.erase(--ft_string_map.end());

	std_char_map.erase(std_char_map.begin());
	ft_char_map.erase(ft_char_map.begin());
	std_string_map.erase(std_string_map.begin());
	ft_string_map.erase(ft_string_map.begin());

	std_char_map.erase(5);
	ft_char_map.erase(5);
	std_string_map.erase(5);
	ft_string_map.erase(5);

	std_char_map.erase(++std_char_map.begin(), ++(++(++std_char_map.begin())));
	ft_char_map.erase(++ft_char_map.begin(), ++(++(++ft_char_map.begin())));
	std_string_map.erase(++std_string_map.begin(), ++(++(++std_string_map.begin())));
	ft_string_map.erase(++ft_string_map.begin(), ++(++(++ft_string_map.begin())));

	compareContent(std_char_map, ft_char_map);
	compareContent(std_string_map, ft_string_map);

	std_char_map.erase(std_char_map.begin(), std_char_map.begin());
	ft_char_map.erase(ft_char_map.begin(), ft_char_map.begin());
	std_string_map.erase(std_string_map.begin(), std_string_map.begin());
	ft_string_map.erase(ft_string_map.begin(), ft_string_map.begin());

	compareContent(std_char_map, ft_char_map);
	compareContent(std_string_map, ft_string_map);
}

TEST(MapModifiers, MapSwap)
{
	std::map<int, char>			other_std_char_map;
	ft::map<int, char>			other_ft_char_map;
	std::map<int, std::string>	other_std_string_map;
	ft::map<int, std::string>	other_ft_string_map;

	std::map<int, char>::iterator			std_char_map_it;
	ft::map<int, char>::iterator			ft_char_map_it;
	std::map<int, std::string>::iterator	std_string_map_it;
	ft::map<int, std::string>::iterator		ft_string_map_it;

	for (int i = 0; i < 5; i++)
	{
		other_std_char_map.insert(std::make_pair(i * 5, i + 64));
		other_ft_char_map.insert(ft::make_pair(i * 5, i + 64));
	}
	other_std_string_map.insert(std::make_pair(10, "qwer"));
	other_std_string_map.insert(std::make_pair(11, "asdf"));
	other_std_string_map.insert(std::make_pair(12, "zxcv"));
	other_std_string_map.insert(std::make_pair(12, "hjkl"));
	other_std_string_map.insert(std::make_pair(13, "yuio"));
	other_ft_string_map.insert(ft::make_pair(10, "qwer"));
	other_ft_string_map.insert(ft::make_pair(11, "asdf"));
	other_ft_string_map.insert(ft::make_pair(12, "zxcv"));
	other_ft_string_map.insert(ft::make_pair(12, "hjkl"));
	other_ft_string_map.insert(ft::make_pair(13, "yuio"));
	other_ft_string_map.printTree();

	compareContent(std_char_map, ft_char_map);
	compareContent(std_string_map, ft_string_map);
	compareContent(other_std_char_map, other_ft_char_map);
	compareContent(other_std_string_map, other_ft_string_map);

	ft_char_map_it = ft_char_map.begin();
	ft_string_map_it = ft_string_map.begin();

	std_char_map.swap(other_std_char_map);
	ft_char_map.swap(other_ft_char_map);
	std_string_map.swap(other_std_string_map);
	ft_string_map.swap(other_ft_string_map);

	compareContent(std_char_map, ft_char_map);
	compareContent(std_string_map, ft_string_map);
	compareContent(other_std_char_map, other_ft_char_map);
	compareContent(other_std_string_map, other_ft_string_map);

	POINTERS_EQUAL(&(*ft_char_map_it), &(*other_ft_char_map.begin()));
	POINTERS_EQUAL(&(*ft_string_map_it), &(*other_ft_string_map.begin()));
}

TEST(MapModifiers, MapClear)
{
	std_char_map.clear();
	ft_char_map.clear();
	std_string_map.clear();
	ft_string_map.clear();

	compareContent(std_char_map, ft_char_map);
	compareContent(std_string_map, ft_string_map);
}

TEST_GROUP(MapMiscellaneous)
{
};

TEST(MapMiscellaneous, MapKeyComp)
{
	  std::map<char,int>	stdmap;
	  ft::map<char,int>		ftmap;

	  ft::map<char,int>::key_compare ftcomp = ftmap.key_comp();

	  stdmap['a']=100;
	  ftmap['a']=100;
	  stdmap['b']=200;
	  ftmap['b']=200;
	  stdmap['c']=300;
	  ftmap['c']=300;

	  char stdhighest = stdmap.rbegin()->first;     // key value of last element
	  char fthighest = ftmap.rbegin()->first;     // key value of last element

	  CHECK_EQUAL(stdhighest, fthighest);
	  std::map<char,int>::iterator stdit = stdmap.begin();
	  ft::map<char,int>::iterator ftit = ftmap.begin();
	  do {
		  checkIteratorsEqual(stdit, ftit);
		  stdit++;
	  } while ( ftcomp((*ftit++).first, fthighest) );
}
