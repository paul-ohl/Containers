/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AvlTree.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulohl <pohl@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 16:31:38 by paulohl           #+#    #+#             */
/*   Updated: 2021/12/13 11:40:11 by paulohl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef AVLTREE_HPP
# define AVLTREE_HPP

# include <iostream>
# include <memory>
# include <fstream>

template< typename Key, typename T, typename Compare = std::less<Key>,
	typename Allocator = std::allocator< std::pair<Key, T> > >
class AvlTree
{

private:

	// Node struct to build the tree
	struct Node
	{
		std::pair<const Key, T>	data;
		Node					*_left_child;
		Node					*_right_child;
		Node					*_parent;
	};

public:

	AvlTree<Key, T>( const Compare &comp = Compare(),
			const Allocator &alloc = Allocator() ):
		_root(NULL), _comparison(comp), _dataAlloc(alloc),
		_nodeAlloc(std::allocator<Node>())
	{
		return;
	}
	AvlTree<Key, T>( Node *node ): _root(node) { return; }
	AvlTree<Key, T>( const AvlTree<Key, T> &src ) { *this = src; }
	~AvlTree<Key, T>( void )
	{
		// TODO: Deallocate that bitch!
		return;
	}

	AvlTree<Key, T>	&operator=( const AvlTree<Key, T> &rhs )
	{
		this->deleteWholeTree();
		this->_allocator = rhs._allocator;
		this->_root = copyNode(rhs._root);
		return *this;
	}

	/* getters */
	Node	*getRoot( void ) const { return _root; }
	Node	*findNode( const Key &key ) const
	{
		Node	*result = _root;

		while (result && result->getKey() != key)
		{
			if (key < result->getKey())
				result = result->getLeftChild();
			else
				result = result->getRightChild();
		}
		return result;
	}
	Node	*treeMinimum( Node *root = NULL ) const
	{
		if (!root)
			root = _root;
		while (root->getLeftChild())
			root = root->getLeftChild();
		return root;
	}

	void	insertNode( const Node &node )
	{
		Node	*newNode = _nodeAlloc.allocate(1);

		*newNode = node;
		insertNode(newNode);
	}
	void	insertNode( Node *to_insert, Node *current_node = NULL )
	{
		if (!to_insert)
			return;
		if (!_root)
		{
			_root = to_insert;
			return;
		}
		if (!current_node)
			current_node = _root;
		if (to_insert->getKey() < current_node->getKey())
		{
			if (current_node->getLeftChild())
				insertNode(to_insert, current_node->getLeftChild());
			else
				current_node->insertChild(to_insert, AvlTree::left);
		}
		else if (to_insert->getKey() > current_node->getKey())
		{
			if (current_node->getRightChild())
				insertNode(to_insert, current_node->getRightChild());
			else
				current_node->insertChild(to_insert, AvlTree::right);
		}
		else
		{
			current_node->setT(to_insert->getT());
			_nodeAlloc.deallocate(to_insert, 1);
			to_insert = NULL;
		}
		correctInbalance(current_node);
	}
	bool	deleteNode( const Key &key )
	{
		Node	*to_delete = findNode(key);

		if (!to_delete)
			return false;
		deleteNode(to_delete);
		return true;
	}
	void	deleteNode( Node *to_delete )
	{
		Node	*tmp;

		if (to_delete->getLeftChild() == NULL)
			transplant(to_delete, to_delete->getRightChild());
		else if (to_delete->getRightChild() == NULL)
			transplant(to_delete, to_delete->getLeftChild());
		else
		{
			tmp = treeMinimum(to_delete->getRightChild());
			if (tmp->getParent() != to_delete)
			{
				transplant(tmp, tmp->getRightChild());
				tmp->setRightChild(to_delete->getRightChild());
				tmp->getRightChild()->setParent(tmp);
			}
			transplant(to_delete, tmp);
			tmp->setLeftChild(to_delete->getLeftChild());
			tmp->getLeftChild()->setParent(tmp);
		}
		tmp = to_delete->getParent();
		_nodeAlloc.deallocate(to_delete, 1);
		to_delete = NULL;
		while (tmp)
		{
			correctInbalance(tmp);
			tmp = tmp->getParent();
		}
	}
	void	rotate( Node *node, int	side )
	{
		Node	*other = node->getChild(1 - side);

		node->setChild(other->getChild(side), 1 - side);
		if (other->getChild(side))
			other->getChild(side)->setParent(node);
		other->setParent(node->getParent());
		if (node->getParent() == NULL)
			_root = other;
		else if (node->getParent()->getLeftChild() == node)
			node->getParent()->setLeftChild(other);
		else
			node->getParent()->setRightChild(other);
		other->setChild(node, side);
		node->setParent(other);
	}

	void	printTree( void ) const
	{
		std::ofstream	myfile;

		myfile.open("tree_visualisation.mmd", std::ios::out);
		myfile << "flowchart TD" << std::endl;
		if (_root)
			traverseTree(this->_root, myfile);
		else
			myfile << "Empty tree" << std::endl;
		myfile.close();
		std::cout << "Printed tree in ./tree_visualisation.mmd" << std::endl;
	}

private:

	void	traverseTree( Node *node, std::ofstream &file) const
	{
		file << node << "(" << node->getKey() << " - " << node->getBalance() << ")" << std::endl;
		if (node->getParent())
			file << node << "-->" << node->getParent() << std::endl;
		if (node->getLeftChild())
		{
			file << node << "-.->" << node->getLeftChild() << std::endl;
			traverseTree(node->getLeftChild(), file);
		}
		if (node->getRightChild())
		{
			file << node << "==>" << node->getRightChild() << std::endl;
			traverseTree(node->getRightChild(), file);
		}
	}
	Node	*copyNode(Node &other)
	{
		Node	*result;

		result = _nodeAlloc.allocate(1);
		*result = *other;
		result->getParent() = NULL;
		if (other.getLeftChild())
		{
			result->getLeftChild() = copyNode(other.getLeftChild());
			result->getLeftChild()->getParent() = result;
		}
		if (other.getRightChild())
		{
			result->getRightChild() = copyNode(other.getRightChild());
			result->getRightChild()->getParent() = result;
		}
		return result;
	}
	void	transplant( Node *original, Node *replacement )
	{
		if (original->getParent() == NULL)
			_root = replacement;
		else if (original == original->getParent()->getLeftChild())
			original->getParent()->setLeftChild(replacement);
		else
			original->getParent()->setRightChild(replacement);
		if (replacement != NULL)
			replacement->setParent(original->getParent());
	}
	void	correctInbalance( Node *node )
	{
		int	inbalance = node->getBalance();
		int	side;

		if (inbalance > 1 || inbalance < -1)
		{
			side = inbalance < 0 ? AvlTree::left : AvlTree::right;
			if ((inbalance ^ node->getChild(side)->getBalance()) < 0) // are this node and its child the same sign
				rotate(node->getChild(side), side);
			rotate(node, 1 - side);
		}
	}

public:

	const static int	right = 0;
	const static int	left = 1;

private:

	Node					*_root;
	Compare					_comparison;
	Allocator				_dataAlloc;
	std::allocator<Node>	_nodeAlloc;

};

template<typename Key, typename T>
std::ostream	&operator<<( std::ostream &ostr, const AvlTree<Key, T> &instance );

#endif
