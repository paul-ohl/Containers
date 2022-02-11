/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pohl <pohl@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 08:52:50 by pohl              #+#    #+#             */
/*   Updated: 2022/02/11 12:18:56 by pohl             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NODE_HPP
# define NODE_HPP

#include <iostream>

# include <stdexcept>
# include "utils/pair.hpp"

# define RED 0
# define BLACK 1

# define LEFT 0
# define RIGHT 1

namespace ft
{

template<typename Key, typename T, typename Compare = std::less<Key>,
	typename Allocator = std::allocator<ft::pair<const Key, T> > >
class node
{

public:

	typedef const Key						key_type;
	typedef T								mapped_type;
	typedef pair<const Key, T>				value_type;
	typedef std::size_t						size_type;

	node( void ):
		parent(NULL), rightChild(NULL), leftChild(NULL), color(RED)
	{
		value.first = Key();
		value.second = T();
	}
	node( value_type &value ):
		parent(NULL), rightChild(NULL), leftChild(NULL), color(RED), value(value)
	{ return; }
	~node( void )
	{
		return;
	}

	node&	operator=( const node& other )
	{
		this->parent = other.parent;
		this->rightChild = other.rightChild;
		this->leftChild = other.leftChild;
		this->color = other.color;
	}

	bool			isNil( void) const
	{
		return this->parent == this;
	}
	bool	isALeftChild( void ) const
	{
		return this->parent->leftChild == this;
	}
	bool	isARightChild( void ) const
	{
		return this->parent->rightChild == this;
	}
	node	*getChild( int side )
	{
		if (side == LEFT)
			return this->leftChild;
		if (side == RIGHT)
			return this->rightChild;
		throw std::invalid_argument("You can only use value LEFT (0) and RIGHT (1)");
	}

	value_type&		getValue( void ) { return value; }
	const value_type&		getValue( void ) const { return value; }
	const key_type&	getKey( void ) const { return value.first; }
	mapped_type&	getMapped( void ) { return value.second; }
	const mapped_type&	getMapped( void ) const { return value.second; }
	std::string		getColorAsString( void ) const
	{
		if (this->color == RED)
			return std::string("RED");
		else
			return std::string("BLACK");
	}
	char			getColorAsChar( void ) const
	{
		return this->color;
	}

	node*	getTreeMinimum( void )
	{
		node*	treeMinimum = this;

		while (!treeMinimum->leftChild->isNil())
			treeMinimum = treeMinimum->leftChild;
		return treeMinimum;
	}
	const node*	getTreeMinimum( void ) const
	{
		const node*	treeMinimum = this;

		while (!treeMinimum->leftChild->isNil())
			treeMinimum = treeMinimum->leftChild;
		return treeMinimum;
	}
	node*	getTreeMaximum( void )
	{
		node*	treeMaximum = this;

		while (!treeMaximum->rightChild->isNil())
			treeMaximum = treeMaximum->rightChild;
		return treeMaximum;
	}
	const node*	getTreeMaximum( void ) const
	{
		const node*	treeMaximum = this;

		while (!treeMaximum->rightChild->isNil())
			treeMaximum = treeMaximum->rightChild;
		return treeMaximum;
	}
	node*	getTreeSuccessor( const node *current_node = NULL )
	{
		node*	tmp;

		if (current_node == NULL)
			current_node = this;
		if (!current_node->rightChild->isNil())
			return current_node->rightChild->getTreeMinimum();
		tmp = current_node->parent;
		while ((!tmp->isNil()) && current_node == tmp->rightChild)
		{
			current_node = tmp;
			tmp = tmp->parent;
		}
		return tmp;
	}
	const node*	getTreeSuccessor( const node *current_node = NULL ) const
	{
		const node*	tmp;

		if (current_node == NULL)
			current_node = this;
		if (!current_node->rightChild->isNil())
			return current_node->rightChild->getTreeMinimum();
		tmp = current_node->parent;
		while ((!tmp->isNil()) && current_node == tmp->rightChild)
		{
			current_node = tmp;
			tmp = tmp->parent;
		}
		return tmp;
	}
	node*	getTreePredecessor( const node *current_node = NULL )
	{
		node*	tmp;

		if (current_node == NULL)
			current_node = this;
		if (!current_node->leftChild->isNil())
			return current_node->leftChild->getTreeMaximum();
		tmp = current_node->parent;
		while ((!tmp->isNil()) && current_node == tmp->leftChild)
		{
			current_node = tmp;
			tmp = tmp->parent;
		}
		return tmp;
	}
	const node*	getTreePredecessor( const node *current_node = NULL ) const
	{
		const node*	tmp;

		if (current_node == NULL)
			current_node = this;
		if (!current_node->leftChild->isNil())
			return current_node->leftChild->getTreeMaximum();
		tmp = current_node->parent;
		while ((!tmp->isNil()) && current_node == tmp->leftChild)
		{
			current_node = tmp;
			tmp = tmp->parent;
		}
		return tmp;
	}

public:

	node*		parent;
	node*		rightChild;
	node*		leftChild;
	char		color;
	value_type	value;

};

}

#endif
