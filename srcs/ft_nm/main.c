/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/24 09:02:33 by gpouyat           #+#    #+#             */
/*   Updated: 2018/04/30 19:46:54 by gpouyat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "misc.h"
#include "libft.h"
#include "ft_nm.h"
#include <sys/mman.h>



//#define	MH_MAGIC	0xfeedface	/* the mach magic number */
//#define MH_CIGAM	0xcefaedfe	/* NXSwapInt(MH_MAGIC) */
//#define MH_MAGIC_64 0xfeedfacf /* the 64-bit mach magic number */
//#define MH_CIGAM_64 0xcffaedfe /* NXSwapInt(MH_MAGIC_64) */
//FAT_MAGIC, ARMAG
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

int main(int ac, const char **av)
{
	t_macho_input		input_file;
	t_handler_func handler_funcs[] =
{
	{M_32, NULL},
	{M_64, NULL},
	{M_FAT, NULL},
	{M_LIB, NULL},
	{M_END, NULL},
};
	if (intern_nm_parse_option(ac, av))
		return (1);
	map_file(PROGNAME, av[g_optind], &input_file);
	if (exec_handler(handler_funcs, input_file) != 0)
		ft_dprintf(STDERR_FILENO, "ERROR TYPE FILE\n");
	munmap((void *)input_file.data, input_file.length);
	//intern_nm_which_header((char *)av[1]);

}