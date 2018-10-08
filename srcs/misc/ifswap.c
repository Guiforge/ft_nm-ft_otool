/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ifswap.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/24 14:00:16 by gpouyat           #+#    #+#             */
/*   Updated: 2018/10/08 12:35:47 by gpouyat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/misc.h"

/*
**	Swap number if is_swap === True
*/

uint16_t	ifswap16(t_arch *input, uint16_t x)
{
	if (input->is_swap)
		return (ft_swap_int16(x));
	return (x);
}

uint32_t	ifswap32(t_arch *input, uint32_t x)
{
	if (input->is_swap)
		return (ft_swap_int32(x));
	return (x);
}

uint64_t	ifswap64(t_arch *input, uint64_t x)
{
	if (input->is_swap)
		return (ft_swap_int64(x));
	return (x);
}
