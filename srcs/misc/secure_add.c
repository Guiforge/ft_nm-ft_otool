/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   secure_add.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/24 19:03:50 by gpouyat           #+#    #+#             */
/*   Updated: 2018/04/24 19:14:43 by gpouyat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "misc.h"

void	*secure_add(t_macho_input input, const void *start_add, size_t length)
{
	void	*end_data_add;
	void	*goal_add;

	end_data_add = (void *)input.data + input.length;
	goal_add = (void *)start_add + length;
	if (goal_add > end_data_add)
	{
		ft_dprintf(STDERR_FILENO, "Something is Wrong \n"); // TODO: remove
		return (NULL);
	}
	return ((void *)start_add);
}