/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/03 13:53:37 by gpouyat           #+#    #+#             */
/*   Updated: 2018/06/03 13:54:08 by gpouyat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

t_arch	*create_new_arch(t_list **lst_archs)
{
	t_arch	*new;

	new = (t_arch *)ft_memalloc(sizeof(t_arch));
	ft_lstpush_new(lst_archs, new, sizeof(t_arch));
	return (new);
}