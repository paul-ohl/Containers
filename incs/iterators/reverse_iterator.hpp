/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pohl <pohl@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 17:41:10 by pohl              #+#    #+#             */
/*   Updated: 2022/02/03 17:54:49 by pohl             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REVERSE_ITERATOR_HPP
# define REVERSE_ITERATOR_HPP

template<typename Iterator>
class reverse_iterator
: public iterator<typename iterator_traits<Iterator>::iterator_category,
	typename iterator_traits<Iterator>::value_type,
	typename iterator_traits<Iterator>::difference_type,
	typename iterator_traits<Iterator>::pointer,
	typename iterator_traits<Iterator>::reference>
{

protected:

	Iterator current;

	typedef iterator_traits<Iterator>		traits_type;

public:

	typedef Iterator					iterator_type;
	typedef typename traits_type::difference_type	difference_type;
	typedef typename traits_type::pointer		pointer;
	typedef typename traits_type::reference		reference;

	reverse_iterator() : current() { }

	explicit reverse_iterator(iterator_type x) : current(x) { }

	reverse_iterator(const reverse_iterator& x) : current(x.current) { }

	template<typename _Iter>
		reverse_iterator(const reverse_iterator<_Iter>& x)
		: current(x.base()) { }

	iterator_type base() const { return current; }

	reference operator*() const
	{
		Iterator tmp = current;
		return *--tmp;
	}

	pointer operator->() const
	{
		Iterator tmp = current;
		--tmp;
		return pointerDispatch(tmp);
	}

	reverse_iterator& operator++()
	{
		--current;
		return *this;
	}

	reverse_iterator operator++(int)
	{
		reverse_iterator tmp = *this;
		--current;
		return tmp;
	}

	reverse_iterator& operator--()
	{
		++current;
		return *this;
	}

	reverse_iterator operator--(int)
	{
		reverse_iterator tmp = *this;
		++current;
		return tmp;
	}

	reverse_iterator operator+(difference_type n) const
	{
		return reverse_iterator(current - n);
	}

	reverse_iterator& operator+=(difference_type n)
	{
		current -= n;
		return *this;
	}

	reverse_iterator operator-(difference_type n) const
	{
		return reverse_iterator(current + n);
	}

	reverse_iterator& operator-=(difference_type n)
	{
		current += n;
		return *this;
	}

	reference operator[](difference_type n) const
	{
		return *(*this + n);
	}

private:

	template<typename _Tp>
	static _Tp* pointerDispatch(_Tp* p) { return p; }

	template<typename _Tp>
	static pointer pointerDispatch(_Tp t) { return t.operator->(); }
};

#endif
