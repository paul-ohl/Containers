/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distanceBetweenIterators.hpp                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pohl <pohl@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 16:48:49 by pohl              #+#    #+#             */
/*   Updated: 2022/02/07 13:57:16 by pohl             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DISTANCEBETWEENITERATORS_HPP
# define DISTANCEBETWEENITERATORS_HPP

# include "iterator_traits.hpp"

namespace ft
{

	template<typename InputIt>
	typename ft::iterator_traits<InputIt>::difference_type
		distanceBetweenIterators( InputIt first, InputIt last )
	{
		typename ft::iterator_traits<InputIt>::difference_type n = 0;
		while (first != last)
		{
			++first;
			++n;
		}
		return n;
	}

}

#endif
