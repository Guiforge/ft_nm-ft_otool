/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/30 11:24:59 by gpouyat           #+#    #+#             */
/*   Updated: 2018/06/09 20:00:07 by gpouyat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

const t_handler_func handler_funcs[] = {
	{M_32, &handler_32},
	{M_64, &handler_64},
	{M_FAT, &handle_fat},
	{M_LIB, &handle_lib},
	{M_END, NULL},
};

static t_nm_flags	flags = {
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
	(t_handler_func *)handler_funcs
};

t_nm_flags		*get_nm_flags()
{
	return (&flags);
}

void	simple_option(char opt)
{
	if (opt == 'g')
		flags.g = True;
	else if (opt == 'A')
		flags.A = True;
	else if (opt == 'n')
		flags.n = True;
	else if (opt == 'r')
		flags.r = True;
	else if (opt == 'm')
		flags.m = True;
	else if (opt == 'j')
		flags.j = True;
	else if (opt == 'U')
		flags.U = True;
}

int		intern_nm_parse_option(int ac, const char **av)
{
	int opt;

	while((opt = ft_getopt(ac, av, "hagAnpruUmj")) != -1)
	{
		simple_option(opt);
		if (opt == 'a')
		{
			flags.a = True;
			flags.u = False;
			flags.U = False;
		}
		if (opt == 'h')
			return (1);
		if (opt == 'u')
		{
			flags.u = True;
			flags.U = False;
			flags.a = False;
		}
		if (opt == 'p')
		{
			flags.n = False;
			flags.p = True;
		}
		if (opt == '?')
			return (1);
	}
	return (0);
}