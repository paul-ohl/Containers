/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pohl <pohl@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 09:03:00 by pohl              #+#    #+#             */
/*   Updated: 2022/02/08 17:51:50 by pohl             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP

# include "RBTree/tree.hpp"

namespace ft
{

template< typename Key, typename T, typename Cmp = std::less<Key>,
	typename Allocator = std::allocator<pair<const Key, T> > >
class map
{

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

	typedef tree<Key, T, Cmp, Allocator>			tree_type;

public:

	explicit map( const key_compare &cmp = key_compare(),
			const Allocator &alloc = Allocator() ):
		_comparator(cmp), _valueAlloc(alloc)
	{
		return;
	}
	~map( void )
	{
		_rbTree.clear();
	}

	void	insert( const key_type &key, mapped_type &mapped )
	{
		this->insert(make_pair(key, mapped));
	}
	void	insert( value_type value )
	{
		this->_rbTree.insertValue(value);
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
