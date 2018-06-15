/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_seg_sect_name.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/05 17:45:26 by gpouyat           #+#    #+#             */
/*   Updated: 2018/06/15 21:12:59 by gpouyat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"
#include <mach-o/nlist.h>

static int		copy_sect_seg_name_64(t_arch input, t_sym *elem_sym, struct segment_command_64 *segment, size_t index)
{
	struct section_64			*sect;
	
	if (!(sect = secure_add_mv(input, segment, sizeof(struct segment_command_64))))
		return (return_error(input.path,PROGRAM, ERR_UNDIFINED, 1));
	if (!(sect = secure_add_mv(input, sect, index * sizeof(struct section_64))))
		return (return_error(input.path,PROGRAM, ERR_UNDIFINED, 1));
	if (secure_add(input, sect->segname, 16))
		ft_memcpy(elem_sym->segname, sect->segname, 16);
	if (ifswap32(&input,segment->nsects) > 0 && secure_add(input, sect->sectname, 16))
		ft_memcpy(elem_sym->sectname, sect->sectname, 16);
	else
		ft_memcpy(elem_sym->sectname,"undefined\0", 10);
	return (0);
}

//Find segment, find section if there is section and copy n_type
int		find_seg_sect_name_64(struct nlist_64 symbol, t_sym *elem_sym, t_arch input)
{
	struct load_command			*lc;
	size_t				i;
	size_t				tot;

	i = 0;
	tot = 0;
	lc = input.lc;
	while (lc && i++ < input.ncmds)
	{
		if (ifswap32(&input, lc->cmd) == LC_SEGMENT_64)
		{
			if (tot + ifswap32(&input, ((struct segment_command_64 *)lc)->nsects) >= symbol.n_sect)
			{
				elem_sym->ntype = symbol.n_type;
				elem_sym->nsect =   symbol.n_sect;
				return (copy_sect_seg_name_64(input, elem_sym,((struct segment_command_64 *)lc), symbol.n_sect - tot - 1));
			}
			tot += ifswap32(&input, ((struct segment_command_64 *)lc)->nsects);
		}
		if (!(lc = secure_add_mv(input, lc, ifswap32(&input, lc->cmdsize))))
			return(return_error(input.path,PROGRAM, ERR_MALFORMED, 1));
	}
	return (0);
}

static int		copy_sect_seg_name(t_arch input, t_sym *elem_sym, struct segment_command *segment, size_t index)
{
	struct section			*sect;
	
	if (!(sect = secure_add_mv(input, segment, sizeof(struct segment_command))))
		return (return_error(input.path,PROGRAM, ERR_UNDIFINED, 1));
	if (!(sect = secure_add_mv(input, sect, index * sizeof(struct section))))
		return (return_error(input.path,PROGRAM, ERR_UNDIFINED, 1));
	if (secure_add(input, sect->segname, 16))
		ft_memcpy(elem_sym->segname, sect->segname, 16);
	if (segment->nsects > 0 && secure_add(input, sect->sectname, 16))
		ft_memcpy(elem_sym->sectname, sect->sectname, 16);
	else
		ft_memcpy(elem_sym->sectname,"undefined\0", 10);
	return (0);
}

//Find segment, find section if there is section and copy n_type
int		find_seg_sect_name(struct nlist symbol, t_sym *elem_sym, t_arch input)
{
	struct load_command			*lc;
	size_t				i;
	size_t				tot;

	i = 0;
	tot = 0;
	lc = input.lc;
	while (i++ < input.ncmds)
	{
		if (ifswap32(&input, lc->cmd) == LC_SEGMENT)
		{
			if (tot + ifswap32(&input, ((struct segment_command *)lc)->nsects) >= symbol.n_sect)
			{
				elem_sym->ntype = symbol.n_type;
				elem_sym->nsect = symbol.n_sect;
				return (copy_sect_seg_name(input, elem_sym, ((struct segment_command *)lc), symbol.n_sect - tot - 1));
			}
			tot += ifswap32(&input, ((struct segment_command *)lc)->nsects);
		}
		if (!(lc = secure_add_mv(input, lc, ifswap32(&input, lc->cmdsize))))
			return_error(input.path,PROGRAM, ERR_MALFORMED, 1);
	}
	return (0);
}