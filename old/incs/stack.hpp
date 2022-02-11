/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pohl <pohl@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 18:05:25 by pohl              #+#    #+#             */
/*   Updated: 2022/01/27 11:55:59 by pohl             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
# define STACK_HPP

# include <deque>

namespace	ft
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

	// Default constructor
	explicit stack<T, Container>( const Container &container = Container() ):
		c(container)
	{
		return;
	}
	// Copy constructor
 	stack<T, Container>( const stack<T>& other ) { *this = other; }
	// Destructor
	~stack<T, Container>( void ) { }

	// Operator overload
	stack		&operator=( const stack<T> &other )
	{
		if (this != &other)
			this->c = other.c;
		return *this;
	}

	/* accessors */
	reference		top( void ) { return c.back(); }
	const_reference	top( void ) const { return c.back(); }

	/* capacity */
	bool		empty( void ) const { return c.empty(); }
	size_type	size( void ) const { return c.size(); }

	/* modifiers */
	void	push( const value_type &value )
	{
		c.push_back(value);
	}
	void	pop( void )
	{
		c.pop_back();
	}

	friend bool	operator==(const stack &lhs, const stack &rhs)
	{
		return lhs.c == rhs.c;
	}
	friend bool	operator!=(const stack &lhs, const stack &rhs)
	{
		return !(lhs == rhs);
	}
	friend bool	operator<(const stack &lhs, const stack &rhs)
	{
		return lhs.c < rhs.c;
	}
	friend bool	operator>(const stack &lhs, const stack &rhs)
	{
		return rhs < lhs;
	}
	friend bool	operator<=(const stack &lhs, const stack &rhs)
	{
		return !(lhs > rhs);
	}
	friend bool	operator>=(const stack &lhs, const stack &rhs)
	{
		return !(lhs < rhs);
	}

};

}

#endif
