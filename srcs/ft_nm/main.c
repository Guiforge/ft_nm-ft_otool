/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/24 09:02:33 by gpouyat           #+#    #+#             */
/*   Updated: 2018/04/29 20:24:31 by gpouyat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "misc.h"
#include "libft.h"
#include "ft_nm.h"

#include <mach-o/loader.h>

extern int g_optind;

static int		intern_nm_help()
{
	ft_printf("This is beautiful Help\n");
	return (1);
}

static int		intern_nm_parse_option(int ac, const char **av)
{
	int opt;

	while((opt = ft_getopt(ac, av, "ah")) != -1)
	{
		if (opt == 'h')
			return (intern_nm_help());
		if (opt == '?')
			return (1);
	}
	return (0);
}

int main(int ac, const char **av)
{
	t_macho_input	input_file;
	uint32_t		magic = 0;

	if (intern_nm_parse_option(ac, av))
		return (1);
	ft_putendl("I am nm");
	map_file(PROGNAME, av[1], &input_file);
	if (secure_add(input_file, input_file.data, sizeof(uint32_t)))
		magic = *(uint32_t *)input_file.data;
	if (magic == MH_MAGIC_64)
		ft_printf("64\n");
	ft_printf("size:%d, data:%#x\n", input_file.length, input_file.data);

}