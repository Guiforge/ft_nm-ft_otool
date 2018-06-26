/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_32.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/23 09:33:20 by gpouyat           #+#    #+#             */
/*   Updated: 2018/06/26 12:49:15 by gpouyat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

static void print_32(t_arch *input, void *start, struct section sect)
{
	uint32_t	index;
	uint16_t	nb_print;
	t_bool		swap;
	t_bool		space;

	index = 0;
	swap = !input->is_swap && GET_ENDIAN == LITTLE;
	space = !(input->cpu_type == CPU_TYPE_I386 || input->cpu_type == CPU_TYPE_X86_64);
	ft_printf("Contents of (%s,%s) section\n", SEG_TEXT, SECT_TEXT);
	while(index < sect.size)
	{
		ft_printf("%08llx	", sect.addr + index);
		nb_print = (sect.size - index) <= 16 ? (sect.size - index) : 16;
		print_hex(start + index, nb_print, space, swap);
		ft_putchar('\n');
		index = index + 16;
	}
}

int handler_32(t_arch *input)
{
	struct mach_header	header;
	struct section		sect;
	void				*start;

	if (get_header_32(*input, input->data, &header))
		return(return_error(input->path, PROGRAM, ERR_INVALID, 2));
	input->ncmds = header.ncmds;
	input->cpu_type = header.cputype;
	input->cpu_subtype = header.cpusubtype;
	if (!(input->lc = secure_add_mv(*input, input->data, sizeof(struct mach_header))))
		return(return_error(input->path, PROGRAM, ERR_INVALID, 2));
	if (!(start = go_text_32(input, &sect)))
		return(1);
	if (secure_add(*input, start, sect.size))
	{
		print_cpu_type(input);
		print_32(input, start, sect);
	}
	else
		return(return_error(input->path, PROGRAM, ERR_MALFORMED, 1));
	return(0);
}