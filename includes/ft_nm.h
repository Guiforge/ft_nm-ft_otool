/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 22:52:36 by gpouyat           #+#    #+#             */
/*   Updated: 2018/06/26 14:07:08 by gpouyat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef FT_NM_H
# define FT_NM_H

#include "misc.h"
#include "libft.h"


# define PROGRAM "ft_nm"



typedef enum	s_type_arch {
	ARCH_32,
	ARCH_64
}				t_type_arch;

typedef struct	s_sym {
	char		*name;
	char		sectname[16];
	char		segname[16];
	uint64_t	value;
	uint8_t		ntype;
	uint8_t		nsect;
	t_type_arch	arch;
}				t_sym;

typedef struct s_nm_flags {
	t_bool		a;
	t_bool		g;
	t_bool		A;
	t_bool		n;
	t_bool		p;
	t_bool		r;
	t_bool		u;
	t_bool		U;
	t_bool		m;
	t_bool		j;
	t_bool		print_arch;
	t_handler_func	*funcs;
}				t_nm_flags;

t_nm_flags		*get_nm_flags();
int		intern_nm_parse_option(int ac, const char **av);

char	if_upper(char c, uint8_t ntype);
char	get_char_type(t_sym sym);
void	print_value(t_sym sym, char c);

int		handler_64(t_arch *input);
int		handler_32(t_arch *input);
int		handle_fat(t_arch *input);
int		handle_lib(t_arch *input);
char	get_sim_type(struct nlist_64 sym, t_arch input);

int		find_seg_sect_name_64(struct nlist_64 symbol, t_sym *elem_sym, t_arch input);
int		find_seg_sect_name(struct nlist symbol, t_sym *elem_sym, t_arch input);

struct symtab_command	*get_symtab_cmd(t_arch input);

void	print_nm(t_arch *input);
void	print_m(t_sym sym);

void	sort_sym(t_list **lst_sym);

#endif