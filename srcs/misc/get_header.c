/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_header.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/30 19:19:41 by gpouyat           #+#    #+#             */
/*   Updated: 2018/05/29 08:02:10 by gpouyat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "misc.h"


uint32_t	get_magic(t_arch *input)
{
	if (secure_add(*input, input->data, sizeof(uint32_t)))
	{
		input->magic = (*(uint32_t *)input->data);
		if (input->magic == MH_CIGAM || input->magic == MH_CIGAM_64
													|| input->magic == FAT_CIGAM)
			input->is_swap = True;
		else
			input->is_swap = False;
		return(*(uint32_t *)input->data);
	}
	return (0);
}

int			get_header_32(const t_arch input, const void *add, struct mach_header *header)
{
	if (secure_add(input, add, sizeof(struct mach_header)))
	{
		*header = *(struct mach_header *)add;
		if (input.is_swap)
			swap_mach_header(header);
		return (0);
	}
	return (1);
}

int			get_header_64(const t_arch input, void const *add, struct mach_header_64 *header)
{
	if (secure_add(input, add, sizeof(struct mach_header_64)))
	{
		*header = *(struct mach_header_64 *)add;
		if (input.is_swap)
			swap_mach_header_64(header);
		return (0);
	}
	return (1);
}

int			get_header_fat(const t_arch input, void const *add, struct fat_header *header)
{
	if (secure_add(input, add, sizeof(struct mach_header_64)))
	{
		*header = *(struct fat_header *)add;
		if (input.is_swap)
			swap_fat_header(header);
		return (0);
	}
	return (1);
}

int			get_header_lib(const t_arch input, void const *add, struct ar_hdr *header)
{
	if (secure_add(input, add, sizeof(struct mach_header_64)))
	{
		*header = *(struct ar_hdr *)add;
		return (0);
	}
	return (1);
}