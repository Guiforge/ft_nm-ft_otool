/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_header.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/30 19:19:41 by gpouyat           #+#    #+#             */
/*   Updated: 2018/10/08 12:20:39 by gpouyat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/misc.h"

/*
** Get the magic number from data and set is_swap
*/

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
		return (*(uint32_t *)input->data);
	}
	return (0);
}

/*
** Get the mach_header from add and swap if is_swap == true, set header variable
*/

int			get_header_32(const t_arch input, const void *add,
													struct mach_header *header)
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

int			get_header_64(const t_arch input, void const *add,
												struct mach_header_64 *header)
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

int			get_header_fat(const t_arch input, void const *add,
													struct fat_header *header)
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

int			get_header_lib(const t_arch input, void const *add,
														struct ar_hdr *header)
{
	if (secure_add(input, add, sizeof(struct ar_hdr) + SARMAG))
	{
		*header = *(struct ar_hdr *)((void *)add + SARMAG);
		return (0);
	}
	return (1);
}
