/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_symtab_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/15 11:27:46 by gpouyat           #+#    #+#             */
/*   Updated: 2018/10/08 16:13:29 by gpouyat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_nm.h"

struct symtab_command	*get_symtab_cmd(t_arch input)
{
	uint32_t				index;
	struct load_command		*lc;

	lc = input.lc;
	index = -1;
	while (++index < input.ncmds)
	{
		if (ifswap32(&input, lc->cmd) == LC_SYMTAB)
			return ((struct symtab_command *)lc);
		if (!(lc = secure_add_mv(input, lc, ifswap32(&input, lc->cmdsize))))
			break ;
	}
	print_error(input.path, PROGRAM, ERR_MALFORMED);
	return (NULL);
}
