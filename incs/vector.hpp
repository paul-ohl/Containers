/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pohl <pohl@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 09:40:54 by pohl              #+#    #+#             */
/*   Updated: 2022/02/02 14:19:10 by pohl             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

/* # include <iostream> */

# include "iterators/vector_iterator.hpp"
# include <cstring>

namespace ft
{

template< typename T, typename Allocator = std::allocator<T> >
class vector
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

public:

	explicit vector( const Allocator &alloc = Allocator() ):
		_data(NULL), _size(0), _capacity(0), _allocator(alloc)
	{
		return;
	}
	explicit vector( size_type count, const T& value = T(),
			const Allocator& alloc = Allocator() ):
		_data(NULL), _size(0), _capacity(0), _allocator(alloc)
	{
		resize(count, value);
	}
	~vector( void )
	{
		this->clear();
		_allocator.deallocate(this->_data, this->_capacity);
	}

	size_type				size( void ) const { return this->_size; }
	size_type				max_size( void ) const
	{
		return _allocator.max_size();
	}
	size_type				capacity( void ) const { return _capacity; }
	bool					empty( void ) const { return this->_size == 0; }
	allocator_type			&get_allocator() { return this->_allocator; }
	const allocator_type	&get_allocator() const { return this->_allocator; }

	iterator		begin( void ) { return iterator(this->_data); }
	const_iterator	begin( void ) const
	{
		return const_iterator(this->_data);
	}
	iterator		end( void ) { return iterator(&this->_data[this->_size]); }
	const_iterator	end( void ) const
	{
		return const_iterator(&this->_data[this->_size]);
	}

	reference		front( void ) { return this->_data[0]; }
	const_reference	front( void ) const { return this->_data[0]; }
	reference		back( void ) { return this->_data[this->_size - 1]; }
	const_reference	back( void ) const { return this->_data[this->_size - 1]; }

	void	insert( iterator position, size_type count,
			const value_type& value )
	{
		size_type	startIndex = position - this->begin();

		this->createHole(position, count);
		this->fillRange(startIndex, count, value);
		this->_size += count;
	}
	void	pop_back( void )
	{
		this->_allocator.destroy(&(this->_data[this->_size - 1]));
		this->_size--;
	}
	void	clear( void )
	{
		while (this->size())
			this->pop_back();
	}
	void	assign( size_type new_size, const value_type& value )
	{
		this->clear();
		this->resize(new_size, value);
	}
	void	resize( size_type new_size, const value_type& value )
	{
		if (this->_size < new_size)
			insert(end(), new_size - size(), value);
		else
		{
			while (this->_size > new_size)
				pop_back();
		}
	}
	void	reserve( size_type size )
	{
		value_type	*new_data;
		size_type	allocated_size;

		if (size > max_size())
			throw std::length_error("The reserve you asked is too high");
		if (this->_capacity < size)
		{
			allocated_size = closest_power_of_two(size);
			new_data = _allocator.allocate(allocated_size);
			memmove(new_data, this->_data, this->_size);
			if (_capacity)
				_allocator.deallocate(_data, _capacity);
			this->_data = new_data;
			this->_capacity = allocated_size;
		}
	}

private:

	void	createHole( iterator position, size_type size )
	{
		if (this->_size + size > this->_capacity)
			this->reserve(this->_size + size);
		if (position.getPointer() && position != this->end())
			memmove(position.getPointer() + size, position.getPointer(), size);
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
	void	fillRange( size_type startIndex, size_type count, const T& value )
	{
		for (size_type i = 0; i < count; i++)
			_allocator.construct(&this->_data[startIndex + i], value);
	}

private:

	T				*_data;
	size_type		_size;
	size_type		_capacity;
	allocator_type	_allocator;

};

}

#endif
