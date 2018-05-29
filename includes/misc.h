/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 22:52:36 by gpouyat           #+#    #+#             */
/*   Updated: 2018/05/29 08:00:22 by gpouyat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MISC_H
# define MISC_H

#include "libft.h"
#include <mach-o/loader.h>
#include <mach-o/fat.h>
#include <mach-o/nlist.h>
#include <ar.h>

typedef enum	s_endian {
	BIG,
	LITTLE,
	UNKNOWN
}				t_endian;

typedef enum s_type_macho {
	M_32,
	M_64,
	M_FAT,
	M_LIB,
	M_END,
	M_ERR
}				t_type_macho;

typedef struct	s_arch {
	const char				*path;
	const void				*data;
	size_t					length;
	uint32_t				magic;
	t_bool					is_swap;
	struct load_command		*lc;
	t_list					*list;
	uint32_t				ncmds;
}				t_arch;

typedef struct	s_handler_func
{
	t_type_macho	type;
	int			(*f)(t_arch *);
}				t_handler_func;

uint16_t ft_swapInt16(uint16_t x);
uint32_t ft_swapInt32(uint32_t x);
uint64_t ft_swapInt64(uint64_t x);

uint16_t ifswap16(t_arch *input, uint16_t x);
uint32_t ifswap32(t_arch *input, uint32_t x);
uint64_t ifswap64(t_arch *input, uint64_t x);

void	swap_fat_header(struct fat_header *fh);
void	swap_mach_header(struct mach_header *mh);
void	swap_mach_header_64(struct mach_header_64 *mh);
void	swap_symtab_command(struct symtab_command *st);
void	swap_section_64(struct section_64 *s, uint32_t nsects);
void	swap_section(struct section *s, uint32_t nsects);
void	swap_nlist_64(struct nlist_64 *symbol);
void	swap_nlist(struct nlist *symbol);

int				map_file(const char *prgm, const char *path, t_arch *arch);
void			*secure_add(const t_arch input, const void *start_add, size_t length);
void			*secure_add_mv(t_arch input, const void *start_add, size_t length);
char			*secure_string(t_arch input, char *string_table, uint32_t offset);
uint32_t		get_magic(t_arch *arch);
int				get_header_32(const t_arch arch, const void *add, struct mach_header *header);
int				get_header_64(const t_arch arch, const void *add, struct mach_header_64 *header);
int				get_header_fat(const t_arch arch, const void *add, struct fat_header *header);
int				get_header_lib(const t_arch arch, const void *add, struct ar_hdr *header);
int				exec_handler(const t_handler_func funcs[], t_arch *arch);


#endif