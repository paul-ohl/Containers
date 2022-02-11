/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_reverse_iterator.hpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulohl <pohl@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 17:39:43 by paulohl           #+#    #+#             */
/*   Updated: 2022/01/26 14:36:04 by pohl             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_REVERSE_ITERATOR_HPP
# define MAP_REVERSE_ITERATOR_HPP

# include <iterator>
# include "Node.hpp"
# include "map_iterator.hpp"

namespace ft
{

template <typename Key, typename T, typename Compare = std::less<Key> >
class map_reverse_iterator
{

public:

	// Member types
	typedef std::bidirectional_iterator_tag	iterator_category;
	typedef std::ptrdiff_t					difference_type;
	typedef std::size_t						size_type;

	typedef	Key					key_type;
	typedef	T					mapped_type;
	typedef	pair<const Key, T>	value_type;
	typedef value_type*			pointer;
	typedef value_type&			reference;

private:

	typedef Node<Key, T, Compare>			node;

public:

	// Member functions
	map_reverse_iterator( node *ptr = NULL, bool is_end = false ) :
		_node(ptr), _is_end(is_end)
	{
		return;
	}
	map_reverse_iterator( const map_reverse_iterator &other ):
		_node(other.getNode()), _is_end(other._is_end)
	{
		return;
	}
	map_reverse_iterator( const map_iterator<Key, T, Compare> &other ):
		_node(other.getNode()), _is_end(other.isEnd())
	{
		(*this)++;
		return;
	}
	map_reverse_iterator( const const_map_iterator<Key, T, Compare> &other ):
		_node(other.getNode()), _is_end(other.isEnd())
	{
		(*this)++;
		return;
	}
	~map_reverse_iterator( void ) { return; }

	map_reverse_iterator &operator=( const map_reverse_iterator &other )
	{
		this->_node = other._node;
		this->_is_end = other._is_end;
		return *this;
	}

	node	*getNode( void ) const { return _node; }

	map_iterator<Key, T, Compare>	base( void ) const
	{
		map_reverse_iterator	tmp(*this);

		tmp--;
		return map_iterator<Key, T, Compare>(tmp.getNode(), tmp._is_end);
	}

	reference			operator*( void ) const { return this->_node->getPair(); }
	pointer				operator->( void ) const { return &this->_node->getPair(); }

	map_reverse_iterator&	operator++( void )
	{
		node	*tmp = this->_node;

		if (!tmp)
		{
			this->_is_end = true;
			return *this;
		}
		while (tmp->getParent())
			tmp = tmp->getParent();
		tmp = tmp->under_bound(this->_node->getKey());
		if (!tmp)
			this->_is_end = true;
		else
			this->_node = tmp;
		return *this;
	}
	map_reverse_iterator&	operator--( void )
	{
		const Key	&key = this->_node->getKey();

		if (this->_is_end)
		{
			this->_is_end = false;
			return *this;
		}
		while (this->_node->getParent())
			this->_node = this->_node->getParent();
		this->_node = this->_node->upper_bound(key);
		return *this;
	}
	map_reverse_iterator		operator++( int ) {
		map_reverse_iterator tmp(*this);
		++(*this);
		return tmp;
	}
	map_reverse_iterator		operator--( int ) {
		map_reverse_iterator tmp(*this);
		--(*this);
		return tmp;
	}

	friend bool	operator==( const map_reverse_iterator& lhs, const map_reverse_iterator& rhs )
	{
		if (lhs._is_end != rhs._is_end)
			return false;
		else if (lhs._is_end == true)
			return true;
		else
			return lhs._node == rhs._node;
	}
	friend bool	operator!=( const map_reverse_iterator& lhs, const map_reverse_iterator& rhs )
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

template <typename Key, typename T, typename Compare = std::less<Key> >
class const_map_reverse_iterator
{

public:

	// Member types
	typedef std::bidirectional_iterator_tag	iterator_category;
	typedef std::ptrdiff_t					difference_type;
	typedef std::size_t						size_type;

	typedef	Key					key_type;
	typedef	T					mapped_type;
	typedef	pair<const Key, T>	value_type;
	typedef const value_type*			pointer;
	typedef const value_type&			reference;

private:

	typedef Node<Key, T, Compare>			node;

public:

	// Member functions
	const_map_reverse_iterator( node *ptr = NULL, bool is_end = false ) :
		_node(ptr), _is_end(is_end)
	{
		return;
	}
	const_map_reverse_iterator( const const_map_reverse_iterator<const Key, T, Compare> &other ):
		_node(other.getNode()), _is_end(other._is_end)
	{
		return;
	}
	const_map_reverse_iterator( const map_iterator<const Key, T, Compare> &other ):
		_node(other.getNode()), _is_end(other._is_end)
	{
		return;
	}
	const_map_reverse_iterator( const const_map_iterator<const Key, T, Compare> &other ):
		_node(other.getNode()), _is_end(other._is_end)
	{
		return;
	}
	~const_map_reverse_iterator( void ) { return; }

	const_map_reverse_iterator &operator=( const const_map_reverse_iterator<const Key, T, Compare> &other )
	{
		this->_node = other._node;
		this->_is_end = other._is_end;
		return *this;
	}

	node	*getNode( void ) const { return _node; }

	const_map_iterator<Key, T, Compare>	base( void ) const
	{
		const_map_reverse_iterator	tmp(*this);

		tmp--;
		return const_map_iterator<Key, T, Compare>(tmp.getNode(), tmp._is_end);
	}

	reference			operator*( void ) const { return this->_node->getPair(); }
	pointer				operator->( void ) const { return &this->_node->getPair(); }

	const_map_reverse_iterator&	operator++( void )
	{
		node	*tmp = this->_node;

		while (tmp->getParent())
			tmp = tmp->getParent();
		tmp = tmp->under_bound(this->_node->getKey());
		if (!tmp)
			this->_is_end = true;
		else
			this->_node = tmp;
		return *this;
	}  
	const_map_reverse_iterator&	operator--( void )
	{
		const Key	&key = this->_node->getKey();

		if (this->_is_end)
		{
			this->_is_end = false;
			return *this;
		}
		while (this->_node->getParent())
			this->_node = this->_node->getParent();
		this->_node = this->_node->upper_bound(key);
		return *this;
	}  
	const_map_reverse_iterator		operator++( int ) {
		const_map_reverse_iterator tmp(*this);
		++(*this);
		return tmp;
	}
	const_map_reverse_iterator		operator--( int ) {
		const_map_reverse_iterator tmp(*this);
		--(*this);
		return tmp;
	}

	friend bool	operator==( const const_map_reverse_iterator& lhs, const const_map_reverse_iterator& rhs )
	{
		if (lhs._is_end != rhs._is_end)
			return false;
		else if (lhs._is_end == true)
			return true;
		else
			return lhs._node == rhs._node;
	}
	friend bool	operator!=( const const_map_reverse_iterator& lhs, const const_map_reverse_iterator& rhs )
	{
		if (lhs._is_end != rhs._is_end)
			return true;
		else if (lhs._is_end == true)
			return false;
		else
			return lhs._node != rhs._node;
	}

private:

	const node	*_node;
	bool	_is_end;

};


}

#endif

