/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Node.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulohl <pohl@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 16:31:10 by paulohl           #+#    #+#             */
/*   Updated: 2022/01/26 10:13:25 by pohl             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NODE_HPP
# define NODE_HPP

# include <iostream>
# include "pair.hpp"

template<typename Key, typename T, typename Compare = std::less<Key>,
	typename Allocator = std::allocator<ft::pair<const Key, T> > >
class Node
{

// Member types
public:

	typedef	Key						key_type;
	typedef	T						mapped_type;
	typedef	ft::pair<const Key, T>	value_type;

public:

	Node( const value_type &value ):
		_left_child(NULL), _right_child(NULL), _parent(NULL),
		_nodeAlloc(std::allocator<Node>()), _pairAlloc(Allocator())
	{
		_pairAlloc.construct(&(this->_data), value);
		return;
	}
	Node( const Node &src ) { *this = src; }
	~Node( void ) { }

	Node	&operator=( const Node &rhs )
	{
		_pairAlloc.destroy(&(this->_data));
		_pairAlloc.construct(&(this->_data), rhs._data);
		this->_left_child = rhs._left_child;
		this->_right_child = rhs._right_child;
		this->_parent = rhs._parent;
		return *this;
	}

	void	assign(const Node &other )
	{
		_pairAlloc.construct(&(this->_data), other._data);
		this->_left_child = other._left_child;
		this->_right_child = other._right_child;
		this->_parent = other._parent;
	}

	/* getters */
	value_type			&getPair( void ) { return _data; }
	const value_type	&getPair( void ) const { return _data; }
	/* Key					&getKey( void ) { return _data.first; } */
	const Key			&getKey( void ) const { return _data.first; }
	T					&getValue( void ) const { return _data.second; }
	const T				&getValue( void ) { return _data.second; }
	Node				*getLeftChild( void ) const { return _left_child; }
	Node				*getRightChild( void ) const { return _right_child; }
	Node				*getChild( int which ) const
	{
		if (which != Node::left && which != Node::right)
			throw std::out_of_range("getChild only accepts 'Node::left' and "
					"'Node::right', select using these");
		return which == Node::left ? _left_child : _right_child;
	}
	Node	*getParent( void ) const { return _parent; }
	Node	*getSibling( void ) const
	{
		if (!this->getParent())
			return NULL;
		else if (this->getParent()->getLeftChild() == this)
			return this->getParent()->getRightChild();
		else
			return this->getParent()->getLeftChild();
	}
	int					getBalance( void ) const
	{
		Node *right = getRightChild();
		Node *left = getLeftChild();

		(void)right; (void)left;
		if (isLeaf())
			return 0;
		else if (getRightChild() == NULL)
			return -getLeftChild()->getDepth();
		else if (getLeftChild() == NULL)
			return getRightChild()->getDepth();
		else
			return getRightChild()->getDepth() - getLeftChild()->getDepth();
	}
	int					getChildCount( void ) const
	{
		if (isLeaf())
			return 0;
		else if (getLeftChild() && getRightChild())
			return 2;
		else
			return 1;
	}
	bool				isLeaf( void ) const
	{
		return (this->getLeftChild() == NULL && this->getRightChild() == NULL);
	}

	/* setters */
	void	setLeftChild(Node *newChild)
	{
		_left_child = newChild;
	}
	void	setRightChild(Node *newChild)
	{
		_right_child = newChild;
	}
	void	setChild(Node *newChild, int side)
	{
		if (side == Node::left)
			_left_child = newChild;
		else
			_right_child = newChild;
	}
	void	setParent(Node *newParent)
	{
		_parent = newParent;
	}
	void	setValue(T newValue)
	{
		_data.second = newValue;
	}
	Node	*insertChild(Node *newChild, int side)
	{
		if (side == Node::left)
			_left_child = newChild;
		else
			_right_child = newChild;
		newChild->_parent = this;
		return newChild;
	}

	/* Copy */
	Node	*clone( void )
	{
		Node *result = this->_nodeAlloc.allocate(1);

		*result = *this;
		if (result->_left_child)
		{
			result->_left_child = this->_left_child->clone();
			result->_left_child->_parent = result;
		}
		if (result->_right_child)
		{
			result->_right_child = this->_right_child->clone();
			result->_right_child->_parent = result;
		}
		return result;
	}

	/* Values */
	Node	*lower_bound( const key_type &key )
	{
		if (key == getKey())
			return this;
		if (_cmp(getKey(), key))
		{
			if (getRightChild())
				return getRightChild()->lower_bound(key);
			return NULL;
		}
		Node *tmp = NULL;
		if (getLeftChild())
			tmp = getLeftChild()->lower_bound(key);
		if (tmp == NULL)
			return this;
		return tmp;
	}
	Node	*upper_bound( const key_type &key )
	{
		if (_cmp(getKey(), key) || getKey() == key)
		{
			if (getRightChild())
				return getRightChild()->upper_bound(key);
			return NULL;
		}
		Node *tmp = NULL;
		if (getLeftChild())
			tmp = getLeftChild()->upper_bound(key);
		if (tmp == NULL)
			return this;
		return tmp;
	}
	Node	*under_bound( const key_type &key )
	{
		if (_cmp(key, getKey()) || getKey() == key)
		{
			if (getLeftChild())
				return getLeftChild()->under_bound(key);
			return NULL;
		}
		Node *tmp = NULL;
		if (getRightChild())
			tmp = getRightChild()->under_bound(key);
		if (tmp == NULL)
			return this;
		return tmp;
	}
	Node	*minimum( void )
	{
		Node *result = this;

		if (!result)
			return result;
		while (result->getLeftChild())
			result = result->getLeftChild();
		return result;
	}
	Node	*maximum( void )
	{
		Node *result = this;

		if (!result)
			return result;
		while (result->getRightChild())
			result = result->getRightChild();
		return result;
	}

	/* Destruction */
	void	clear( void )
	{
		if (this->getLeftChild())
			this->getLeftChild()->clear();
		if (this->getRightChild())
			this->getRightChild()->clear();
		_pairAlloc.destroy(&(this->_data));
		_nodeAlloc.deallocate(this, 1);
	}

private:

	int					getDepth( void ) const
	{
		int		tmpLeft;
		int		tmpRight;

		if (isLeaf())
			return 1;
		tmpLeft = getLeftChild() ? 1 + getLeftChild()->getDepth() : 1;
		tmpRight = getRightChild() ? 1 + getRightChild()->getDepth() : 1;
		return tmpLeft > tmpRight ? tmpLeft : tmpRight;
	}

public:

	const static int	right = 0;
	const static int	left = 1;

private:

	value_type				_data;
	Node					*_left_child;
	Node					*_right_child;
	Node					*_parent;
	std::allocator<Node>	_nodeAlloc;
	Allocator				_pairAlloc;
	Compare					_cmp;

};

#endif
