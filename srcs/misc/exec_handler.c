/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/30 19:07:05 by gpouyat           #+#    #+#             */
/*   Updated: 2018/04/30 19:40:49 by gpouyat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mach-o/loader.h>
#include <mach-o/fat.h>
# include <mach-o/nlist.h>
# include <ar.h>
#include "misc.h"

static t_type_macho which_header(const t_macho_input input_file)
{
	uint32_t		magic;

	magic = get_header(input_file);
	if (magic == MH_MAGIC_64 || magic == MH_CIGAM_64)
		return (M_64);
	else if (magic == MH_MAGIC || magic == MH_CIGAM)
		return (M_32);
	else if (magic == FAT_MAGIC || magic == FAT_CIGAM)
		return (M_FAT);
	else if (secure_add(input_file, input_file.data, SARMAG) && !ft_strncmp(ARMAG, (char *)input_file.data, SARMAG))
		return (M_LIB);
	return (M_ERR);
}

int		exec_handler(t_handler_func funcs[], t_macho_input input_file)
{
	t_type_macho	type;
	int				index;

	index = -1;
	type = which_header(input_file);
	if (type == M_ERR)
		return (1);
	while (funcs[++index].type != M_END)
		if (funcs[++index].type == type)
			return (funcs[index].f(input_file));
	return (2);
}