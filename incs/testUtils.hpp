/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testUtils.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pohl <pohl@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 14:09:57 by pohl              #+#    #+#             */
/*   Updated: 2022/01/31 14:34:10 by pohl             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TESTUTILS_HPP
# define TESTUTILS_HPP

const int MAX_TIME_DIFFERENCE = 50;

std::string	getTimeDiffAsString(double std_time, double ft_time);

template<typename U, typename V>
void	checkAllOperators(U std_container1, U std_container2, V ft_container1, V ft_container2);

#endif
