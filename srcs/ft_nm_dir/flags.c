/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/30 11:24:59 by gpouyat           #+#    #+#             */
/*   Updated: 2018/10/08 17:59:57 by gpouyat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_nm.h"

static const t_handler_func	g_handler_funcs[] = {
	{M_32, &handler_32},
	{M_64, &handler_64},
	{M_FAT, &handle_fat},
	{M_LIB, &handle_lib},
	{M_END, NULL},
};

static t_nm_flags			g_flags = {
	False,
	False,
	False,
	False,
	False,
	False,
	False,
	False,
	False,
	False,
	False,
	(t_handler_func *)g_handler_funcs
};

t_nm_flags					*get_nm_flags(void)
{
	return (&g_flags);
}

void						simple_option(char opt)
{
	if (opt == 'g')
		g_flags.g = True;
	else if (opt == 'A')
		g_flags.a_up = True;
	else if (opt == 'n')
		g_flags.n = True;
	else if (opt == 'r')
		g_flags.r = True;
	else if (opt == 'm')
		g_flags.m = True;
	else if (opt == 'j')
		g_flags.j = True;
	else if (opt == 'U')
		g_flags.u_up = True;
	else if (opt == 'p')
	{
		g_flags.n = False;
		g_flags.p = True;
	}
	else if (opt == 'u')
	{
		g_flags.u = True;
		g_flags.u_up = False;
		g_flags.a = False;
	}
}

int							intern_nm_parse_option(int ac, const char **av)
{
	int		opt;

	while ((opt = ft_getopt(ac, av, "hagAnpruUmj")) != -1)
	{
		simple_option(opt);
		if (opt == 'a')
		{
			g_flags.a = True;
			g_flags.u = False;
			g_flags.u_up = False;
		}
		if (opt == 'h')
			return (1);
		if (opt == '?')
			return (1);
	}
	return (0);
}
