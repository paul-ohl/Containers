/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulohl <pohl@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 11:05:42 by paulohl           #+#    #+#             */
/*   Updated: 2022/02/10 10:55:03 by pohl             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP

# include <fstream>
# include "Node.hpp"
# include "map_iterator.hpp"
# include "map_reverse_iterator.hpp"
# include "pair.hpp"

namespace ft
{

template< typename Key, typename T, typename Cmp = std::less<Key>,
	typename Allocator = std::allocator<pair<const Key, T> > >
class map
{

// Member types
public:

	typedef Key										key_type;
	typedef T										mapped_type;
	typedef pair<const Key, T>						value_type;
	typedef std::size_t								size_type;
	typedef std::ptrdiff_t							difference_type;
	typedef Cmp										key_compare;
	typedef Allocator								allocator_type;
	typedef typename Allocator::reference			reference;
	typedef typename Allocator::const_reference		const_reference;
	typedef typename Allocator::pointer				pointer;
	typedef typename Allocator::const_pointer		const_pointer;
	typedef map_iterator<const Key, T, Cmp>				iterator;
	typedef const_map_iterator<const Key, T, Cmp>			const_iterator;
	typedef map_reverse_iterator<const Key, T, Cmp>		reverse_iterator;
	typedef map_reverse_iterator<const Key, T, Cmp>		const_reverse_iterator;

private:

	typedef Node<const Key, T, Cmp>	node;

// Member class
public:

	class value_compare
	{

	public:

		typedef bool		result_type;
		typedef value_type	first_argument_type;
		typedef value_type	second_argument_type;

	public:

		Cmp	comp;

		value_compare( Cmp c = Cmp() ): comp(c) { return ; }

	public:

		bool operator()( const value_type& lhs, const value_type& rhs ) const
		{
			return comp(lhs.first, rhs.first);
		}

	};

public:

	// Default constructor
	explicit map( const key_compare &cmp = key_compare(),
			const Allocator &alloc = Allocator() ):
		_root(NULL), _comparator(cmp), _pairAlloc(alloc), _size(0)
	{
		return ;
	}
	// Iterator constructor
	template< class InputIt >
	map( InputIt first, InputIt last,
			const Cmp& cmp = Cmp(),
			const Allocator& alloc = Allocator() ):
		_root(NULL), _comparator(cmp), _pairAlloc(alloc), _size(0)
	{
		while (first != last)
		{
			this->insert(*first);
			first++;
		}
		return ;
	}
	// Copy constructor
	map( const map& other ): _root(NULL)
	{
		*this = other;
	}
	// Destructor
	~map( void )
	{
		this->clear();
		return;
	}

	// Assignation operator
	map	&operator=( const map &rhs )
	{
		this->_pairAlloc = rhs._pairAlloc;
		this->_comparator = rhs._comparator;
		this->clear();
		this->_size = rhs._size;
		this->_root = rhs._root->clone();
		return *this;
	}

	allocator_type	get_pairAlloc( void ) const { return _pairAlloc; }

	// Element access
	mapped_type			&at( const key_type &key )
	{
		return *this[key];
	}
	const mapped_type	&at( const key_type &key ) const
	{
		return *this[key];
	}
	mapped_type			&operator[]( const key_type &key )
	{
		value_type	tmp = ft::make_pair(key, mapped_type());

		return (this->insert(tmp).first)->second;
	}

	// Iterator operations
	iterator				begin( void )
	{
		node	*begin_node = _root->minimum();

		if (begin_node)
			return iterator(begin_node);
		return iterator(NULL, true);
	}
	iterator			begin( void ) const
	{
		node	*begin_node = _root->minimum();

		if (begin_node)
			return iterator(begin_node);
		return iterator(NULL, true);
	}
	iterator				end( void )
	{
		return iterator(_root->maximum(), true);
	}
	iterator			end( void ) const
	{
		return iterator(_root->maximum(), true);
	}
	reverse_iterator		rbegin( void )
	{
		return reverse_iterator(_root->maximum());
	}
	const_reverse_iterator	rbegin( void ) const
	{
		return const_reverse_iterator(_root->maximum());
	}
	reverse_iterator		rend( void )
	{
		return reverse_iterator(_root->minimum(), true);
	}
	const_reverse_iterator	rend( void ) const
	{
		return const_reverse_iterator(_root->minimum(), true);
	}

	// Capacity
	bool		empty( void ) const { return _size == 0; }
	size_type	size( void ) const { return _size; }
	size_type	max_size( void ) const { return _nodeAlloc.max_size(); }

	// Modifiers
	void						clear ( void )
	{
		if (this->_root)
			this->_root->clear();
		this->_root = NULL;
		this->_size = 0;
	}
	pair<iterator, bool>	insert( const value_type &value )
	{
		node	*newNode = _nodeAlloc.allocate(1);
		node	*insertedPlace = NULL;

		newNode->assign(node(value));
		insertedPlace = insertNode(newNode, _root);
		if (newNode == insertedPlace)
		{
			this->_size++;
			return ft::make_pair(iterator(insertedPlace), true);
		}
		newNode->clear();
		return ft::make_pair(iterator(insertedPlace), false);
	}
	iterator					insert( iterator hint, const value_type &value)
	{
		(void)hint;
		return insert(value).first;
	}
	template< typename InputIt >
	void						insert( InputIt first, InputIt last )
	{
		while (first != last)
		{
			this->insert(*first);
			first++;
		}
	}
	void						erase( iterator pos )
	{
		node	*to_delete = pos.getNode();
		node	*tmp;

		if (to_delete->getLeftChild() == NULL)
			transplant(to_delete, to_delete->getRightChild());
		else if (to_delete->getRightChild() == NULL)
			transplant(to_delete, to_delete->getLeftChild());
		else
		{
			tmp = to_delete->getRightChild()->minimum();
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
		_pairAlloc.destroy(&to_delete->getPair());
		_nodeAlloc.deallocate(to_delete, 1);
		to_delete = NULL;
		this->_size--;
		while (tmp)
		{
			correctInbalance(tmp);
			tmp = tmp->getParent();
		}
	}
	void						erase( iterator first, iterator last )
	{
		while (first != last)
			this->erase(first++);
	}
	size_type					erase( const key_type &key )
	{
		iterator	to_erase = find(key);

		if (to_erase == this->end())
			return (0);
		erase(to_erase);
		return (1);
	}
	void						swap( map &other )
	{
		node			*tmp_root = other._root;
		key_compare		tmp_comparator = other._comparator;
		allocator_type	tmp_pairAlloc = other._pairAlloc;
		size_type		tmp_size = other._size;

		other._root = this->_root;
		other._comparator = this->_comparator;
		other._pairAlloc = this->_pairAlloc;
		other._size = this->_size;
		this->_root = tmp_root;
		this->_comparator = tmp_comparator;
		this->_pairAlloc = tmp_pairAlloc;
		this->_size = tmp_size;
	}

	// Lookup
	size_type		count( const key_type &key ) const
	{
		return find(key) == end() ? 0 : 1;
	}
	iterator		find( const key_type &key )
	{
		node *tmp = findNode(key);

		if (!tmp)
			return iterator(this->_root->maximum(), true);
		else
			return iterator(tmp);
	}
	const_iterator	find( const key_type &key ) const
	{
		node *tmp = findNode(key);

		if (!tmp)
			return const_iterator(this->_root->maximum(), true);
		else
			return const_iterator(tmp);
	}
	pair<iterator, iterator>	equal_range( const key_type &key )
	{
		return ft::make_pair(lower_bound(key), upper_bound(key));
	}
	pair<const_iterator, const_iterator>	equal_range( const key_type &key ) const
	{
		return ft::make_pair(lower_bound(key), upper_bound(key));
	}
	iterator		lower_bound( const key_type &key )
	{
		node	*lower_bound_node = _root->lower_bound(key);

		if (lower_bound_node)
			return iterator(lower_bound_node);
		return iterator(lower_bound_node, true);
	}
	const_iterator	lower_bound( const key_type &key ) const
	{
		node	*lower_bound_node = _root->lower_bound(key);

		if (lower_bound_node)
			return const_iterator(lower_bound_node);
		return const_iterator(lower_bound_node, true);
	}
	iterator		upper_bound( const key_type &key )
	{
		node	*upper_bound_node = _root->upper_bound(key);

		if (upper_bound_node)
			return iterator(upper_bound_node);
		return iterator(upper_bound_node, true);
	}
	const_iterator	upper_bound( const key_type &key ) const
	{
		node	*upper_bound_node = _root->upper_bound(key);

		if (upper_bound_node)
			return const_iterator(upper_bound_node);
		return const_iterator(upper_bound_node, true);
	}

	// Observers
	key_compare		key_comp( void ) const { return _comparator; }
	value_compare	value_comp( void ) const { return value_compare(); }

	// Non-member functions
	friend bool	operator==( const map &lhs, const map &rhs )
	{
		iterator	lhs_it = lhs.begin();
		iterator	lhs_ite = lhs.end();
		iterator	rhs_it = rhs.begin();
		iterator	rhs_ite = rhs.end();

		while (lhs_it != lhs_ite && rhs_it != rhs_ite)
		{
			if (lhs_it->second != rhs_it->second)
				return false;
			lhs_it++;
			rhs_it++;
		}
		if (lhs_it != lhs_ite || rhs_it != rhs_ite)
			return false;
		return true;
	}
	friend bool	operator!=( const map &lhs, const map &rhs )
	{
		return !(lhs == rhs);
	}
	friend bool	operator<( const map &lhs, const map &rhs )
	{
		iterator	lhs_it = lhs.begin();
		iterator	lhs_ite = lhs.end();
		iterator	rhs_it = rhs.begin();
		iterator	rhs_ite = rhs.end();

		while (lhs_it != lhs_ite && rhs_it != rhs_ite)
		{
			if (lhs_it->second != rhs_it->second)
				return lhs_it->second < rhs_it->second;
			lhs_it++;
			rhs_it++;
		}
		if (rhs_it == rhs_ite)
			return false;
		return true;
	}
	friend bool	operator>( const map &lhs, const map &rhs )
	{
		return rhs < lhs;
	}
	friend bool	operator<=( const map &lhs, const map &rhs )
	{
		return !(lhs > rhs);
	}
	friend bool	operator>=( const map &lhs, const map &rhs )
	{
		return !(lhs < rhs);
	}
	friend void	swap( map &rhs, map &lhs )
	{
		lhs.swap(rhs);
	}

	// Debug
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
		/* std::cout << "Printed tree in ./tree_visualisation.mmd" << std::endl; */
	}

