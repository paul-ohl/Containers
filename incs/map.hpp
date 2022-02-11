/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pohl <pohl@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 09:03:00 by pohl              #+#    #+#             */
/*   Updated: 2022/02/11 17:23:28 by pohl             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP

# include "RBTree/tree.hpp"
# include "iterators/map_iterator.hpp"
# include "iterators/reverse_iterator.hpp"

namespace ft
{

template< typename Key, typename T, typename Cmp = std::less<Key>,
	typename Allocator = std::allocator<pair<const Key, T> > >
class map
{

public:

	typedef Key					key_type;
	typedef T					mapped_type;
	typedef pair<const Key, T>	value_type;
	typedef std::size_t			size_type;
	typedef std::ptrdiff_t		difference_type;
	typedef Cmp					key_compare;
	typedef Allocator			allocator_type;

	typedef typename Allocator::reference			reference;
	typedef typename Allocator::const_reference		const_reference;
	typedef typename Allocator::pointer				pointer;
	typedef typename Allocator::const_pointer		const_pointer;

	typedef map_iterator<const Key, T, Cmp>									iterator;
	typedef map_iterator<const Key, T, Cmp, true>							const_iterator;
	typedef ft::reverse_iterator<map_iterator<const Key, T, Cmp> >			reverse_iterator;
	typedef ft::reverse_iterator<map_iterator<const Key, T, Cmp, true> >	const_reverse_iterator;

	typedef tree<const Key, T, Cmp, Allocator>			tree_type;

public:

	explicit map( const key_compare &cmp = key_compare(),
			const Allocator &alloc = Allocator() ):
		_comparator(cmp), _valueAlloc(alloc)
	{
		return;
	}
	template< typename InputIt >
	map( InputIt first, InputIt last, const key_compare &cmp = key_compare(),
			const Allocator &alloc = Allocator() ):
		_comparator(cmp), _valueAlloc(alloc)
	{
		this->insert(first, last);
	}
	map( const map& other )
	{
		this->_rbTree = other._rbTree;
		this->_comparator = other._comparator;
		this->_valueAlloc = other._valueAlloc;
	}
	~map( void )
	{
	}

	map	&operator=( const map& other )
	{
		if (this == &other)
			return *this;
		this->_rbTree = other._rbTree;
		this->_comparator = other._comparator;
		this->_valueAlloc = other._valueAlloc;
		return *this;
	}

	/* mapped_type&	operator[]( const key_type& key ) */
	/* { */
	/* } */

	iterator	begin( void )
	{
		return iterator(this->_rbTree.treeMinimum());
	}
	const_iterator	begin( void ) const
	{
		return const_iterator(this->_rbTree.treeMinimum());
	}
	iterator	end( void )
	{
		return iterator(this->_rbTree.treeMaximum(), true);
	}
	const_iterator	end( void ) const
	{
		return const_iterator(this->_rbTree.treeMaximum(), true);
	}
	reverse_iterator	rbegin( void )
	{
		return reverse_iterator(this->end());
	}
	const_reverse_iterator	rbegin( void ) const
	{
		return const_reverse_iterator(this->end());
	}
	reverse_iterator	rend( void )
	{
		return reverse_iterator(this->begin());
	}
	const_reverse_iterator	rend( void ) const
	{
		return const_reverse_iterator(this->begin());
	}

	bool		empty( void ) const { return _rbTree.size() == 0; }
	size_type	size( void ) const { return _rbTree.size(); }
	size_type	max_size( void ) const { return _rbTree.max_size(); }

	ft::pair<iterator, bool>	insert( const value_type& value )
	{
		bool		wasInserted = false;
		iterator	inserted = this->_rbTree.insertValue(value, wasInserted);

		return ft::make_pair(iterator(inserted), wasInserted);
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
	void	clear( void )
	{
		this->_rbTree.clear();
	}

	void	swap( map& other )
	{
		allocator_type				tmp_valueAlloc = other._valueAlloc;
		key_compare					tmp_comparator = other._comparator;

		other._valueAlloc = this->_valueAlloc;
		other._comparator = this->_comparator;
		this->_valueAlloc = tmp_valueAlloc;
		this->_comparator = tmp_comparator;
		this->_rbTree.swap(other._rbTree);
	}

	void	printTree( void ) const
	{
		_rbTree.printTree();
	}

private:

	tree_type		_rbTree;
	key_compare		_comparator;
	allocator_type	_valueAlloc;

};

}

#endif
