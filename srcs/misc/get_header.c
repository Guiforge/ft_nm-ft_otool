/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_header.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/30 19:19:41 by gpouyat           #+#    #+#             */
/*   Updated: 2018/05/08 15:35:58 by gpouyat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "misc.h"


uint32_t	get_magic(t_macho_input input_file)
{
	if (secure_add(input_file, input_file.data, sizeof(uint32_t)))
	{
		input_file.magic = (*(uint32_t *)input_file.data);
		return(*(uint32_t *)input_file.data);
	}
	return (0);
}

int			get_header_32(const t_macho_input input_file, const void *add, struct mach_header *header)
{
	if (secure_add(input_file, add, sizeof(struct mach_header)))
	{
		*header = *(struct mach_header *)add;
		return (0);
	}
	return (1);
}

int			get_header_64(const t_macho_input input_file, void const *add, struct mach_header_64 *header)
{
	if (secure_add(input_file, add, sizeof(struct mach_header_64)))
	{
		*header = *(struct mach_header_64 *)add;
		return (0);
	}
	return (1);
}

int			get_header_fat(const t_macho_input input_file, void const *add, struct fat_header *header)
{
	if (secure_add(input_file, add, sizeof(struct mach_header_64)))
	{
		*header = *(struct fat_header *)add;
		return (0);
	}
	return (1);
}

int			get_header_lib(const t_macho_input input_file, void const *add, struct ar_hdr *header)
{
	if (secure_add(input_file, add, sizeof(struct mach_header_64)))
	{
		*header = *(struct ar_hdr *)add;
		return (0);
	}
	return (1);
}