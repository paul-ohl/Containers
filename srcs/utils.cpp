/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pohl <pohl@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 13:59:39 by pohl              #+#    #+#             */
/*   Updated: 2022/01/31 14:08:44 by pohl             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sstream>

std::string	getTimeDiffAsString(double std_time, double ft_time)
{
	std::ostringstream	sstream;

	sstream << "ft_time (" << ft_time << "s) takes " << ft_time / std_time
		<< " longer than std_time (" << std_time << "s)" << std::endl;
	std::string resultString = sstream.str();
	return resultString;
}
