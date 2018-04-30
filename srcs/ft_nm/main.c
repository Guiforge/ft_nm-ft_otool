/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/24 09:02:33 by gpouyat           #+#    #+#             */
/*   Updated: 2018/04/30 18:55:23 by gpouyat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "misc.h"
#include "libft.h"
#include "ft_nm.h"

#include <mach-o/loader.h>
#include <mach-o/fat.h>
# include <mach-o/nlist.h>
# include <ar.h>
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

static void intern_nm_which_header(char *path)
{
	t_macho_input	input_file;
	uint32_t		magic = 0;


	map_file(PROGNAME, path, &input_file);
	if (secure_add(input_file, input_file.data, sizeof(uint32_t)))
		magic = *(uint32_t *)input_file.data;
	if (magic == MH_MAGIC_64 || magic == MH_CIGAM_64)
		ft_printf("64\n");
	else if (magic == MH_MAGIC || magic == MH_CIGAM)
		ft_printf("32\n");
	else if (magic == FAT_MAGIC || magic == FAT_CIGAM)
		ft_printf("FAT\n");
	else if (secure_add(input_file, input_file.data, SARMAG) && !ft_strncmp(ARMAG, (char *)input_file.data, SARMAG))
		ft_printf("LIB\n");
	else
		ft_printf("Autre?\n");
	//else if (magic == ARMAG)
	//	ft_printf("LIB\n");

	ft_printf("size:%d, data:%#x\n", input_file.length, input_file.data);
}

int main(int ac, const char **av)
{
	
	if (intern_nm_parse_option(ac, av))
		return (1);
	intern_nm_which_header((char *)av[1]);

}