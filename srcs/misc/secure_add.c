/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   secure_add.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/24 19:03:50 by gpouyat           #+#    #+#             */
/*   Updated: 2018/04/30 18:56:23 by gpouyat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "misc.h"

void	*secure_add(t_macho_input input, const void *start_add, size_t length)
{
	uint8_t start = (uint8_t *) start_add - (uint8_t *) input.data;
	if (start + length >= input.length)
		return (NULL);
	return ((void *)start_add);
}