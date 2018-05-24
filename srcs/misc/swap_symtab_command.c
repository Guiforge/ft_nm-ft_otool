/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_symtab_command.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/24 15:02:40 by gpouyat           #+#    #+#             */
/*   Updated: 2018/05/24 15:07:23 by gpouyat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "misc.h"

void	swap_symtab_command(struct symtab_command *st)
{
	st->cmd = ft_swapInt32(st->cmd);
	st->cmdsize = ft_swapInt32(st->cmdsize);
	st->symoff = ft_swapInt32(st->symoff);
	st->nsyms = ft_swapInt32(st->nsyms);
	st->stroff = ft_swapInt32(st->stroff);
	st->strsize = ft_swapInt32(st->strsize);
}