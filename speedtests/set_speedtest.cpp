/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_speedtest.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pohl <pohl@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 18:02:27 by pohl              #+#    #+#             */
/*   Updated: 2022/02/17 11:42:31 by pohl             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

#ifndef IS_STD
# define IS_STD 0
#endif

#if IS_STD == 1
	#include <set>
	namespace ft = std;
#else
	#include "set.hpp"
#endif

int main( void )
{
	ft::set<int>				testedMap;
	ft::set<int>::iterator	it, ite;

	size_t				numberOfPushes = 5000000;

	for (size_t i = 0; i < numberOfPushes; i++)
		testedMap.insert(i);
	it = testedMap.begin();
	ite = testedMap.end();
	while (it != ite)
	{
		it++;
	}
	testedMap.clear();
	return 0;
}