private:

	node	*findNode( const key_type &key )
	{
		node	*result = _root;

		while (result && result->getKey() != key)
		{
			if (_comparator(key, result->getKey()))
				result = result->getLeftChild();
			else
				result = result->getRightChild();
		}
		return result;
	}
	node	*findNode( const key_type &key ) const
	{
		node	*result = _root;

		while (result && result->getKey() != key)
		{
			if (_comparator(key, result->getKey()))
				result = result->getLeftChild();
			else
				result = result->getRightChild();
		}
		return result;
	}
	node	*insertNode( node *to_insert, node *current_node = NULL )
	{
		if (!to_insert)
			return NULL;
		if (!_root)
		{
			_root = to_insert;
			return _root;
		}
		if (!current_node)
			current_node = _root;
		if (_comparator(to_insert->getKey(), current_node->getKey()))
		{
			if (current_node->getLeftChild())
				current_node = insertNode(to_insert, current_node->getLeftChild());
			else
				current_node = current_node->insertChild(to_insert, map::left);
		}
		else if (_comparator(current_node->getKey(), to_insert->getKey()))
		{
			if (current_node->getRightChild())
				current_node = insertNode(to_insert, current_node->getRightChild());
			else
				current_node = current_node->insertChild(to_insert, map::right);
		}
		correctInbalance(current_node);
		return current_node;
	}
	void	correctInbalance( node *node )
	{
		int	inbalance = node->getBalance();
		int	side;

		if (inbalance > 1 || inbalance < -1)
		{
			side = inbalance < 0 ? map::left : map::right;
			if ((inbalance ^ node->getChild(side)->getBalance()) < 0) // are this node and its child the same sign
				rotate(node->getChild(side), side);
			rotate(node, 1 - side);
		}
		if (node->getParent())
			correctInbalance(node->getParent());
	}
	void	rotate( node *hinge, int	side )
	{
		node	*other = hinge->getChild(1 - side);

		hinge->setChild(other->getChild(side), 1 - side);
		if (other->getChild(side))
			other->getChild(side)->setParent(hinge);
		other->setParent(hinge->getParent());
		if (hinge->getParent() == NULL)
			_root = other;
		else if (hinge->getParent()->getLeftChild() == hinge)
			hinge->getParent()->setLeftChild(other);
		else
			hinge->getParent()->setRightChild(other);
		other->setChild(hinge, side);
		hinge->setParent(other);
	}
	void	transplant( node *original, node *replacement )
	{
		if (original->getParent() == NULL)
			this->_root = replacement;
		else if (original == original->getParent()->getLeftChild())
			original->getParent()->setLeftChild(replacement);
		else
			original->getParent()->setRightChild(replacement);
		if (replacement != NULL)
			replacement->setParent(original->getParent());
	}
	void	traverseTree( node *node, std::ofstream &file) const
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

private:

	node					*_root;
	key_compare				_comparator;
	allocator_type			_pairAlloc;
	size_type				_size;
	std::allocator<node>	_nodeAlloc;

	const static int	right = 0;
	const static int	left = 1;

};

}

#endif
