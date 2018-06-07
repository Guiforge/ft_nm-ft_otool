/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/07 17:52:55 by gpouyat           #+#    #+#             */
/*   Updated: 2018/06/07 18:21:26 by gpouyat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

static int cmp_alpha(t_list *lst_a, t_list *lst_b)
{
	t_sym	*a;
	t_sym	*b;
	int		ret;
	
	a = (t_sym *)(lst_a->content);
	b = (t_sym *)(lst_b->content);
	ret = ft_strcmp(a->name, b->name);
	if (!ret)
		return(a->value > b->value);
	return(ret);
}

void	sort_sym(t_list **lst_sym)
{
	if (get_nm_flags()->r)
	{
		printf("INVERSE\n");
		return ;
	}
	ft_lstsort(lst_sym, &cmp_alpha);
}