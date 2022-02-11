/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pohl <pohl@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 11:21:08 by pohl              #+#    #+#             */
/*   Updated: 2022/01/28 17:58:41 by pohl             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "testers.hpp"

int	main( void )
{
	// Need to test every feature, against the original function,
	// then test the speed with massive inputs

	// tests for stack
	stackRegularTests();
	// tests for map
	mapRegularTests();
	// tests for vector
	vectorRegularTests();

	// Speed tests
	stackSpeedTests();
	mapSpeedTests();
	vectorSpeedTests();
}
