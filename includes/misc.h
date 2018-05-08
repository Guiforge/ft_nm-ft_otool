/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 22:52:36 by gpouyat           #+#    #+#             */
/*   Updated: 2018/05/08 15:34:20 by gpouyat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MISC_H
# define MISC_H

#include "libft.h"
#include <mach-o/loader.h>
#include <mach-o/fat.h>
#include <ar.h>

typedef enum s_type_macho {
	M_32,
	M_64,
	M_FAT,
	M_LIB,
	M_END,
	M_ERR
}				t_type_macho;

typedef struct	s_macho_input {
	const char				*path;
	const void				*data;
	size_t					length;
	// t_type_macho			type;
	uint32_t				magic;
	struct load_command		*lc;
	uint32_t				ncmds;
}				t_macho_input;

typedef struct	s_handler_func
{
	t_type_macho	type;
	int			(*f)(const t_macho_input, void **list);
}				t_handler_func;

int				map_file(const char *prgm, const char *path, t_macho_input *input_file);
void			*secure_add(const t_macho_input input, const void *start_add, size_t length);
void			*secure_add_mv(t_macho_input input, const void *start_add, size_t length);
uint32_t		get_magic(t_macho_input input_file);
int				get_header_32(const t_macho_input input_file, const void *add, struct mach_header *header);
int				get_header_64(const t_macho_input input_file, const void *add, struct mach_header_64 *header);
int				get_header_fat(const t_macho_input input_file, const void *add, struct fat_header *header);
int				get_header_lib(const t_macho_input input_file, const void *add, struct ar_hdr *header);
int				exec_handler(const t_handler_func funcs[], t_macho_input input_file, void **list);


#endif