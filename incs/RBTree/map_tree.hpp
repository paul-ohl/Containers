/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_tree.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pohl <pohl@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 08:52:10 by pohl              #+#    #+#             */
/*   Updated: 2022/02/17 11:21:40 by pohl             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TREE_HPP
# define TREE_HPP

#include <iostream>

# include <fstream>
# include "pair.hpp"
# include "map_node.hpp"

namespace ft
{

template< typename Key, typename T, typename Cmp = std::less<Key>,
	typename Allocator = std::allocator<pair<const Key, T> > >
class tree
{

public:

	typedef node<const Key, T, Cmp, Allocator>	node;
	typedef Key									key_type;
	typedef T									mapped_type;
	typedef ft::pair<const Key, T>				value_type;
	typedef std::size_t							size_type;

	tree( void ):
		_root(NULL), _size(0), _comparator(Cmp()), _valueAlloc(Allocator())
	{
		this->_nodeAlloc = std::allocator<node>();
		this->initializeNil();
		this->_root = this->nil;
	}
	tree( const tree& other ): _nodeAlloc(other._nodeAlloc)
	{
		this->_nodeAlloc = std::allocator<node>();
		this->initializeNil();
		*this = other;
	}
	~tree( void )
	{
		this->clear();
		deleteNode(this->nil);
		this->nil = NULL;
	}

	tree&	operator=( const tree& other )
	{
		if (this == &other)
			return *this;
		this->clear();
		this->_comparator = other._comparator;
		this->_valueAlloc = other._valueAlloc;
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
		this->_root = this->nil;
	}
	void	rotateLeft( node *hinge )
	{
		this->rotateSide(hinge, LEFT);
	}
	void	rotateRight( node *hinge )
	{
		this->rotateSide(hinge, RIGHT);
	}
	node*	insertValue( const value_type& value, bool &wasInserted )
	{
		node	*insertionParent = getInsertionParent(value.first);

		return insertValue(insertionParent, value, wasInserted);
	}
	node*	insertValue( node* insertionParent, const value_type& value,
			bool &wasInserted )
	{
		node	*nodeToInsert;

		if (value.first == insertionParent->getKey()
				&& !insertionParent->isNil())
		{
			wasInserted = false;
			return insertionParent;
		}
		nodeToInsert = newNode(value);
		nodeToInsert->parent = insertionParent;
		if (insertionParent->isNil())
			this->_root = nodeToInsert;
		else if (_comparator(nodeToInsert->getKey(), insertionParent->getKey()))
			insertionParent->leftChild = nodeToInsert;
		else
			insertionParent->rightChild = nodeToInsert;
		this->insertFixup(nodeToInsert);
		this->_size++;
		wasInserted = true;
		return nodeToInsert;
	}
	size_type	eraseNodeFromKey( const key_type& key )
	{
		node	*foundNode = this->findNode(key);
		if (foundNode->isNil())
			return 0;
		eraseNode(foundNode);
		return 1;
	}
	void	eraseNode( node* toDelete )
	{
		node*	x = this->nil;
		node*	y = toDelete;
		char	yOriginalColor = y->color;

		if (toDelete->leftChild->isNil())
		{
			x = toDelete->rightChild;
			transplant(toDelete, toDelete->rightChild);
		}
		else if (toDelete->rightChild->isNil())
		{
			x = toDelete->leftChild;
			transplant(toDelete, toDelete->leftChild);
		}
		else
		{
			y = toDelete->rightChild->getTreeMinimum();
			yOriginalColor = y->color;
			x = y->rightChild;
			if (y->parent == toDelete && !x->isNil())
				x->parent = y;
			else
			{
				transplant(y, y->rightChild);
				y->rightChild = toDelete->rightChild;
				if (!y->rightChild->isNil())
					y->rightChild->parent = y;
			}
			transplant(toDelete, y);
			y->leftChild = toDelete->leftChild;
			if (!y->leftChild->isNil())
				y->leftChild->parent = y;
			y->color = toDelete->color;
		}
		if (yOriginalColor == BLACK)
			deleteFixup(x);
		this->_size--;
		deleteNode(toDelete);
	}

	node*	findNode( const key_type& key )
	{
		return this->findNode( this->_root, key );
	}
	node*	findNode( node* current_node, const key_type& key )
	{
		if (current_node->isNil() || current_node->getKey() == key)
			return current_node;
		if (_comparator(key, current_node->getKey()))
			return this->findNode(current_node->leftChild, key);
		return this->findNode(current_node->rightChild, key);
	}
	node*	findNode( const key_type& key ) const
	{
		return this->findNode(this->_root, key);
	}
	node*	findNode( node* current_node, const key_type& key ) const
	{
		if (current_node->isNil() || current_node->getKey() == key)
			return current_node;
		if (_comparator(key, current_node->getKey()))
			return this->findNode(current_node->leftChild, key);
		return this->findNode(current_node->rightChild, key);
	}
	node*	lower_bound( const key_type& key )
	{
		return this->lower_bound(this->_root, key);
	}
	node*	lower_bound( const key_type& key ) const
	{
		return this->lower_bound(this->_root, key);
	}
	node*	lower_bound( node* current_node, const key_type& key)
	{
		node *tmp = this->nil;

		if (current_node->isNil() || key == current_node->getKey())
			return current_node;
		if (_comparator(current_node->getKey(), key))
			return lower_bound(current_node->rightChild, key);
		tmp = lower_bound(current_node->leftChild, key);
		if (tmp->isNil())
			return current_node;
		return tmp;
	}
	node*	lower_bound( node* current_node, const key_type& key) const
	{
		node *tmp = this->nil;

		if (current_node->isNil() || key == current_node->getKey())
			return current_node;
		if (_comparator(current_node->getKey(), key))
			return lower_bound(current_node->rightChild, key);
		tmp = lower_bound(current_node->leftChild, key);
		if (tmp->isNil())
			return current_node;
		return tmp;
	}
	node*	upper_bound( const key_type& key )
	{
		return this->upper_bound(this->_root, key);
	}
	node*	upper_bound( const key_type& key ) const
	{
		return this->upper_bound(this->_root, key);
	}
	node*	upper_bound( node* current_node, const key_type& key)
	{
		node *tmp = this->nil;

		if (current_node->isNil())
			return current_node;
		if (_comparator(current_node->getKey(), key) || current_node->getKey() == key)
			return upper_bound(current_node->rightChild, key);
		tmp = upper_bound(current_node->leftChild, key);
		if (tmp->isNil())
			return current_node;
		return tmp;
	}
	node*	upper_bound( node* current_node, const key_type& key) const
	{
		node *tmp = this->nil;

		if (current_node->isNil())
			return current_node;
		if (_comparator(current_node->getKey(), key) || current_node->getKey() == key)
			return upper_bound(current_node->rightChild, key);
		tmp = upper_bound(current_node->leftChild, key);
		if (tmp->isNil())
			return current_node;
		return tmp;
	}
	node*	treeMinimum( void )
	{
		return this->_root->getTreeMinimum();
	}
	node*	treeMinimum( void ) const
	{
		return this->_root->getTreeMinimum();
	}
	node*	treeMaximum( void )
	{
		return this->_root->getTreeMaximum();
	}
	node*	treeMaximum( void ) const
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
	void	swap ( tree& other )
	{
		node*					tmp_root = other._root;
		node*					tmp_nil = other.nil;
		size_type				tmp_size = other._size;
		Cmp						tmp_comparator = other._comparator;
		Allocator				tmp_valueAlloc = other._valueAlloc;

		other._root = this->_root;
		other.nil = this->nil;
		other._size = this->_size;
		other._comparator = this->_comparator;
		other._valueAlloc = this->_valueAlloc;
		this->_root = tmp_root;
		this->nil = tmp_nil;
		this->_size = tmp_size;
		this->_comparator = tmp_comparator;
		this->_valueAlloc = tmp_valueAlloc;
	}

private:

	node*					_root;
	node*					nil;
	size_type				_size;
	Cmp						_comparator;
	Allocator				_valueAlloc;
	std::allocator<node>	_nodeAlloc;

private:

	void	transplant( node* oldNode, node* newNode )
	{
		if (oldNode->parent->isNil())
			this->_root = newNode;
		else if (oldNode->isALeftChild())
			oldNode->parent->leftChild = newNode;
		else
			oldNode->parent->rightChild = newNode;
		if (!newNode->isNil())
			newNode->parent = oldNode->parent;
	}
	void	deleteFixup( node* x )
	{
		node*	w = this->nil;

		while (x != this->_root && x->color == BLACK)
		{
			if (x == x->parent->leftChild)
			{
				w = x->parent->rightChild;
				if (w->color == RED)
				{
					w->color = BLACK;
					x->parent->color = RED;
					rotateLeft(x->parent);
					w = x->parent->rightChild;
				}
				if (w->leftChild->color == BLACK && w->rightChild->color == BLACK)
				{
					w->color = RED;
					x = x->parent;
				}
				else
				{
					if (w->rightChild->color == BLACK)
					{
						w->leftChild->color = BLACK;
						w->color = RED;
						rotateRight(w);
						w = x->parent->rightChild;
					}
					w->color = x->parent->color;
					x->parent->color = BLACK;
					w->rightChild->color = BLACK;
					rotateLeft(x->parent);
					x = this->_root;
				}
			}
			else
			{
				w = x->parent->leftChild;
				if (w->color == RED)
				{
					w->color = BLACK;
					x->parent->color = RED;
					rotateRight(x->parent);
					w = x->parent->leftChild;
				}
				if (w->rightChild->color == BLACK && w->leftChild->color == BLACK)
				{
					w->color = RED;
					x = x->parent;
				}
				else
				{
					if (w->leftChild->color == BLACK)
					{
						w->rightChild->color = BLACK;
						w->color = RED;
						rotateLeft(w);
						w = x->parent->leftChild;
					}
					w->color = x->parent->color;
					x->parent->color = BLACK;
					w->leftChild->color = BLACK;
					rotateRight(x->parent);
					x = this->_root;
				}
			}
		}
		x->color = BLACK;
	}

	void	initializeNil( void )
	{
		value_type	nilValue = ft::make_pair(Key(), T());

		this->nil = this->newNode(nilValue);
		this->nil->color = BLACK;
		this->nil->parent = this->nil;
		this->nil->leftChild = this->nil;
		this->nil->rightChild = this->nil;
	}

	void	clearNodesRecursively( node *toDelete )
	{
		if (!toDelete->leftChild->isNil())
			clearNodesRecursively(toDelete->leftChild);
		if (!toDelete->rightChild->isNil())
			clearNodesRecursively(toDelete->rightChild);
		deleteNode(toDelete);
		this->_size--;
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
			else if (insertKey == traversingTree->getKey())
				return result;
			else
				traversingTree = traversingTree->rightChild;
		}
		return result;
	}
	void	insertFixup( node *lastInsertedNode )
	{
		node	*tmp;

		while (lastInsertedNode->parent->color == RED)
		{
			if (lastInsertedNode->parent == lastInsertedNode->parent->parent->leftChild)
			{
				tmp = lastInsertedNode->parent->parent->rightChild;
				if (tmp->color == RED)
				{
					lastInsertedNode->parent->color = BLACK;
					tmp->color = BLACK;
					lastInsertedNode->parent->parent->color = RED;
					lastInsertedNode = lastInsertedNode->parent->parent;
				}
				else
				{
					if (lastInsertedNode == lastInsertedNode->parent->rightChild)
					{
						lastInsertedNode = lastInsertedNode->parent;
						this->rotateLeft(lastInsertedNode);
					}
					lastInsertedNode->parent->color = BLACK;
					lastInsertedNode->parent->parent->color = RED;
					this->rotateRight(lastInsertedNode->parent->parent);
				}
			}
			else
			{
				tmp = lastInsertedNode->parent->parent->leftChild;
				if (tmp->color == RED)
				{
					lastInsertedNode->parent->color = BLACK;
					tmp->color = BLACK;
					lastInsertedNode->parent->parent->color = RED;
					lastInsertedNode = lastInsertedNode->parent->parent;
				}
				else
				{
					if (lastInsertedNode == lastInsertedNode->parent->leftChild)
					{
						lastInsertedNode = lastInsertedNode->parent;
						this->rotateRight(lastInsertedNode);
					}
					lastInsertedNode->parent->color = BLACK;
					lastInsertedNode->parent->parent->color = RED;
					this->rotateLeft(lastInsertedNode->parent->parent);
				}
			}
		}
		this->_root->color = BLACK;
	}
	node*	newNode( const value_type &value )
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
