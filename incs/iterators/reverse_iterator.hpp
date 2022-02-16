/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pohl <pohl@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 17:41:10 by pohl              #+#    #+#             */
/*   Updated: 2022/02/16 16:56:33 by pohl             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REVERSE_ITERATOR_HPP
# define REVERSE_ITERATOR_HPP

# include "iterator_traits.hpp"

namespace ft
{

template<typename Iterator>
class reverse_iterator
{

protected:

	Iterator current;

public:

	typedef Iterator													iterator_type;
	typedef	typename ft::iterator_traits<Iterator>::value_type			value_type;
	typedef	typename ft::iterator_traits<Iterator>::iterator_category	iterator_category;
	typedef typename ft::iterator_traits<Iterator>::difference_type		difference_type;
	typedef typename ft::iterator_traits<Iterator>::pointer				pointer;
	typedef typename ft::iterator_traits<Iterator>::reference			reference;

	reverse_iterator(): current() { }

	explicit reverse_iterator(iterator_type x): current(x) { }

	reverse_iterator(const reverse_iterator& x): current(x.current) { }

	template<typename Iter>
	reverse_iterator(const reverse_iterator<Iter>& x): current(x.base()) { }

	iterator_type base() const { return this->current; }

	reference operator*() const
	{
		Iterator tmp = this->current;
		return *--tmp;
	}

	pointer operator->() const
	{
		Iterator tmp = this->current;
		--tmp;
		return this->pointerDispatch(tmp);
	}

	reverse_iterator& operator++()
	{
		--(this->current);
		return *this;
	}

	reverse_iterator operator++(int)
	{
		reverse_iterator tmp = *this;
		--(this->current);
		return tmp;
	}

	reverse_iterator& operator--()
	{
		++(this->current);
		return *this;
	}

	reverse_iterator operator--(int)
	{
		reverse_iterator tmp = *this;
		++(this->current);
		return tmp;
	}

	reverse_iterator operator+(difference_type n) const
	{
		return reverse_iterator(this->current - n);
	}

	reverse_iterator& operator+=(difference_type n)
	{
		this->current -= n;
		return *this;
	}

	reverse_iterator operator-(difference_type n) const
	{
		return reverse_iterator(this->current + n);
	}

	reverse_iterator& operator-=(difference_type n)
	{
		this->current += n;
		return *this;
	}

	reference operator[](difference_type n) const
	{
		return *(*this + n);
	}

	friend bool	operator==( const reverse_iterator& lhs,
			const reverse_iterator& rhs )
	{
		return lhs.current == rhs.current;
	}
	friend bool	operator!=( const reverse_iterator& lhs,
			const reverse_iterator& rhs )
	{
		return lhs.current != rhs.current;
	}

private:

	template<typename _Tp>
	static _Tp* pointerDispatch(_Tp* p) { return p; }

	template<typename _Tp>
	static pointer pointerDispatch(_Tp t) { return t.operator->(); }
};

}

#endif
