/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   go_text_32.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/15 21:20:48 by gpouyat           #+#    #+#             */
/*   Updated: 2018/10/08 13:52:36 by gpouyat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_otool.h"

static void		*go_lc_text_32(t_arch input)
{
	uint32_t				index;
	struct load_command		*lc;
	char					cmp[16];

	lc = input.lc;
	(void)cmp;
	ft_memset(cmp, 0, 16);
	index = -1;
	while (++index < input.ncmds)
	{
		if (ifswap32(&input, lc->cmd) == LC_SEGMENT)
		{
			if (!secure_add(input, lc, sizeof(struct segment_command)))
				return (return_error_null(input.path, PROGRAM, ERR_MALFORMED));
			if (!ft_strncmp(
				((struct segment_command *)lc)->segname, SEG_TEXT, 16) ||
				!ft_memcmp(((struct segment_command_64 *)lc)->segname, cmp, 16))
				return (lc);
		}
		if (!(lc = secure_add_mv(input, lc, ifswap32(&input, lc->cmdsize))))
			break ;
	}
	print_error(input.path, PROGRAM, ERR_MALFORMED);
	return (NULL);
}

static void		*go_sect_text_32(t_arch input, void *offset, uint32_t nb)
{
	uint32_t	index;

	if (!secure_add(input, offset, sizeof(struct section)))
		return (return_error_null(input.path, PROGRAM, ERR_MALFORMED));
	index = -1;
	while (++index < nb)
	{
		if (!secure_add(input, offset, sizeof(struct section)))
			return (return_error_null(input.path, PROGRAM, ERR_MALFORMED));
		if (!ft_strncmp(((struct section *)offset)->sectname, SECT_TEXT, 16))
			return (offset);
		if (!(offset = secure_add_mv(input, offset, sizeof(struct section))))
			break ;
	}
	print_error(input.path, PROGRAM, ERR_MALFORMED);
	return (NULL);
}

void			*go_text_32(t_arch *input, struct section *sect)
{
	void		*offset;

	if (!(offset = go_lc_text_32(*input)))
		return (NULL);
	if (!secure_add_mv(*input, offset, sizeof(struct segment_command)))
		return (return_error_null(input->path, PROGRAM, ERR_MALFORMED));
	offset = go_sect_text_32(*input, offset + sizeof(struct segment_command),
									((struct segment_command *)offset)->nsects);
	if (!offset)
		return (return_error_null(input->path, PROGRAM, ERR_MALFORMED));
	*sect = *((struct section *)offset);
	if (input->is_swap)
		swap_section(sect, 1);
	if (!(offset = secure_add_mv(*input, input->data, sect->offset)))
		return (return_error_null(input->path, PROGRAM, ERR_MALFORMED));
	return (offset);
}
