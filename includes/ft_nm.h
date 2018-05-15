/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 22:52:36 by gpouyat           #+#    #+#             */
/*   Updated: 2018/05/15 11:30:22 by gpouyat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef FT_NM_H
# define FT_NM_H

#include "misc.h"
#include "libft.h"
#include <mach-o/nlist.h>

# define PROGNAME "ft_nm"
# define ERR_INVALID_FMT "{red}%s{no}: %s The file was not recognized as a valid object file\n"
# define ERR_MALFORMED_FMT "{red}%s{no}: %s truncated or malformed object\n"

typedef enum	s_type_err {
	ERR_INVALID,
	ERR_MALFORMED,
	ERR_UNDIFINED,
}				t_type_err;

typedef enum	s_type_arch {
	ARCH_32,
	ARCH_64,
}				t_type_arch;

typedef struct	s_sym {
	char		*name;
	char		sectname[16];
	char		segname[16];
	uint64_t	value;
	uint8_t		ntype;
	t_bool		is_ext;
	t_type_arch	arch;
}				t_sym;

void	print_error(const char *path, t_type_err type);
int		return_error(const char *path, t_type_err type, int ret);
int		handler_64(t_macho_input input, void **list);
int		handler_32(t_macho_input input, void **list);
char	get_sim_type(struct nlist_64 sym, t_macho_input input);

int		find_seg_sect_name_64(struct nlist_64 symbol, t_sym *elem_sym, t_macho_input input);
int		find_seg_sect_name(struct nlist symbol, t_sym *elem_sym, t_macho_input input);

struct symtab_command	*get_symtab_cmd(t_macho_input input);
#endif