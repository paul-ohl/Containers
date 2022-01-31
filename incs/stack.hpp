/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pohl <pohl@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 11:18:28 by pohl              #+#    #+#             */
/*   Updated: 2022/01/31 12:11:02 by pohl             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
# define STACK_HPP

# include <deque>

namespace ft
{

template<typename T, typename Container = std::deque<T> >
class	stack
{

public:

	typedef Container							container_type;
	typedef typename Container::value_type		value_type;
	typedef typename Container::size_type		size_type;
	typedef typename Container::reference		reference;
	typedef typename Container::const_reference	const_reference;

protected:

	Container	c;

public:

	explicit stack<T, Container>( const Container &container = Container() ):
		c(container)
	{
		return;
	}
 	stack<T, Container>( const stack<T>& other ) { *this = other; }
	~stack<T, Container>( void ) { }

	stack		&operator=( const stack<T> &other )
	{
		if (this != &other)
			this->c = other.c;
		return *this;
	}

};

}

#endif
