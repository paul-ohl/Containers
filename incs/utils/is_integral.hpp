/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_integral.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulohl <pohl@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 17:36:43 by paulohl           #+#    #+#             */
/*   Updated: 2022/02/02 17:09:56 by pohl             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IS_INTEGRAL_HPP
# define IS_INTEGRAL_HPP

# include <stdint.h>

namespace ft {

template<typename T>
struct	is_integral
{
	static const bool value = false;
};

template<>
struct	is_integral<bool>
{
	static const bool value = true;
};

template<>
struct	is_integral<char>
{
	static const bool value = true;
};

template<>
struct	is_integral<wchar_t>
{
	static const bool value = true;
};

template<>
struct	is_integral<short>
{
	static const bool value = true;
};

template<>
struct	is_integral<int>
{
	static const bool value = true;
};

template<>
struct	is_integral<long>
{
	static const bool value = true;
};

template<>
struct	is_integral<long long>
{
	static const bool value = true;
};

}

#endif
