/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_64.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/06 12:16:54 by gpouyat           #+#    #+#             */
/*   Updated: 2018/05/29 11:53:15 by gpouyat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "misc.h"
#include "libft.h"
#include "ft_nm.h"
#include <mach-o/nlist.h>

static t_list		*create_sym_64(t_arch input, char *string_table, struct nlist_64 sym_table)
{
	t_sym	*elem_sym;
	t_list	*elem;

	if (input.is_swap)
		swap_nlist_64(&sym_table);
	if (!(elem_sym = (t_sym *)ft_memalloc(sizeof(t_sym))))
	{
		ft_dprintf(STDERR_FILENO, "ERROR MALLOC\n");
		return(NULL);
	}
	elem_sym->name = secure_string(input, string_table, sym_table.n_un.n_strx);
	elem_sym->value = sym_table.n_value;
	if (find_seg_sect_name_64(sym_table, elem_sym, input))
	{
		free(elem_sym);
		return (NULL);
	}
	elem = ft_lstnew(elem_sym, sizeof(t_sym));
	return (elem);
}

static int	loop_get_list_sym_64(t_arch input, struct symtab_command sym, struct nlist_64 *array, char *string)
{
	int64_t		index;
	t_list		*new;

	index = -1;
	while (++index < sym.nsyms)
	{
		new = create_sym_64(input, string, array[index]);
		if (!new)
		{
			/*freeALL*/
			return (1);
		}
		ft_lstpush(&(input.list), new);
	}
	return (0);
}

static t_list	*get_list_syms_64(struct symtab_command sym, t_arch input)
{
	char			*string;
	struct nlist_64 *array;

	if (input.is_swap)
		swap_symtab_command(&sym);
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
	if (!loop_get_list_sym_64(input, sym, array, string))
		return(input.list);
	return (NULL);
}

int handler_64(t_arch *input)
{
	struct mach_header_64 header;
	struct	symtab_command	*sym;

	if (get_header_64(*input, input->data, &header))
		return(return_error(input->path, ERR_INVALID, 2));
	ft_printf("HEADER: %x, %d\n", header.magic, header.ncmds);
	input->ncmds = header.ncmds;
	if (!(input->lc = secure_add_mv(*input, input->data, sizeof(struct mach_header_64))))
		return(return_error(input->path, ERR_INVALID, 2));
	if (!(sym = get_symtab_cmd(*input)))
		return (1);
	input->list = get_list_syms_64(*sym, *input);
	if (!input->list)
		return (1);
	while (input->list)
	{
		if (!(((t_sym *)(((t_list *)(input->list))->content))->ntype & N_STAB))
			ft_printf("%#0llx -(%s, %s) %s\n", ((t_sym *)(((t_list *)(input->list))->content))->value, ((t_sym *)(((t_list *)(input->list))->content))->segname, ((t_sym *)(((t_list *)(input->list))->content))->sectname, ((t_sym *)(((t_list *)(input->list))->content))->name);
		input->list = ((t_list *)(input->list))->next;
	}
	
	return (0);
}