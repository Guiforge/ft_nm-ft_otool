/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/24 09:02:33 by gpouyat           #+#    #+#             */
/*   Updated: 2018/06/12 09:06:14 by gpouyat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_nm.h"
#include <sys/mman.h>
# include <ar.h>
#include <mach-o/ranlib.h>

extern int g_optind;

static int		intern_nm_help()
{
	ft_printf("This is beautiful Help\n");
	return (1);
}


static int one_file(const char *path, int print)
{
	t_arch		arch;
	int					ret;
	t_handler_func *handler_funcs;

	handler_funcs = get_nm_flags()->funcs;
	if (map_file(PROGNAME, path, &arch) != 0)
		return (1);
	if (print && which_header(&arch) != M_FAT && which_header(&arch) != M_LIB)
		ft_printf("\n%s:\n", path);
	t_list	*list;
	list = NULL;
	get_nm_flags()->print_arch = False;
	ret = exec_handler(handler_funcs, &arch);
	if (ret == 2)
		print_error(arch.path, ERR_INVALID);
	munmap((void *)arch.data, arch.length);
	ft_secu_free_lvl(MALLOC_LVL_FILE_MACH_O);
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