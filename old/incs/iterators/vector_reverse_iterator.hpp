/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_reverse_iterator.hpp                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulohl <pohl@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 17:39:43 by paulohl           #+#    #+#             */
/*   Updated: 2021/12/09 17:27:23 by paulohl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_REVERSE_ITERATOR_HPP
# define VECTOR_REVERSE_ITERATOR_HPP

# include <iterator>
# include "select_const_type.hpp"
# include "vector_iterator.hpp"

namespace ft
{

template <typename T, bool IsConst = false>
class vector_reverse_iterator
{

public:

	typedef std::random_access_iterator_tag	iterator_category;
	typedef std::ptrdiff_t					difference_type;
	typedef std::size_t						size_type;

	typedef T														value_type;
	typedef typename select_const_type<IsConst, T*, const T*>::type	pointer;
	typedef typename select_const_type<IsConst, T&, const T&>::type	reference;

	vector_reverse_iterator( value_type *ptr = 0 ) : _ptr(ptr) { return; }
	vector_reverse_iterator( const vector_reverse_iterator<T> &other ): _ptr(other.getPtr()) { return; }
	vector_reverse_iterator( const vector_iterator<T, false> &other ): _ptr(other.getPtr() - 1) { return; }
	vector_reverse_iterator( const vector_iterator<T, true> &other ): _ptr(other.getPtr() - 1) { return; }
	~vector_reverse_iterator( void ) { return; }

	vector_reverse_iterator &operator=( const vector_reverse_iterator &other )
	{
		if (this != &other)
			this->_ptr = other._ptr;
		return *this;
	}

	value_type	*getPtr( void ) const { return _ptr; }
	vector_iterator<T, IsConst>	base( void ) const { return vector_iterator<T, IsConst>(_ptr + 1); }

	reference			operator*() const { return *this->_ptr; }
	pointer				operator->() const { return this->_ptr; }

	vector_reverse_iterator&	operator++() { this->_ptr--; return *this; }  
	vector_reverse_iterator&	operator--() { this->_ptr++; return *this; }  
	vector_reverse_iterator		operator++(int) {
		vector_reverse_iterator tmp(*this);
		++(*this);
		return tmp;
	}
	vector_reverse_iterator		operator--(int) {
		vector_reverse_iterator tmp(*this);
		--(*this);
		return tmp;
	}

	friend bool	operator==( const vector_reverse_iterator& lhs, const vector_reverse_iterator& rhs )
	{
		return lhs._ptr == rhs._ptr;
	}
	friend bool	operator!=( const vector_reverse_iterator& lhs, const vector_reverse_iterator& rhs )
	{
		return lhs._ptr != rhs._ptr;
	}
	friend bool	operator<( const vector_reverse_iterator& lhs, const vector_reverse_iterator& rhs )
	{
		return lhs._ptr > rhs._ptr;
	}
	friend bool	operator<=( const vector_reverse_iterator& lhs, const vector_reverse_iterator& rhs )
	{
		return lhs._ptr >= rhs._ptr;
	}
	friend bool	operator>( const vector_reverse_iterator& lhs, const vector_reverse_iterator& rhs )
	{
		return lhs._ptr < rhs._ptr;
	}
	friend bool	operator>=( const vector_reverse_iterator& lhs, const vector_reverse_iterator& rhs )
	{
		return lhs._ptr <= rhs._ptr;
	}

	vector_reverse_iterator&	operator+=( int n ) { this->_ptr -= n; return *this; }
	vector_reverse_iterator&	operator-=( int n ) { this->_ptr += n; return *this; }
	vector_reverse_iterator		operator+( int n ) const { return vector_reverse_iterator(this->_ptr - n); }  
	vector_reverse_iterator		operator-( int n ) const { return vector_reverse_iterator(this->_ptr + n); }  
	friend difference_type		operator-( vector_reverse_iterator lhs, vector_reverse_iterator rhs )
	{
		return rhs._ptr - lhs._ptr;
	}  

	reference	operator[]( int n ) const { return *(*this + n); }

	friend vector_reverse_iterator operator+( int lhs, const vector_reverse_iterator& rhs )
	{
		return vector_reverse_iterator(rhs._ptr - lhs);
	}
	friend vector_reverse_iterator operator-( int lhs, const vector_reverse_iterator& rhs )
	{
		return vector_reverse_iterator(rhs._ptr + lhs);
	}

private:

	value_type *_ptr;

};

}

#endif
