/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/15 19:23:18 by gpouyat           #+#    #+#             */
/*   Updated: 2018/06/26 11:22:39 by gpouyat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

const t_handler_func handler_funcs[] = {
	{M_32, &handler_32},
	{M_64, &handler_64},
	// {M_FAT, &handle_fat},
	// {M_LIB, &handle_lib},
	{M_END, NULL},
};

static t_nm_flags	flags = {
	False,
	False,
	False,
	(t_handler_func *)handler_funcs
};

t_nm_flags		*get_otool_flags()
{
	return (&flags);
}

int		intern_nm_parse_option(int ac, const char **av)
{
	int opt;

	while((opt = ft_getopt(ac, av, "ht")) != -1)
	{
		if (opt == 'h')
			return (1);
		if (opt == '?')
			return (1);
	}
	return (0);
}