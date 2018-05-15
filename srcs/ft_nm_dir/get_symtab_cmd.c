/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_symtab_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/15 11:27:46 by gpouyat           #+#    #+#             */
/*   Updated: 2018/05/15 11:28:38 by gpouyat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

struct symtab_command	*get_symtab_cmd(t_macho_input input)
{
	uint32_t				index;
	struct	symtab_command	*sym;
	struct	load_command	*lc;

	lc = input.lc;
	index = -1;
	while (++index < input.ncmds)
	{
		if (lc->cmd == LC_SYMTAB)
		{
			sym = (struct symtab_command *)lc;
			return (sym);
		}
		if (!(lc = secure_add_mv(input, lc, lc->cmdsize)))
		{
			print_error(input.path, ERR_MALFORMED);
			return (NULL);
		}
	}
	return (NULL);
}