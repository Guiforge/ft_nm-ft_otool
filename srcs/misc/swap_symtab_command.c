/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_symtab_command.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/24 15:02:40 by gpouyat           #+#    #+#             */
/*   Updated: 2018/10/08 12:49:06 by gpouyat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/misc.h"

void	swap_symtab_command(struct symtab_command *st)
{
	st->cmd = ft_swap_int32(st->cmd);
	st->cmdsize = ft_swap_int32(st->cmdsize);
	st->symoff = ft_swap_int32(st->symoff);
	st->nsyms = ft_swap_int32(st->nsyms);
	st->stroff = ft_swap_int32(st->stroff);
	st->strsize = ft_swap_int32(st->strsize);
}
