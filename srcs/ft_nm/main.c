/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/24 09:02:33 by gpouyat           #+#    #+#             */
/*   Updated: 2018/04/30 20:46:11 by gpouyat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "misc.h"
#include "libft.h"
#include "ft_nm.h"
#include <sys/mman.h>

/*  swapint32  ((__uint32_t)((((__uint32_t)(x) & 0xff000000) >> 24) | \
                (((__uint32_t)(x) & 0x00ff0000) >>  8) | \
                (((__uint32_t)(x) & 0x0000ff00) <<  8) | \
                (((__uint32_t)(x) & 0x000000ff) << 24))):*/
extern int g_optind;

static int		intern_nm_help()
{
	ft_printf("This is beautiful Help\n");
	return (1);
}

static int		intern_nm_parse_option(int ac, const char **av)
{
	int opt;
	while((opt = ft_getopt(ac, av, "h")) != -1)
	{
		if (opt == 'h')
			return (intern_nm_help());
		if (opt == '?')
			return (1);
	}
	return (0);
}

static int fake_handler(t_macho_input input)
{
	(void)input;
	ft_printf("Fake Handler\n");
	return (0);
}

static int one_file(const char *path)
{
	t_macho_input		input_file;
	const t_handler_func handler_funcs[] = {
		{M_32, &fake_handler},
		{M_64, &fake_handler},
		{M_FAT, &fake_handler},
		{M_LIB, &fake_handler},
		{M_END, &fake_handler},
	};

	if (map_file(PROGNAME, path, &input_file) != 0)
		return (1);
	if (exec_handler(handler_funcs, input_file) != 0)
		ft_dprintf(STDERR_FILENO, "ERROR TYPE FILE\n");
	munmap((void *)input_file.data, input_file.length);
	return (0);
}

static int loop_files(const char *paths[])
{
	int		index;
	int		ret;

	index = -1;
	ret = 0;
	while (paths[++index])
	{
		ft_printf("\n%s:\n", paths[index]);
		if (one_file(paths[index]) !=0)
			ret = 1;
	}
	return(ret);
}

int main(int ac, const char **av)
{
	if (intern_nm_parse_option(ac, av))
		return (1);
	if (ac > g_optind + 1)
		return (loop_files(&av[g_optind]));
	else if (av[g_optind])
		return (one_file(av[g_optind]));
	return (one_file("./a.out"));
}