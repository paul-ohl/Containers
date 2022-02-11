/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enable_if.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pohl <pohl@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 15:47:50 by pohl              #+#    #+#             */
/*   Updated: 2021/11/29 15:49:42 by pohl             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

namespace ft
{

template<bool, typename T = void>
struct enable_if
{};

template<typename T>
struct enable_if<true, T>
{
	typedef T type;
};

}
