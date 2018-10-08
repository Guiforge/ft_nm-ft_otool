/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_64.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/06 12:16:54 by gpouyat           #+#    #+#             */
/*   Updated: 2018/10/08 16:58:01 by gpouyat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_nm.h"

static t_list	*create_sym_64(t_arch input, char *string_table,
													struct nlist_64 sym_table)
{
	t_sym	*elem_sym;
	t_list	*elem;

	if (input.is_swap)
		swap_nlist_64(&sym_table);
	if (!(elem_sym = (t_sym *)ft_secu_malloc_lvl(sizeof(t_sym),
													MALLOC_LVL_FILE_MACH_O)))
		return (return_error_null(__FILE__, PROGRAM, ERR_MALLOC));
	elem_sym->name = secure_string(input, string_table, sym_table.n_un.n_strx);
	elem_sym->value = sym_table.n_value;
	elem_sym->ntype = sym_table.n_type;
	elem_sym->arch = ARCH_64;
	if (find_seg_sect_name_64(sym_table, elem_sym, input))
	{
		ft_secu_free(elem_sym);
		return (NULL);
	}
	elem = ft_lstnew_secu(elem_sym, sizeof(t_sym), MALLOC_LVL_FILE_MACH_O);
	return (elem);
}

static int		loop_get_list_sym_64(t_arch *input, struct symtab_command sym,
										struct nlist_64 *array, char *string)
{
	int64_t		index;
	t_list		*new;
	t_list		*lst;

	lst = NULL;
	index = -1;
	while (++index < sym.nsyms)
	{
		new = create_sym_64(*input, string, array[index]);
		if (!new)
			return (1);
		ft_lstpush(&lst, new);
	}
	input->list = lst;
	return (0);
}

static t_list	*get_list_syms_64(struct symtab_command sym, t_arch input)
{
	char			*string;
	struct nlist_64	*array;

	if (input.is_swap)
		swap_symtab_command(&sym);
	if (!(array = secure_add_mv(input, input.data, sym.symoff)))
		return (return_error_null(input.path, PROGRAM, ERR_MALFORMED));
	if (!(string = secure_add_mv(input, input.data, sym.stroff)))
		return (return_error_null(input.path, PROGRAM, ERR_MALFORMED));
	if (!loop_get_list_sym_64(&input, sym, array, string))
		return (input.list);
	return (NULL);
}

int				handler_64(t_arch *input)
{
	struct mach_header_64	header;
	struct symtab_command	*sym;

	if (get_header_64(*input, input->data, &header))
		return (return_error(input->path, PROGRAM, ERR_INVALID, 2));
	input->ncmds = header.ncmds;
	input->cpu_type = header.cputype;
	input->cpu_subtype = header.cpusubtype;
	if (!(input->lc = secure_add_mv(*input, input->data,
											sizeof(struct mach_header_64))))
		return (return_error(input->path, PROGRAM, ERR_INVALID, 2));
	if (!(sym = get_symtab_cmd(*input)))
		return (1);
	input->list = get_list_syms_64(*sym, *input);
	if (!(input->list))
		return (1);
	sort_sym(&(input->list));
	print_nm(input);
	return (0);
}
