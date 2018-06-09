/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/07 17:52:55 by gpouyat           #+#    #+#             */
/*   Updated: 2018/06/09 21:46:23 by gpouyat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

static t_bool cmp_alpha(t_list *lst_a, t_list *lst_b)
{
	t_sym		*a;
	t_sym			*b;
	int	ret;
	
	a = (t_sym *)(lst_a->content);
	b = (t_sym *)(lst_b->content);
	ret = ft_strcmp(a->name, b->name);
	if (!ret || ret == -1)
		return(a->value < b->value);
	return((t_bool)ret);
}

static t_bool cmp_num(t_list *lst_a, t_list *lst_b)
{
	t_sym			*a;
	t_sym			*b;
	int				ret;
	
	a = (t_sym *)(lst_a->content);
	b = (t_sym *)(lst_b->content);
	ret = a->value < b->value;
	if (!ret)
		return((t_bool)ft_strcmp(a->name, b->name));
	return((t_bool)ret);
}

void	sort_sym(t_list **lst_sym)
{
	if (!get_nm_flags()->p)
	{
		if (get_nm_flags()->n)
			ft_lstsort(lst_sym, &cmp_num);
		else
			ft_lstsort(lst_sym, &cmp_alpha);
	}
	if (get_nm_flags()->r)
		ft_lstrev(lst_sym);
}