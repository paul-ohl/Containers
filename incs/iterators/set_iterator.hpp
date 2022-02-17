/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_iterator.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulohl <pohl@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 17:39:43 by paulohl           #+#    #+#             */
/*   Updated: 2022/02/17 10:33:00 by pohl             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SET_ITERATOR_HPP
# define SET_ITERATOR_HPP

# include <iterator>
# include "set_node.hpp"
# include "select_const_type.hpp"

namespace ft
{

template < typename Key, typename Compare = std::less<Key>,
		 bool IsConst = false >
class set_iterator
{

public:

	// Member types
	typedef std::bidirectional_iterator_tag	iterator_category;
	typedef std::ptrdiff_t					difference_type;
	typedef std::size_t						size_type;

	typedef	Key	key_type;
	typedef	Key	value_type;

	typedef typename ft::select_const_type<IsConst, value_type*, const value_type*>::type	pointer;
	typedef typename ft::select_const_type<IsConst, value_type&, const value_type&>::type	reference;

private:

	typedef node<Key, Compare>			node;

public:

	// Member functions
	set_iterator( node *ptr = NULL, bool is_end = false ) :
		_node(ptr), _is_end(is_end)
	{
		return;
	}
	set_iterator( const set_iterator<const Key, Compare> &other ):
		_node(other.getNode()), _is_end(other.isEnd())
	{
		return;
	}
	~set_iterator( void ) { return; }

	set_iterator &operator=( const set_iterator<const Key, Compare> &other )
	{
		this->_node = other._node;
		this->_is_end = other._is_end;
		return *this;
	}

	node	*getNode( void ) const { return _node; }
	bool	isEnd( void ) const { return _is_end; }

	reference			operator*( void ) const { return this->_node->getValue(); }
	pointer				operator->( void ) const { return &this->_node->getValue(); }

	set_iterator&	operator++( void )
	{
		node *tmp = this->_node->getTreeSuccessor();
		
		if (tmp->isNil())
			this->_is_end = true;
		else
			this->_node = tmp;
		return *this;
	}  
	set_iterator&	operator--( void )
	{
		node *tmp = this->_node->getTreePredecessor();
		
		if (this->_is_end)
			this->_is_end = false;
		else if (tmp->isNil())
			this->_is_end = true;
		else
			this->_node = tmp;
		return *this;

	}  
	set_iterator		operator++( int ) {
		set_iterator tmp(*this);
		++(*this);
		return tmp;
	}
	set_iterator		operator--( int ) {
		set_iterator tmp(*this);
		--(*this);
		return tmp;
	}

	friend bool	operator==( const set_iterator& lhs, const set_iterator& rhs )
	{
		if (lhs._is_end != rhs._is_end)
			return false;
		else if (lhs._is_end == true)
			return true;
		else
			return lhs._node == rhs._node;
	}
	friend bool	operator!=( const set_iterator& lhs, const set_iterator& rhs )
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
