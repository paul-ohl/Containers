/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pohl <pohl@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 08:52:10 by pohl              #+#    #+#             */
/*   Updated: 2022/02/10 17:34:30 by pohl             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TREE_HPP
# define TREE_HPP

#include <iostream>

# include <fstream>
# include "utils/pair.hpp"
# include "RBTree/node.hpp"

namespace ft
{

template< typename Key, typename T, typename Cmp = std::less<Key>,
	typename Allocator = std::allocator<pair<const Key, T> > >
class tree
{

public:

	typedef node<const Key, T, Cmp, Allocator>	node;
	typedef Key								key_type;
	typedef T								mapped_type;
	typedef ft::pair<const Key, T>			value_type;
	typedef std::size_t						size_type;

	tree( void ):
		_root(NULL), _size(0), _comparator(Cmp()), _valueAlloc(Allocator())
	{
		this->_nodeAlloc = std::allocator<node>();
		this->initializeNil();
		this->_root = this->nil;
	}
	tree( const tree& other ): _nodeAlloc(other._nodeAlloc)
	{
		*this = other;
	}
	~tree( void )
	{
		this->clear();
	}

	tree&	operator=( const tree& other )
	{
		if (this == &other)
			return *this;
		this->clear();
		this->_comparator = other._comparator;
		this->_nodeAlloc = other._nodeAlloc;
		this->_valueAlloc = other._valueAlloc;
		this->initializeNil();
		this->_root = this->clone(other._root);
		this->_size = other._size;
		return *this;
	}

	node	*getRootNode( void ) { return this->_root; }
	size_type	size( void ) const { return this->_size; }
	size_type	max_size( void ) const { return this->_nodeAlloc.max_size(); }

	void	clear( void )
	{
		if (!_root->isNil())
			clearNodesRecursively(_root);
		deleteNode(this->nil);
	}
	void	rotateLeft( node *hinge )
	{
		this->rotateSide(hinge, LEFT);
	}
	void	rotateRight( node *hinge )
	{
		this->rotateSide(hinge, RIGHT);
	}
	void	insertValue( value_type &value )
	{
		node	*nodeToInsert = newNode(value);

		this->insertNode(nodeToInsert);
	}

	const node*	treeSearch( const key_type& key ) const
	{
		return this->treeSearch( this->_root, key );
	}
	const node*	treeSearch( node* current_node, const key_type& key ) const
	{
		if (current_node->isNil() || current_node->getKey() == key)
			return current_node;
		if (_comparator(current_node->getKey(), key))
			return this->treeSearch(current_node->leftChild, key);
		return this->treeSearch(current_node->rightChild, key);
	}
	node*	treeMinimum( void )
	{
		return this->_root->getTreeMinimum();
	}
	const node*	treeMinimum( void ) const
	{
		return this->_root->getTreeMinimum();
	}
	node*	treeMaximum( void )
	{
		return this->_root->getTreeMaximum();
	}
	const node*	treeMaximum( void ) const
	{
		return this->_root->getTreeMaximum();
	}

	void	printTree( void ) const
	{
		std::ofstream	myfile;

		myfile.open("tree_visualisation.mmd", std::ios::out);
		myfile << "flowchart TD" << std::endl;
		myfile << "classDef RED fill:#FF0000,color:#FFFFFF;" << std::endl;
		myfile << "classDef BLACK fill:#000000,color:#FFFFFF;" << std::endl;
		if (_root)
			traverseTree(this->_root, myfile);
		else
			myfile << "Empty tree" << std::endl;
		myfile.close();
	}

private:

	node*					_root;
	node*					nil;
	size_type				_size;
	Cmp						_comparator;
	Allocator				_valueAlloc;
	std::allocator<node>	_nodeAlloc;

private:

	void	initializeNil( void )
	{
		value_type	nilValue = ft::make_pair(Key(), T());

		this->nil = this->newNode(nilValue);
		this->nil->color = BLACK;
		this->nil->parent = NULL;
		this->nil->leftChild = NULL;
		this->nil->rightChild = NULL;
	}

	void	clearNodesRecursively( node *to_delete )
	{
		if (!to_delete->leftChild->isNil())
			clearNodesRecursively(to_delete->leftChild);
		if (!to_delete->rightChild->isNil())
			clearNodesRecursively(to_delete->rightChild);
		deleteNode(to_delete);
	}
	void	insertNode( node *nodeToInsert )
	{
		node	*insertionParent = getInsertionParent(nodeToInsert->getKey());

		nodeToInsert->parent = insertionParent;
		if (insertionParent->isNil())
			this->_root = nodeToInsert;
		else if (_comparator(nodeToInsert->getKey(), insertionParent->getKey()))
			insertionParent->leftChild = nodeToInsert;
		else
			insertionParent->rightChild = nodeToInsert;
		this->insertFixup(nodeToInsert);
		this->_size++;
	}
	void	rotateSide( node *hinge, char side )
	{
		node	*movedNode = hinge->getChild(1 - side);

		if (side == LEFT)
			hinge->rightChild = movedNode->leftChild;
		else
			hinge->leftChild = movedNode->rightChild;
		if (!movedNode->getChild(side)->isNil())
			movedNode->getChild(side)->parent = hinge;
		movedNode->parent = hinge->parent;
		if (hinge->parent->isNil())
			this->_root = movedNode;
		else if (hinge->isALeftChild())
			hinge->parent->leftChild = movedNode;
		else
			hinge->parent->rightChild = movedNode;
		if (side == LEFT)
			movedNode->leftChild = hinge;
		else
			movedNode->rightChild = hinge;
		hinge->parent = movedNode;
	}
	node*	getInsertionParent( const key_type &insertKey )
	{
		node*	traversingTree = this->_root;
		node*	result = this->nil;

		while (!traversingTree->isNil())
		{
			result = traversingTree;
			if (_comparator(insertKey, traversingTree->getKey()))
				traversingTree = traversingTree->leftChild;
			else
				traversingTree = traversingTree->rightChild;
		}
		return result;
	}
	void	insertFixup( node *lastInsertedNode )
	{
		while (lastInsertedNode->parent->color == RED)
		{
			if (lastInsertedNode->parent->isALeftChild())
				colorFixup(lastInsertedNode, RIGHT);
			else
				colorFixup(lastInsertedNode, LEFT);
		}
		this->_root->color = BLACK;
	}
	node*	colorFixup( node *lastInsertedNode, char side )
	{
		node*	tmp;

		tmp = lastInsertedNode->parent->parent->getChild(side);
		if (tmp->color == RED)
		{
			lastInsertedNode->parent->color = BLACK;
			tmp->color = BLACK;
			lastInsertedNode->parent->parent->color = RED;
			return lastInsertedNode->parent->parent;
		}
		if (lastInsertedNode->parent->getChild(side) == lastInsertedNode)
		{
			lastInsertedNode = lastInsertedNode->parent;
			this->rotateSide(lastInsertedNode, 1 - side);
		}
		lastInsertedNode->parent->color = BLACK;
		lastInsertedNode->parent->parent->color = RED;
		this->rotateSide(lastInsertedNode->parent->parent, side);
		return lastInsertedNode;
	}
	node*	newNode( value_type &value )
	{
		node	*newNode = _nodeAlloc.allocate(1);

		_valueAlloc.construct(&newNode->value, value);
		newNode->leftChild = this->nil;
		newNode->rightChild = this->nil;
		newNode->parent = this->nil;
		newNode->color = RED;
		return newNode;
	}
	void	deleteNode( node* node )
	{
		_valueAlloc.destroy(&node->value);
		_nodeAlloc.deallocate(node, 1);
	}

	node	*clone( node *src )
	{
		node *result = this->newNode(src->value);

		result->color = src->color;
		if (src->leftChild->isNil())
			result->leftChild = this->nil;
		else
		{
			result->leftChild = this->clone(src->leftChild);
			result->leftChild->parent = result;
		}
		if (src->rightChild->isNil())
			result->rightChild = this->nil;
		else
		{
			result->rightChild = this->clone(src->rightChild);
			result->rightChild->parent = result;
		}
		return result;
	}

	void	traverseTree( node *node, std::ofstream &file) const
	{
		file << node << "(" << node->getKey() << " - " << node->getMapped()
			<< ")" << std::endl;
		file << "class " << node << " " << node->getColorAsString() << ";"
			<< std::endl;
		if (!node->parent->isNil())
			file << node << "-->" << node->parent << std::endl;
		if (!node->leftChild->isNil())
		{
			file << node << "-.->" << node->leftChild << std::endl;
			traverseTree(node->leftChild, file);
		}
		if (!node->rightChild->isNil())
		{
			file << node << "==>" << node->rightChild << std::endl;
			traverseTree(node->rightChild, file);
		}
	}

};

}

#endif
