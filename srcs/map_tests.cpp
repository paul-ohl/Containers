/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_tests.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pohl <pohl@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 08:59:01 by pohl              #+#    #+#             */
/*   Updated: 2022/02/10 18:53:44 by pohl             ###   ########.fr       */
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
	std::map<int, char>			std_char_map;
	ft::map<int, char>			ft_char_map;
	std::map<int, std::string>	std_string_map;
	ft::map<int, std::string>	ft_string_map;
}

TEST(MapMemberFunctions, InputIteratorConstructor)
{
	std::map<int, char>			std_char_map(std_list_char.begin(), std_list_char.end());
	ft::map<int, char>			ft_char_map(ft_list_char.begin(), ft_list_char.end());;
	std::map<int, std::string>	std_string_map(std_list_string.begin(), std_list_string.end());;
	ft::map<int, std::string>	ft_string_map(ft_list_string.begin(), ft_list_string.end());;

	compareContent(std_char_map, ft_char_map);
	compareContent(std_string_map, ft_string_map);
}

TEST(MapMemberFunctions, CopyConstructor)
{
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
}

TEST(MapMemberFunctions, EqualOperator)
{
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

IGNORE_TEST(MapReverseIterators, Arithmetics)
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

IGNORE_TEST(MapReverseIterators, Base)
{
	std_char_map_it = std_char_map.rbegin();
	std_char_map_ite = std_char_map.rend();
	ft_char_map_it = ft_char_map.rbegin();
	ft_char_map_ite = ft_char_map.rend();
	std_string_map_it = std_string_map.rbegin();
	std_string_map_ite = std_string_map.rend();
	ft_string_map_it = ft_string_map.rbegin();
	ft_string_map_ite = ft_string_map.rend();

	checkIteratorsEqual(std_char_map_it.base(), ft_char_map_it.base());
	checkIteratorsEqual(std_string_map_it.base(), ft_string_map_it.base());

	std_char_map_it++;
	ft_char_map_it++;
	std_string_map_it++;
	ft_string_map_it++;

	checkIteratorsEqual(std_char_map_it.base(), ft_char_map_it.base());
	checkIteratorsEqual(std_string_map_it.base(), ft_string_map_it.base());
	checkIteratorsEqual(std_char_map_ite.base(), ft_char_map_ite.base());
	checkIteratorsEqual(std_string_map_ite.base(), ft_string_map_ite.base());
}
