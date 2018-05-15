/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   secure_add.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/24 19:03:50 by gpouyat           #+#    #+#             */
/*   Updated: 2018/05/15 10:58:58 by gpouyat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "misc.h"

void	*secure_add(t_macho_input input, const void *start_add, size_t length)
{
	int64_t		diff;	
	uint8_t		start;
	
	start = (uint8_t *) start_add - (uint8_t *) input.data;
	diff = (input.data + input.length) - (start_add + length);
	if (start + length > input.length || diff <= 0)
		return (NULL);
	return ((void *)start_add);
}

void	*secure_add_mv(t_macho_input input, const void *start_add, size_t length)
{
	if (secure_add(input, start_add, length))
		return ((void *)start_add + length);
	return (NULL);
}

char		*secure_string(t_macho_input input, char *string_table, uint32_t offset)
{
	char	*ret;
	size_t		i;

	i = 0;
	if (!(ret = secure_add_mv(input, (void *)string_table, offset)))
		return (NULL);

	while(ret[i++])
		if (!secure_add(input, (void *)ret, i))
			return (NULL);
	return (ret);
}