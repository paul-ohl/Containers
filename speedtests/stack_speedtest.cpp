/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_speedtest.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pohl <pohl@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 17:35:40 by pohl              #+#    #+#             */
/*   Updated: 2022/02/02 09:38:03 by pohl             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* #include <cstdio> */
/* #include <iostream> */
/* #include <list> */
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

int		getNumberOfPushes(int argc, char **argv)
{
	int numberOfPushes = 1500000;

	if (argc == 2)
		numberOfPushes = std::atoi(argv[1]);
	else if (argc > 2)
		throw std::invalid_argument("Too many arguments");
	return numberOfPushes;
}

int	main( int argc, char **argv )
{
	(void)argc;(void)argv;
	ft::stack<int>	testedStack;
	int				numberOfPushes = getNumberOfPushes(argc, argv);

	for (int i = 0; i < numberOfPushes; i++)
		testedStack.push(i);
	for (int i = 0; i < numberOfPushes; i++)
		testedStack.pop();
	return 0;
}
