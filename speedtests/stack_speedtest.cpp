/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_speedtest.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pohl <pohl@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 17:35:40 by pohl              #+#    #+#             */
/*   Updated: 2022/02/07 15:40:03 by pohl             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdexcept>
#include <cstdlib>

#ifndef IS_STD
# define IS_STD 0
#endif

#if IS_STD == 1
	#include <stack>
	namespace ft = std;
#else
	#include "../incs/stack.hpp"
#endif

int	main( void )
{
	ft::stack<int>	testedStack;
	int				numberOfPushes = 100000000;

	for (int i = 0; i < numberOfPushes; i++)
		testedStack.push(i);
	for (int i = 0; i < numberOfPushes; i++)
		testedStack.pop();
	return 0;
}
