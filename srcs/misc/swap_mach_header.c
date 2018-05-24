/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_mach_header.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/24 14:11:23 by gpouyat           #+#    #+#             */
/*   Updated: 2018/05/24 14:14:14 by gpouyat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "misc.h"

void	swap_mach_header(struct mach_header *mh)
{
	mh->magic = ft_swapInt32(mh->magic);
	mh->cputype = ft_swapInt32(mh->cputype);
	mh->cpusubtype = ft_swapInt32(mh->cpusubtype);
	mh->filetype = ft_swapInt32(mh->filetype);
	mh->ncmds = ft_swapInt32(mh->ncmds);
	mh->sizeofcmds = ft_swapInt32(mh->sizeofcmds);
	mh->flags = ft_swapInt32(mh->flags);
}

void	swap_mach_header_64(struct mach_header_64 *mh)
{
	mh->magic = ft_swapInt32(mh->magic);
	mh->cputype = ft_swapInt32(mh->cputype);
	mh->cpusubtype = ft_swapInt32(mh->cpusubtype);
	mh->filetype = ft_swapInt32(mh->filetype);
	mh->ncmds = ft_swapInt32(mh->ncmds);
	mh->sizeofcmds = ft_swapInt32(mh->sizeofcmds);
	mh->flags = ft_swapInt32(mh->flags);
	mh->reserved = ft_swapInt32(mh->reserved);
}