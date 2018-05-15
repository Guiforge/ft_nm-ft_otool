/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_32.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/06 12:16:54 by gpouyat           #+#    #+#             */
/*   Updated: 2018/05/15 11:34:38 by gpouyat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "misc.h"
#include "libft.h"
#include "ft_nm.h"
#include <mach-o/nlist.h>

static t_list		*create_sym(t_macho_input input, char *string_table, struct nlist sym_table)
{
	t_sym	*elem_sym;
	t_list	*elem;

	if (!(elem_sym = (t_sym *)ft_memalloc(sizeof(t_sym))))
	{
		ft_dprintf(STDERR_FILENO, "ERROR MALLOC\n");
		return(NULL);
	}
	elem_sym->name = secure_string(input, string_table, sym_table.n_un.n_strx);
	elem_sym->value = sym_table.n_value;
	find_seg_sect_name(sym_table, elem_sym, input);
	elem = ft_lstnew(elem_sym, sizeof(t_sym));
	return (elem);
}

static t_list	*get_list_syms(struct symtab_command sym, t_macho_input input)
{
	t_list			*list;
	char			*string;
	struct nlist *array;
	int64_t		index;

	list = NULL;
	index = -1;	
	if (!(array = secure_add_mv(input, input.data, sym.symoff)))
	{
		ft_printf("%d - %s \n", __LINE__, __FILE__);
		print_error(input.path, ERR_UNDIFINED);
		return (NULL);
	}
	if (!(string = secure_add_mv(input, input.data, sym.stroff)))
	{
		ft_printf("%d - %s \n", __LINE__, __FILE__);
		print_error(input.path, ERR_UNDIFINED);
		return (NULL);
	}
	while (++index < sym.nsyms)
		ft_lstpush(&list, create_sym(input, string, array[index]));
	return(list);
}

int handler_32(t_macho_input input, void **list)
{
	struct mach_header header;
	struct	symtab_command	*sym;

	if (get_header_32(input, input.data, &header))
		return(return_error(input.path, ERR_INVALID, 2));
	input.ncmds = header.ncmds;
	if (!(input.lc = secure_add_mv(input, input.data, sizeof(struct mach_header))))
		return(return_error(input.path, ERR_INVALID, 2));
	sym = get_symtab_cmd(input);
	if (!sym)
		return (2);
	*list = get_list_syms(*sym, input);

	while (*list)
	{
		if (!(((t_sym *)(((t_list *)(*list))->content))->ntype & N_STAB))
			ft_printf("%#0llx -(%s, %s) %s\n", ((t_sym *)(((t_list *)(*list))->content))->value, ((t_sym *)(((t_list *)(*list))->content))->segname, ((t_sym *)(((t_list *)(*list))->content))->sectname, ((t_sym *)(((t_list *)(*list))->content))->name);
		*list = ((t_list *)(*list))->next;
	}
	
	return (0);
}