/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pohl <pohl@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 13:39:21 by pohl              #+#    #+#             */
/*   Updated: 2022/01/26 17:18:23 by pohl             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <memory>
# include <cstddef>
# include <stdexcept>
# include <iostream>
# include "enable_if.hpp"
# include "is_integral.hpp"
# include "vector_iterator.hpp"
# include "vector_reverse_iterator.hpp"

namespace	ft
{

template<typename T, typename Allocator = std::allocator<T> >
class	vector
{

public:

	typedef T										value_type;
	typedef Allocator								allocator_type;
	typedef std::size_t								size_type;
	typedef std::ptrdiff_t							difference_type;
	typedef typename Allocator::reference			reference;
	typedef typename Allocator::const_reference		const_reference;
	typedef typename Allocator::pointer				pointer;
	typedef typename Allocator::const_pointer		const_pointer;
	typedef vector_iterator<T>						iterator;
	typedef vector_iterator<T, true>				const_iterator;
	typedef vector_reverse_iterator<T>				reverse_iterator;
	typedef vector_reverse_iterator<T, true>		const_reverse_iterator;

public:

	// Default constructor
	explicit vector<T, Allocator>( const Allocator &alloc = Allocator() ):
		_data(NULL), _size(0), _capacity(0), _allocator(alloc)
	{
		return;
	}
	// Copy constructor
 	vector<T, Allocator>( const vector<T>& other ):
		_data(NULL), _size(0), _capacity(0), _allocator(other._allocator)
	{ *this = other; }
	// Fill constructor
	explicit vector<T, Allocator>( size_type count,
			const T& value = T(),
			const Allocator& alloc = Allocator() ):
		_data(NULL), _size(0), _capacity(0), _allocator(alloc)
	{
		assign(count, value);
		return;
	}
	// Range constructor with iterator
	template<typename InputIt>
	vector<T, Allocator>( InputIt first, InputIt last,
			const Allocator& alloc = Allocator() ):
		_data(NULL), _size(0), _capacity(0), _allocator(alloc)
	{
		assign(first, last);
		return;
	}
	// Destructor
	~vector<T, Allocator>( void )
	{
		this->clear();
		_allocator.deallocate(_data, _capacity);
	}

	// Operator overload
	vector		&operator=( const vector<T> &other )
	{
		if (this == &other)
			return *this;
		assign(other.begin(), other.end());
		return *this;
	}

	void			assign( size_type count, const T &value )
	{
		this->clear();
		this->resize(count);
		for (iterator it = begin(); it != end(); it++)
			*it = value;
	}
	template<typename InputIt>
	typename ft::enable_if<!ft::is_integral<InputIt>::value >::type	assign(
			InputIt first, InputIt last )
	{
		size_type	count = this->it_range_len(first, last);

		this->clear();
		this->resize(count);
		for (iterator it = begin(); first != last; it++)
		{
			*it = *first;
			first++;
		}
	}
	allocator_type	get_allocator() const { return this->_allocator; }

	/* iterator operations */
	iterator				begin( void )
	{
		return iterator(&_data[0]);
	}
	const_iterator			begin( void ) const
	{
		return const_iterator(&_data[0]);
	}
	iterator				end( void )
	{
		return iterator(&_data[this->_size]);
	}
	const_iterator			end( void ) const
	{
		return const_iterator(&_data[this->_size]);
	}
	reverse_iterator		rbegin( void )
	{
		return reverse_iterator(_data + this->_size - 1);
	}
	const_reverse_iterator	rbegin( void ) const
	{
		return const_reverse_iterator(_data + this->_size - 1);
	}
	reverse_iterator		rend( void )
	{
		return reverse_iterator(this->_data - 1);
	}
	const_reverse_iterator	rend( void ) const
	{
		return const_reverse_iterator(this->_data - 1);
	}

	/* capacity */
	size_type			size( void ) const { return _size; }
	size_type			max_size( void ) const { return _allocator.max_size(); }
	void				resize( size_type count, T value = T())
	{
		if (count > size())
			insert(end(), count - size(), value);
		else if (count < size())
			erase(begin() + count, end());
	}
	size_type			capacity( void ) const { return _capacity; }
	bool				empty( void ) const { return _size == 0; }
	void				reserve( size_type new_cap )
	{
		value_type	*new_data;
		size_type	allocated_size;

		if (new_cap > max_size())
			throw std::length_error("The reserve you asked is too high");
		if (_capacity < new_cap)
		{
			allocated_size = closest_power_of_two(new_cap);
			new_data = _allocator.allocate(allocated_size);
			for (size_type i = 0; i < size(); i++)
				_allocator.construct(&new_data[i], _data[i]);
			if (_capacity)
				_allocator.deallocate(_data, _capacity);
			_data = new_data;
			_capacity = allocated_size;
		}
	}

	/* accessors */
	reference		operator[]( size_type pos )
	{
		return this->_data[pos];
	}
	const_reference	operator[]( size_type pos ) const
	{
		return this->_data[pos];
	}
	reference			at( size_type pos ) {
		if (pos < 0 || pos >= this->_size)
			throw std::out_of_range("Index out of range");
		return this->_data[pos];
	}
	const_reference		at( size_type pos ) const {
		if (pos < 0 || pos >= this->_size)
			throw std::out_of_range("Index out of range");
		return this->_data[pos];
	}
	reference			front( void ) { return _data[0]; }
	const_reference		front( void ) const { return _data[0]; }
	reference			back( void ) { return _data[this->_size - 1]; }
	const_reference		back( void ) const { return _data[this->_size - 1]; }
	value_type			*data( void ) { return _data; }
	const value_type	*data( void ) const { return _data; }

	/* modifiers */
	void		push_back( const T &value ) { insert(end(), value); }
	void		pop_back( void ) { erase(end() - 1); }
	iterator	insert( iterator pos, const T &value )
	{
		size_type	index = pos - begin();
		insert(pos, 1, value);
		return iterator(&_data[index]);
	}
	void		insert( iterator pos, size_type count, const T &value )
	{
		pos = createHole(pos, count);
		for (size_type i = 0; i < count; i++)
			_allocator.construct(&(*pos++), value);
		_size += count;
	}
	template<typename InputIt>
	typename ft::enable_if<!ft::is_integral<InputIt>::value >::type	insert(
		iterator pos, InputIt first, InputIt last )
	{
		size_type	input_size = it_range_len(first, last);

		pos = createHole(pos, input_size);
		while (first != last)
		{
			*pos = *first;
			pos++;
			first++;
		}
		_size += input_size;
	}
	iterator	erase( iterator pos ) { return erase(pos, pos + 1); }
	iterator	erase( iterator first, iterator last )
	{
		size_type	count = last - first;
		iterator	result(first);
		iterator	tmp;

		if (first == last || first == end())
			return first;
		tmp = first + count;
		for (; first != end(); first++, tmp++)
		{
			_allocator.destroy(&(*first));
			if (tmp < end())
				_allocator.construct(&(*first), *tmp);
		}
		_size -= count;
		return result;
	}
	void		swap( vector &other )
	{
		swap(this->_data, other._data);
		swap(this->_allocator, other._allocator);
		swap(this->_size, other._size);
		swap(this->_capacity, other._capacity);
	}
	void		clear( void )
	{
		while (_size)
			this->pop_back();
	}

	friend bool	operator==(const vector &lhs, const vector &rhs)
	{
		const_iterator	lhs_it = lhs.begin();
		const_iterator	lhs_ite = lhs.end();
		const_iterator	rhs_it = rhs.begin();
		const_iterator	rhs_ite = rhs.end();

		while (lhs_it != lhs_ite && rhs_it != rhs_ite && *lhs_it == *rhs_it)
		{
			lhs_it++;
			rhs_it++;
		}
		if (lhs_it == lhs_ite && rhs_it == rhs_ite)
			return true;
		return false;
	}
	friend bool	operator!=(const vector &lhs, const vector &rhs)
	{
		return !(lhs == rhs);
	}
	friend bool	operator<(const vector &lhs, const vector &rhs)
	{
		const_iterator	lhs_it = lhs.begin();
		const_iterator	lhs_ite = lhs.end();
		const_iterator	rhs_it = rhs.begin();
		const_iterator	rhs_ite = rhs.end();

		while (lhs_it != lhs_ite && rhs_it != rhs_ite && *lhs_it == *rhs_it)
		{
			lhs_it++;
			rhs_it++;
		}
		if (lhs_it == lhs_ite)
		{
			if (rhs_it != rhs_ite)
				return true;
			return false;
		}
		if (rhs_it == rhs_ite)
			return false;
		return *lhs_it < *rhs_it;
	}
	friend bool	operator>(const vector &lhs, const vector &rhs)
	{
		return rhs < lhs;
	}
	friend bool	operator<=(const vector &lhs, const vector &rhs)
	{
		return !(lhs > rhs);
	}
	friend bool	operator>=(const vector &lhs, const vector &rhs)
	{
		return !(lhs < rhs);
	}

private:

	T				*_data;
	size_type		_size;
	size_type		_capacity;
	allocator_type	_allocator;

	template<typename InputIt>
	size_type	it_range_len( InputIt first, InputIt last ) const
	{
		size_type	len = 0;

		while (first++ != last)
			len++;
		return (len);
	}
	size_type	closest_power_of_two( size_type num ) const
	{
		if (num == 0)
			return (num);
		num--;
		num |= num >> 1;
		num |= num >> 2;
		num |= num >> 4;
		num |= num >> 8;
		num |= num >> 16;
		num++;
		return (num);
	}
	iterator	createHole( iterator startPos, size_type size )
	{
		iterator	newPos;
		size_type	diff = startPos - begin();

		if (_size + size > _capacity)
			reserve(_capacity + size);
		newPos = begin() + diff;
		if (_size && newPos != end())
		{
			for (iterator it(end() - 1); it != newPos - 1; it--)
				*(it + size) = *it;
		}
		return newPos;
	}
	template<typename Var>
	void	swap( Var &a, Var &b )
	{
		Var tmp = a;

		a = b;
		b = tmp;
	}
};

}

#endif
