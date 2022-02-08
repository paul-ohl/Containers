/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pair.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pohl <pohl@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 06:13:43 by pohl              #+#    #+#             */
/*   Updated: 2022/01/17 06:47:11 by pohl             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PAIR_HPP
# define PAIR_HPP

namespace ft
{

template<typename _T1, typename _T2>
struct pair
{

	typedef _T1	first_type;
	typedef _T2	second_type;

	// Default constructor
	pair( void ) : first(), second() {}

	// Copy constructor
	template<typename _U1, typename _U2>
	pair( const pair<_U1, _U2>& _p ) : first(_p.first), second(_p.second) { }

	// Standard constructor
	pair( const _T1& _a, const _T2& _b ) : first(_a), second(_b) { }

	_T1 first;
	_T2 second;

};

template<typename _T1, typename _T2>
pair<_T1, _T2> make_pair(_T1 _x, _T2 _y)
{
	return pair<_T1, _T2>(_x, _y);
}

}

#endif
