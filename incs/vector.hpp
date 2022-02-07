/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pohl <pohl@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 09:40:54 by pohl              #+#    #+#             */
/*   Updated: 2022/02/07 15:08:18 by pohl             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <iostream>

/* # include "vector_iterator.hpp" */
/* # include "reverse_iterator.hpp" */
/* # include "distanceBetweenIterators.hpp" */
/* # include "is_integral.hpp" */
# include "iterators/vector_iterator.hpp"
# include "iterators/reverse_iterator.hpp"
# include "utils/distanceBetweenIterators.hpp"
# include "utils/is_integral.hpp"
# include <cstring>

namespace ft
{

template< typename T, typename Allocator = std::allocator<T> >
class vector
{

public:

	typedef T												value_type;
	typedef Allocator										allocator_type;
	typedef std::size_t										size_type;
	typedef std::ptrdiff_t									difference_type;
	typedef typename Allocator::reference					reference;
	typedef typename Allocator::const_reference				const_reference;
	typedef typename Allocator::pointer						pointer;
	typedef typename Allocator::const_pointer				const_pointer;
	typedef vector_iterator<T>								iterator;
	typedef vector_iterator<T, true>						const_iterator;
	typedef ft::reverse_iterator<vector_iterator<T> >		reverse_iterator;
	typedef ft::reverse_iterator<vector_iterator<T, true> >	const_reverse_iterator;

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
	template< typename InputIt >
	vector( InputIt first, InputIt last, const Allocator& alloc = Allocator() ):
		_data(NULL), _size(0), _capacity(0), _allocator(alloc)
	{
		assignDispatch(first, last);
	}
	vector( const vector& other ):
		_data(NULL), _size(0), _capacity(0), _allocator(other._allocator)
	{
		*this = other;
	}
	~vector( void )
	{
		this->clear();
		_allocator.deallocate(this->_data, this->_capacity);
	}

