/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 17:45:09 by gpouyat           #+#    #+#             */
/*   Updated: 2018/10/02 13:09:23 by gpouyat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

char	if_upper(char c, uint8_t ntype)
{
	if (ntype & N_EXT)
		return (ft_toupper(c));
	if (c == 'c' || c == 'u')
		return ('?');	
	return (c);
}

static char find_sect_type(t_sym sym)
{
	if (ft_strequ(sym.segname, "__TEXT") && ft_strequ(sym.sectname, "__text"))
		return(if_upper('t', sym.ntype));
	if (ft_strequ(sym.segname, "__DATA") && ft_strequ(sym.sectname, "__data"))
		return(if_upper('d', sym.ntype));
	if (ft_strequ(sym.segname, "__DATA") && ft_strequ(sym.sectname, "__bss"))
		return(if_upper('b', sym.ntype));
	return (if_upper('s', sym.ntype));
}

char get_char_type(t_sym sym)
{
	int		type;

	type = sym.ntype & N_TYPE;
	if ((type == N_UNDF || type == N_PBUD) && sym.nsect == NO_SECT)
	{
		if (sym.value && type != N_PBUD)
			return(if_upper('c', sym.ntype));
		return(if_upper('u', sym.ntype));
	}
	else if (type == N_ABS)
		return(if_upper('a', sym.ntype));
	else if (type == N_SECT && sym.nsect != NO_SECT && sym.nsect <= MAX_SECT)
		return(find_sect_type(sym));
	else if (type == N_INDR)
		return(if_upper('i', sym.ntype));
	return (if_upper('?', sym.ntype));
}

void print_value(t_sym sym, char c)
{
	if (sym.arch == ARCH_64)
	{
		if ((!(sym.ntype & N_EXT) || sym.value || (sym.ntype & N_TYPE) == N_SECT || c == 'A'))
			ft_printf("%016llx", sym.value);
		else
			ft_putstr("                ");
	}
	else
	{
		if ((!(sym.ntype & N_EXT) || sym.value || (sym.ntype & N_TYPE) == N_SECT || c == 'A' ))
			ft_printf("%08llx", sym.value);
		else
			ft_putstr("        ");
	}
}

void	print_m(t_sym sym)
{
	char	c;

	c = ft_toupper(get_char_type(sym));
	if ((sym.ntype & N_TYPE) == N_UNDF && sym.value)
		ft_putstr(" (common)");
	else if (c == 'U')
		ft_putstr(" (undefined)");
	else if (c == 'C')
		ft_putstr(" (common)");
	else if (c == 'A')
		ft_putstr(" (absolute)");
	else if (c == 'I')
		ft_putstr(" (indirect)");
	else if ((sym.ntype & N_TYPE) == N_SECT)
	{	if (sym.sectname[0] && sym.segname[0])
			ft_printf(" (%s,%s)", sym.segname, sym.sectname);
		else
			ft_putstr(" (?,?)");
	}
	else
		ft_putstr(" (?)");	
	if (sym.ntype & N_EXT)
		ft_putstr(" external ");
	else if (sym.ntype & N_PEXT)
		ft_putstr(" private external ");
	else
		ft_putstr(" non-external ");
}
