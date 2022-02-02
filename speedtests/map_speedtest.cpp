/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_speedtest.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pohl <pohl@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 18:02:27 by pohl              #+#    #+#             */
/*   Updated: 2022/01/31 18:04:15 by pohl             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

#ifndef IS_STD
# define IS_STD 0
#endif

#if IS_STD == 1
	#include <stack>
	namespace ft = std;
#else
	#include "stack.hpp"
#endif

int main( void )
{
	std::cout << "HI " << IS_STD << std::endl;
}
