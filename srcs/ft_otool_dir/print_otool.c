/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_otool.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/18 16:29:49 by gpouyat           #+#    #+#             */
/*   Updated: 2018/10/08 12:09:30 by gpouyat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

void print_number(char number[8], t_bool swap)
{
	int		index;

	if (!swap)
	{
		index = 0;
		while (index < 8)
		{
			ft_putnbr_base_fd_low(number[index], 16, STDOUT_FILENO);
			ft_putnbr_base_fd_low(number[index + 1], 16, STDOUT_FILENO);
			index +=2;
		}
	}
	else
	{
		index = 7;
		while (index > 0)
		{
			ft_putnbr_base_fd_low(number[index - 1], 16, STDOUT_FILENO);
			ft_putnbr_base_fd_low(number[index], 16, STDOUT_FILENO);
			index -=2;
		}
	}
}

void print_hex_space(char *start, uint16_t nb, t_bool swap)
{
	char number[8];
	uint16_t	i;
	int			k;

	ft_memset(number, 0, 8);
	i = 1;
	k = 0;
	while(i <= nb)
	{
		if (k == 8)
		{
			print_number(number, swap);
			k = 0;
		}
		number[k] = (0x000000f0 & (*(char *)start)) >> 4 ;
		number[k + 1] = (0x0000000f & (*(char *)start));
		if (i / 4 && !(i % 4) && i != 4)
			ft_putchar(' ');
		start++;
		i++;
		k += 2;
	}
	print_number(number, swap);
	ft_putchar(' ');
}

void print_hex(char *start, uint16_t nb, t_bool space, t_bool swap)
{
	uint16_t	i;

	if (space)
		return(print_hex_space(start, nb, swap));
	i = 1;
	while(i <= nb)
	{
		ft_putnbr_base_fd_low( (0x000000f0 & (*(char *)start)) >> 4 , 16, STDOUT_FILENO);
		ft_putnbr_base_fd_low( (0x0000000f & (*(char *)start)), 16, STDOUT_FILENO);
		if (!space || ( i / 4 && !(i % 4)))
			ft_putchar(' ');
		start++;
		i++;
	}
}

t_bool	print_cpu_type(t_arch *input)
{
	const char	*name;

	if (!get_otool_flags()->print_arch)
		return (True);
	name = get_arch_info_from_cpu_type(input->cpu_type, input->cpu_subtype).name;
	if (name && !ft_strcmp(name, GET_ARCH))
	{
		ft_printf("%s:\n", input->path);
		return (False);
	}
	if (!name)
	{
		ft_printf("%s:\n", input->path);
		return (False);
	}
	ft_printf("%s (architecture %s):\n", input->path, name);
	return (False);
}
