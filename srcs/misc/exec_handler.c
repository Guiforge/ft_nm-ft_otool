/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/30 19:07:05 by gpouyat           #+#    #+#             */
/*   Updated: 2018/05/24 14:16:57 by gpouyat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mach-o/loader.h>
#include <mach-o/fat.h>
# include <mach-o/nlist.h>
# include <ar.h>
#include "misc.h"

static t_type_macho which_header(t_arch *arch)
{
	uint32_t		magic;

	magic = get_magic(arch);
	if (magic == MH_MAGIC_64 || magic == MH_CIGAM_64)
		return (M_64);
	else if (magic == MH_MAGIC || magic == MH_CIGAM)
		return (M_32);
	else if (magic == FAT_MAGIC || magic == FAT_CIGAM)
		return (M_FAT);
	else if (secure_add(*arch, arch->data, SARMAG) && !ft_strncmp(ARMAG, (char *)arch->data, SARMAG))
		return (M_LIB);
	return (M_ERR);
}

int		exec_handler(const t_handler_func funcs[], t_arch *arch)
{
	t_type_macho	type;
	int				index;

	index = -1;
	type = which_header(arch);
	if (type == M_ERR)
		return (1);
	ft_printf("TOPO: Magic = %x, swap = %d\n", arch->magic, arch->is_swap);
	//(void)funcs;
	while (funcs[++index].type != M_END)
		if (funcs[index].type == type)
			return (funcs[index].f(arch));
	return (2);
}