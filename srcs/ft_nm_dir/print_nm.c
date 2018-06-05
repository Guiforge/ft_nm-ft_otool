/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_nm.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/30 11:19:00 by gpouyat           #+#    #+#             */
/*   Updated: 2018/06/01 09:42:12 by gpouyat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

static	t_bool is_print_nm(t_sym sym)
{
	if (get_nm_flags()->a)
		return (True);
	if (get_nm_flags()->u && !ft_strchr("uU", get_char_type(sym)))
		return (False);
	if (get_nm_flags()->U && ft_strchr("uU", get_char_type(sym)))
		return (False);
	if (get_nm_flags()->g && sym.ntype & N_EXT)
		return (False);
	if ((sym.ntype & N_STAB))
		return (False);
	return (True);
}


static void	print_path(t_arch *input)
{
	ft_printf("%s: ", input->path);
}

static t_bool	print_cpu_type(t_arch *input)
{
	const char	*name;

	name = getArchInfoFromCpuType(input->cpu_type, input->cpu_subtype).name;
	if (!name)
	{
		ft_putchar_fd('\n', STDERR_FILENO);
		print_error(input->path, ERR_MALFORMED);
		return (True);
	}
	ft_printf("\n%s (for architecture %s):\n", input->path, name);
	return (False);
}

void	print_nm(t_arch *input)
{
	t_sym	sym;
	t_list *lst;

	if (get_nm_flags()->print_arch && print_cpu_type(input))
		return ;
		
	lst = input->list;
	while (lst)
	{
		sym = *(t_sym *)lst->content;
		if (is_print_nm(sym))
		{
			if (get_nm_flags()->A)
				print_path(input);
			if (!get_nm_flags()->j && !get_nm_flags()->u)
			{
				print_value(sym);
				if (!get_nm_flags()->m)
					ft_printf(" %c ", get_char_type(sym));
				if (sym.ntype & N_STAB)
					ft_putstr(" DEBUG SYMBOL ");
				else if (get_nm_flags()->m)
					print_m(sym);
			}
			if (sym.name)
				ft_putstr(sym.name);
			else
				ft_putstr("bad string index");
			ft_putchar('\n');
		}
		lst = lst->next;
	}
}