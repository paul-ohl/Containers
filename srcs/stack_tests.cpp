/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testest.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pohl <pohl@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 11:01:45 by pohl              #+#    #+#             */
/*   Updated: 2022/01/31 11:01:59 by pohl             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CppUTest/TestHarness.h"

TEST_GROUP(FirstTestGroup)
{
};

TEST(FirstTestGroup, FirstTest)
{
   FAIL("Fail me!");
}
