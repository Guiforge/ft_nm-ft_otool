/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_nlist.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/24 15:45:39 by gpouyat           #+#    #+#             */
/*   Updated: 2018/05/24 16:04:30 by gpouyat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "misc.h"

void swap_nlist(struct nlist *symbol)
{
	symbol->n_un.n_strx = ft_swapInt32(symbol->n_un.n_strx);
	symbol->n_desc = ft_swapInt16(symbol->n_desc);
	symbol->n_value = ft_swapInt32(symbol->n_value);
}

void swap_nlist_64(struct nlist_64 *symbol)
{
	symbol->n_un.n_strx = ft_swapInt32(symbol->n_un.n_strx);
	symbol->n_desc = ft_swapInt16(symbol->n_desc);
	symbol->n_value = ft_swapInt64(symbol->n_value);
}