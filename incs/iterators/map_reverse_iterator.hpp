/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_reverse_iterator.hpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulohl <pohl@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 17:39:43 by paulohl           #+#    #+#             */
/*   Updated: 2022/02/15 18:19:15 by pohl             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_REVERSE_ITERATOR_HPP
# define MAP_REVERSE_ITERATOR_HPP

# include "iterators/map_iterator.hpp"

namespace ft
{

template < typename Key, typename T, typename Compare = std::less<const Key>,
		 bool IsConst = false >
class map_reverse_iterator
{

public:

	// Member types
	typedef std::bidirectional_iterator_tag	iterator_category;
	typedef std::ptrdiff_t					difference_type;
	typedef std::size_t						size_type;
	typedef	map_iterator<const Key, T, Compare, IsConst>		Iterator;

	typedef	const Key			key_type;
	typedef	T					mapped_type;
	typedef	pair<const Key, T>	value_type;
	typedef typename ft::select_const_type<IsConst, value_type*, const value_type*>::type	pointer;
	typedef typename ft::select_const_type<IsConst, value_type&, const value_type&>::type	reference;

private:

	typedef node<Key, T, Compare>			node;

public:

	// Member functions
	map_reverse_iterator( node *ptr = NULL, bool is_end = false ) :
		_node(ptr), _is_end(is_end)
	{
		return;
	}
	explicit map_reverse_iterator( Iterator x ):
		_node(x.getNode()), _is_end(x.isEnd())
	{
		++(*this);
		return;
	}
	map_reverse_iterator( const map_reverse_iterator<const Key, T, Compare> &other ):
		_node(other.getNode()), _is_end(other._is_end)
	{
		return;
	}
	~map_reverse_iterator( void ) { return; }

	map_reverse_iterator &operator=( const map_reverse_iterator<const Key, T, Compare> &other )
	{
		this->_node = other._node;
		this->_is_end = other._is_end;
		return *this;
	}

	node	*getNode( void ) const { return _node; }
	bool	isEnd( void ) const { return _is_end; }

	Iterator	base( void ) const
	{
		map_reverse_iterator	tmp(*this);

		--tmp;
		return Iterator(tmp.getNode(), tmp._is_end);
	}

	reference			operator*( void ) const
	{
		map_reverse_iterator	tmp(*this);

		/* ++tmp; */
		return tmp._node->getValue();
	}
	pointer				operator->( void ) const
	{
		map_reverse_iterator	tmp(*this);

		/* ++tmp; */
		return &tmp._node->getValue();
	}

	map_reverse_iterator&	operator++( void )
	{
		node *tmp = this->_node->getTreePredecessor();
		
		if (this->_is_end == true)
			this->_is_end = false;
		else if (tmp->isNil())
			this->_is_end = true;
		else
			this->_node = tmp;
		return *this;
	}  
	map_reverse_iterator&	operator--( void )
	{
		node *tmp = this->_node->getTreeSuccessor();
		
		if (this->_is_end)
			this->_is_end = false;
		else if (tmp->isNil())
			this->_is_end = true;
		else
			this->_node = tmp;
		return *this;

	}
	map_reverse_iterator		operator++( int ) {
		map_reverse_iterator tmp(*this);
		++(*this);
		return tmp;
	}
	map_reverse_iterator		operator--( int ) {
		map_reverse_iterator tmp(*this);
		--(*this);
		return tmp;
	}

	friend bool	operator==( const map_reverse_iterator& lhs, const map_reverse_iterator& rhs )
	{
		if (lhs._is_end != rhs._is_end)
			return false;
		else if (lhs._is_end == true)
			return true;
		else
			return lhs._node == rhs._node;
	}
	friend bool	operator!=( const map_reverse_iterator& lhs, const map_reverse_iterator& rhs )
	{
		if (lhs._is_end != rhs._is_end)
			return true;
		else if (lhs._is_end == true)
			return false;
		else
			return lhs._node != rhs._node;
	}

private:

	node	*_node;
	bool	_is_end;

};

}

#endif
