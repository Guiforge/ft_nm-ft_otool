/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_header.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/30 19:19:41 by gpouyat           #+#    #+#             */
/*   Updated: 2018/04/30 19:31:23 by gpouyat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "misc.h"

uint32_t	get_header(const t_macho_input input_file)
{
	if (secure_add(input_file, input_file.data, sizeof(uint32_t)))
		return(*(uint32_t *)input_file.data);
	return (0);
}