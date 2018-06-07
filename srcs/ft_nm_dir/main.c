/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/24 09:02:33 by gpouyat           #+#    #+#             */
/*   Updated: 2018/06/07 16:54:38 by gpouyat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_nm.h"
#include <sys/mman.h>
# include <ar.h>
#include <mach-o/ranlib.h>

extern int g_optind;

static int fake_handler(t_arch *input)
{
	(void)input;	
	ft_putendl("FAKE HANDLE");
	return (0);
}

static int		intern_nm_help()
{
	ft_printf("This is beautiful Help\n");
	return (1);
}


static int one_file(const char *path, int print)
{
	t_arch		arch;
	int					ret;
	const t_handler_func handler_funcs[] = {
		{M_32, &handler_32},
		{M_64, &handler_64},
		{M_FAT, &handle_fat},
		{M_LIB, &handle_lib},
		{M_END, &fake_handler},
	};

	if (map_file(PROGNAME, path, &arch) != 0)
		return (1);
	if (print && which_header(&arch) != M_FAT && which_header(&arch) != M_LIB)
		ft_printf("\n%s:\n", path);
	t_list	*list;
	list = NULL;
	get_nm_flags()->print_arch = False;
	ret = exec_handler(handler_funcs, &arch);
	munmap((void *)arch.data, arch.length);
	return (ret);
}

static int loop_files(const char *paths[])
{
	int		index;
	int		ret;

	index = -1;
	ret = 0;
	while (paths[++index])
	{
		if (one_file(paths[index], 1) !=0)
			ret = 1;
	}
	return(ret);
}

int main(int ac, const char **av)
{
	if (intern_nm_parse_option(ac, av))
		return (intern_nm_help());
	if (ac > g_optind + 1)
		return (loop_files(&av[g_optind]));
	else if (av[g_optind])
		return (one_file(av[g_optind], 0));
	return (one_file("./a.out", 0));
}