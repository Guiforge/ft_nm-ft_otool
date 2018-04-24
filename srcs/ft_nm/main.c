/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/24 09:02:33 by gpouyat           #+#    #+#             */
/*   Updated: 2018/04/24 19:38:22 by gpouyat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "misc.h"
#include "libft.h"
#include "ft_nm.h"

#include <mach-o/loader.h>


int main(int ac, const char **av)
{
	t_macho_input	input_file;

	(void)ac;
	ft_putendl("I am nm");
	map_file(PROGNAME, av[1], &input_file);
	uint32_t magic = *(uint32_t *)secure_add(input_file, input_file.data, sizeof(uint32_t));
	if (magic == MH_MAGIC_64)
		ft_printf("64\n");
	ft_printf("size:%d, data:%#x\n", input_file.length, input_file.data);

}