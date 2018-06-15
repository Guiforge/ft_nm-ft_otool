/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/24 09:02:33 by gpouyat           #+#    #+#             */
/*   Updated: 2018/06/15 21:17:45 by gpouyat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_otool.h"
#include <sys/mman.h>

extern int g_optind;

int handler_32(t_arch *input)
{
	struct mach_header header;
	// struct	symtab_command	*sym;

	if (get_header_32(*input, input->data, &header))
		return(return_error(input->path, PROGRAM, ERR_INVALID, 2));
	input->ncmds = header.ncmds;
	input->cpu_type = header.cputype;
	input->cpu_subtype = header.cpusubtype;
	if (!(input->lc = secure_add_mv(*input, input->data, sizeof(struct mach_header))))
		return(return_error(input->path, PROGRAM, ERR_INVALID, 2));
	return(0);
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
	t_handler_func *handler_funcs;

	handler_funcs = get_otool_flags()->funcs;
	if (map_file(PROGRAM, path, &arch) != 0)
		return (1);
	if (print && which_header(&arch) != M_FAT && which_header(&arch) != M_LIB)
		ft_printf("\n%s:\n", path);
	t_list	*list;
	list = NULL;
	get_otool_flags()->print_arch = False;
	ret = exec_handler(handler_funcs, &arch);
	if (ret == 2)
		ft_printf("EROOR A CHANGER");//print_error(arch.path, PROGRAM, ERR_INVALID);
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