	vector&		operator=( const vector& other )
	{
		this->_allocator = other._allocator;
		this->assign(other.begin(), other.end());
		return *this;
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
	reverse_iterator		rbegin( void )
	{
		return reverse_iterator(this->end());
	}
	const_reverse_iterator	rbegin( void ) const
	{
		return const_reverse_iterator(this->end());
	}
	reverse_iterator		rend( void )
	{
		return reverse_iterator(this->begin());
	}
	const_reverse_iterator	rend( void ) const
	{
		return const_reverse_iterator(this->begin());
	}

	reference	operator[]( const size_type index )
	{
		return this->_data[index];
	}
	reference	at( const size_type index )
	{
		if (index >= this->_size)
			throw std::out_of_range("index given is out of range.");
		return this->_data[index];
	}
	const reference	at( const size_type index ) const
	{
		if (index >= this->_size)
			throw std::out_of_range("index given is out of range.");
		return this->_data[index];
	}

	reference		front( void ) { return this->_data[0]; }
	const_reference	front( void ) const { return this->_data[0]; }
	reference		back( void ) { return this->_data[this->_size - 1]; }
	const_reference	back( void ) const { return this->_data[this->_size - 1]; }

	iterator	insert( iterator position, const value_type& value )
	{
		size_type	insertionIndex = position - this->begin();

		this->insert(position, 1, value);
		return (iterator(&this->_data[insertionIndex]));
	}
	void	insert( iterator position, size_type count,
			const value_type& value )
	{
		size_type	startIndex = position - this->begin();

		this->createHole(startIndex, count);
		this->fillRange(startIndex, count, value);
		this->_size += count;
	}
	template< typename InputIt >
	void	insert( iterator position, InputIt first, InputIt last )
	{
		this->insertDispatch(position, first, last);
	}
	void	push_back( const T& value )
	{
		this->insert(this->end(), 1, value);
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
	template< typename InputIt >
	void	assign( InputIt first, InputIt last )
	{
		assignDispatch(first, last);
	}
	iterator	erase( iterator position )
	{
		if (position + 1 == this->end())
		{
			this->pop_back();
			return position;
		}
		this->_allocator.destroy(position.getPointer());
		this->_size--;
		this->copyObjects(position.getPointer(), position.getPointer() + 1,
				this->end() - position);
		return position;
	}
	iterator	erase( iterator first, iterator last )
	{
		value_type *dst = first.getPointer();
		size_type	amountToMove = this->end() - last;

		if (last == this->end())
		{
			while (first != this->end())
				this->pop_back();
			return this->end();
		}
		this->_size -= last - first;
		while (first != last)
		{
			this->_allocator.destroy(first.getPointer());
			first++;
		}
		this->copyObjects(dst, last.getPointer(), amountToMove);
		return iterator(dst);
	}
	void	resize( size_type new_size, const value_type& value = value_type() )
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
			if (_size)
				copyObjects(new_data, this->_data, this->_size);
			if (_capacity)
				_allocator.deallocate(_data, _capacity);
			this->_data = new_data;
			this->_capacity = allocated_size;
		}
	}
	void	swap( vector& other )
	{
		value_type		*tmp_data = this->_data;
		size_type		tmp_size = this->_size;
		size_type		tmp_capacity = this->_capacity;
		allocator_type	tmp_allocator = this->_allocator;

		this->_data = other._data;
		this->_size = other._size;
		this->_capacity = other._capacity;
		this->_allocator = other._allocator;
		other._data			= tmp_data;
		other._size			= tmp_size;
		other._capacity		= tmp_capacity;
		other._allocator	= tmp_allocator;
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

	void	createHole( size_type startIndex,
			size_type size )
	{
		if (this->_size + size > this->_capacity)
			this->reserve(this->_size + size);
		if (this->_data && this->_size > startIndex)
		{
			copyObjects(this->_data + startIndex + size,
					this->_data + startIndex, this->_size - startIndex);
		}
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
	template<typename InputIt>
	void	insertDispatch( iterator position, InputIt first, InputIt last,
			char(*)[ft::is_integral<InputIt>::value == true] = 0 )
	{
		size_type	startIndex = position - this->begin();

		this->createHole(startIndex, first);
		this->fillRange(startIndex, first, last);
		this->_size += first;
	}
	template<typename InputIt>
	void	insertDispatch( iterator position, InputIt first, InputIt last,
			char(*)[ft::is_integral<InputIt>::value == false] = 0 )
	{
		const size_type rangeSize = ft::distanceBetweenIterators(first, last);
		const size_type startIndex = position - this->begin();

		this->createHole(startIndex, rangeSize);
		for (size_type i = startIndex; first != last; i++, first++)
			_allocator.construct(&this->_data[i], *first);
		this->_size += rangeSize;
	}
	template<typename InputIt>
	void	assignDispatch( InputIt first, InputIt last,
			char(*)[ft::is_integral<InputIt>::value == true] = 0 )
	{
		this->clear();
		this->resize(first, last);
	}
	template<typename InputIt>
	void	assignDispatch( InputIt first, InputIt last,
			char(*)[ft::is_integral<InputIt>::value == false] = 0 )
	{
		const size_type newSize = ft::distanceBetweenIterators(first, last);

		this->clear();
		if (newSize > capacity())
			this->reserve(newSize);
		for (size_type i = 0; first != last; i++, first++)
			_allocator.construct(&this->_data[i], *first);
		this->_size = newSize;
	}
	value_type	*copyObjects( value_type *dst, value_type *src,
			size_type size)
	{
		if (dst == src)
			return dst;
		if (dst < src)
		{
			for (size_type i = 0; i < size; i++)
			{
				_allocator.construct(dst + i, src[i]);
				_allocator.destroy(&(src[i]));
			}
		}
		else
		{
			for (size_type i = size; i > 0;)
			{
				i--;
				_allocator.construct(dst + i, src[i]);
				_allocator.destroy(src + i);
			}
		}
		return dst;
	}

private:

	value_type		*_data;
	size_type		_size;
	size_type		_capacity;
	allocator_type	_allocator;

};

}

#endif
