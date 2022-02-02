/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_iterator.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pohl <pohl@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 11:30:59 by pohl              #+#    #+#             */
/*   Updated: 2022/02/02 13:00:55 by pohl             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_ITERATOR_HPP
# define VECTOR_ITERATOR_HPP

# include <iterator>
# include "utils/select_const_type.hpp"

namespace ft
{

template <typename T, bool IsConst = false>
class vector_iterator
{

public:

	typedef std::random_access_iterator_tag	iterator_category;
	typedef std::ptrdiff_t					difference_type;
	typedef std::size_t						size_type;

	typedef T															value_type;
	typedef typename ft::select_const_type<IsConst, T*, const T*>::type	pointer;
	typedef typename ft::select_const_type<IsConst, T&, const T&>::type	reference;

	vector_iterator( pointer pointer = 0 ) : _pointer(pointer) { return; }
	vector_iterator( const vector_iterator<T> &other ):
		_pointer(other.getPointer())
	{
		return;
	}
	~vector_iterator( void ) { return; }

	vector_iterator &operator=( const vector_iterator &other )
	{
		if (this != &other)
			this->_pointer = other._pointer;
		return *this;
	}

	pointer			getPointer( void ) const { return this->_pointer; }

	friend bool	operator==( const vector_iterator& lhs,
			const vector_iterator& rhs )
	{
		return lhs._pointer == rhs._pointer;
	}
	friend bool	operator!=( const vector_iterator& lhs,
			const vector_iterator& rhs )
	{
		return lhs._pointer != rhs._pointer;
	}

	friend difference_type		operator-( vector_iterator lhs,
			vector_iterator rhs )
	{
		return lhs._pointer - rhs._pointer;
	}  

private:

	pointer	_pointer;

};

}

#endif
