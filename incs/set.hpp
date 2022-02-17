/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pohl <pohl@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 09:03:00 by pohl              #+#    #+#             */
/*   Updated: 2022/02/17 10:47:25 by pohl             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SET_HPP
# define SET_HPP

# include "set_tree.hpp"
# include "set_iterator.hpp"
# include "set_reverse_iterator.hpp"

namespace ft
{

template< typename Key, typename Cmp = std::less<Key>,
	typename Allocator = std::allocator<Key> >
class set
{

public:

	typedef Key					key_type;
	typedef Key					value_type;
	typedef std::size_t			size_type;
	typedef std::ptrdiff_t		difference_type;
	typedef Cmp					key_compare;
	typedef Cmp					value_compare;
	typedef Allocator			allocator_type;

	typedef typename Allocator::reference			reference;
	typedef typename Allocator::const_reference		const_reference;
	typedef typename Allocator::pointer				pointer;
	typedef typename Allocator::const_pointer		const_pointer;

	typedef set_iterator<Key, Cmp>						iterator;
	typedef set_iterator<Key, Cmp, true>				const_iterator;
	typedef ft::set_reverse_iterator<Key, Cmp>			reverse_iterator;
	typedef ft::set_reverse_iterator<Key, Cmp, true>	const_reverse_iterator;

	typedef tree<Key, Cmp, Allocator>			tree_type;

public:

	explicit set( const key_compare &cmp = key_compare(),
			const Allocator &alloc = Allocator() ):
		_comparator(cmp), _valueAlloc(alloc)
	{
		return;
	}
	template< typename InputIt >
	set( InputIt first, InputIt last, const key_compare &cmp = key_compare(),
			const Allocator &alloc = Allocator() ):
		_comparator(cmp), _valueAlloc(alloc)
	{
		this->insert(first, last);
	}
	set( const set& other )
	{
		this->_rbTree = other._rbTree;
		this->_comparator = other._comparator;
		this->_valueAlloc = other._valueAlloc;
	}
	~set( void )
	{
	}

	set	&operator=( const set& other )
	{
		if (this == &other)
			return *this;
		this->_rbTree = other._rbTree;
		this->_comparator = other._comparator;
		this->_valueAlloc = other._valueAlloc;
		return *this;
	}

	iterator	begin( void )
	{
		return iterator(this->_rbTree.treeMinimum(), (_rbTree.size() == 0));
	}
	iterator	begin( void ) const
	{
		return iterator(this->_rbTree.treeMinimum(), (_rbTree.size() == 0));
	}
	iterator	end( void )
	{
		return iterator(this->_rbTree.treeMaximum(), true);
	}
	iterator	end( void ) const
	{
		return iterator(this->_rbTree.treeMaximum(), true);
	}
	reverse_iterator	rbegin( void )
	{
		return reverse_iterator(this->_rbTree.treeMaximum(), (_rbTree.size() == 0));
	}
	reverse_iterator	rbegin( void ) const
	{
		return reverse_iterator(this->_rbTree.treeMaximum(), (_rbTree.size() == 0));
	}
	reverse_iterator	rend( void )
	{
		return reverse_iterator(this->_rbTree.treeMinimum(), true);
	}
	reverse_iterator	rend( void ) const
	{
		return reverse_iterator(this->_rbTree.treeMinimum(), true);
	}

	bool		empty( void ) const { return _rbTree.size() == 0; }
	size_type	size( void ) const { return _rbTree.size(); }
	size_type	max_size( void ) const { return _rbTree.max_size(); }

	key_compare		key_comp( void ) const { return this->_comparator; }
	value_compare	value_comp() const { return value_compare(key_comp()); }
	allocator_type	get_allocator( void ) const { return this->_valueAlloc; }

	iterator		find( key_type key )
	{
		node<Key, Cmp, Allocator>	*result = _rbTree.findNode(key);

		if (result->isNil())
			return this->end();
		return iterator(result);
	}
	const_iterator	find( key_type key ) const
	{
		node<Key, Cmp, Allocator>	*result = _rbTree.findNode(key);

		if (result->isNil())
			return this->end();
		return const_iterator(result);
	}
	size_type	count( key_type key ) const
	{
		if (_rbTree.findNode(key)->isNil())
			return 0;
		return 1;
	}
	iterator		lower_bound( key_type key )
	{
		node<Key, Cmp, Allocator>	*result = _rbTree.lower_bound(key);

		if (result->isNil())
			return this->end();
		return iterator(result);
	}
	const_iterator		lower_bound( key_type key ) const
	{
		node<Key, Cmp, Allocator>	*result = _rbTree.lower_bound(key);

		if (result->isNil())
			return this->end();
		return const_iterator(result);
	}
	iterator		upper_bound( key_type key )
	{
		node<Key, Cmp, Allocator>	*result = _rbTree.upper_bound(key);

		if (result->isNil())
			return this->end();
		return iterator(result);
	}
	const_iterator		upper_bound( key_type key ) const
	{
		node<Key, Cmp, Allocator>	*result = _rbTree.upper_bound(key);

		if (result->isNil())
			return this->end();
		return const_iterator(result);
	}
	std::pair<iterator, iterator>	equal_range( key_type key )
	{
		return std::make_pair(this->lower_bound(key), this->upper_bound(key));
	}
	std::pair<const_iterator, const_iterator>	equal_range( key_type& key ) const
	{
		return std::make_pair(this->lower_bound(key), this->upper_bound(key));
	}

	std::pair<iterator, bool>	insert( value_type value )
	{
		bool		wasInserted = false;
		iterator	inserted = this->_rbTree.insertValue(value, wasInserted);

		return std::make_pair(iterator(inserted), wasInserted);
	}
	iterator	insert( iterator position, value_type value )
	{
		bool placeholder = false;

		if ((*position).first + 1 == value.first)
			return this->_rbTree.insertValue(position.getNode(), value,
					placeholder);
		return this->_rbTree.insertValue(value, placeholder);
	}
	template< typename InputIt >
	void	insert( InputIt first, InputIt last )
	{
		bool useless;

		while (first != last)
		{
			this->_rbTree.insertValue(*first, useless);
			first++;
		}
	}

	void	erase( iterator position )
	{
		this->_rbTree.eraseNode(position.getNode());
	}
	void	erase( iterator first, iterator last )
	{
		while (first != last)
			this->_rbTree.eraseNode((first++).getNode());
	}
	size_type	erase( key_type key )
	{
		return this->_rbTree.eraseNodeFromKey(key);
	}

	void	clear( void )
	{
		this->_rbTree.clear();
	}

	void	swap( set& other )
	{
		allocator_type				tmp_valueAlloc = other._valueAlloc;
		key_compare					tmp_comparator = other._comparator;

		other._valueAlloc = this->_valueAlloc;
		other._comparator = this->_comparator;
		this->_valueAlloc = tmp_valueAlloc;
		this->_comparator = tmp_comparator;
		this->_rbTree.swap(other._rbTree);
	}

	friend bool	operator==( const set &lhs, const set &rhs )
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
	friend bool	operator!=( const set &lhs, const set &rhs )
	{
		return !(lhs == rhs);
	}
	friend bool	operator<( const set &lhs, const set &rhs )
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
	friend bool	operator>( const set &lhs, const set &rhs )
	{
		return rhs < lhs;
	}
	friend bool	operator<=( const set &lhs, const set &rhs )
	{
		return !(lhs > rhs);
	}
	friend bool	operator>=( const set &lhs, const set &rhs )
	{
		return !(lhs < rhs);
	}
	friend void	swap( set &rhs, set &lhs )
	{
		lhs.swap(rhs);
	}

	void	printTree( void ) const
	{
		_rbTree.printTree();
	}

private:

	tree_type		_rbTree;
	key_compare		_comparator;
	allocator_type	_valueAlloc;

	bool	alreadyExists( key_type& key ) const
	{
		return _rbTree.findNode(key)->isNil();
	}

};

}

#endif
