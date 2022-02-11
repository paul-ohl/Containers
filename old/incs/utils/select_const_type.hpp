/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_const_type.hpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulohl <pohl@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 17:53:37 by paulohl           #+#    #+#             */
/*   Updated: 2021/12/09 18:01:24 by paulohl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SELECT_CONST_TYPE_HPP
#define SELECT_CONST_TYPE_HPP

namespace ft
{

    template <bool IsConst, typename NonConst, typename Const>
    struct select_const_type {};

    template <typename NonConst, typename Const>
    struct select_const_type<false, NonConst, Const>
    {
        typedef NonConst type;
    };

    template <typename NonConst, typename Const>
    struct select_const_type<true, NonConst, Const>
    {
        typedef Const type;
    };

}

#endif
