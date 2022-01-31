/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pohl <pohl@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 09:53:12 by pohl              #+#    #+#             */
/*   Updated: 2022/01/31 10:54:09 by pohl             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "CppUTest/CommandLineTestRunner.h"

int	main( int ac, char **av )
{
	return CommandLineTestRunner::RunAllTests(ac, av);
}
