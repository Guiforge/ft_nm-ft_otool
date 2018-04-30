/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 22:52:36 by gpouyat           #+#    #+#             */
/*   Updated: 2018/04/30 20:28:57 by gpouyat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MISC_H
# define MISC_H

#include "libft.h"

typedef struct	s_macho_input {
	const void	*data;
	size_t		length;
}				t_macho_input;

typedef enum s_type_macho {
	M_32,
	M_64,
	M_FAT,
	M_LIB,
	M_END,
	M_ERR
}				t_type_macho;

typedef struct	s_handler_func
{
	t_type_macho	type;
	int			(*f)(const t_macho_input);
}				t_handler_func;

int				map_file(const char *prgm, const char *path, t_macho_input *input_file);
void			*secure_add(const t_macho_input input, const void *start_add, size_t length);
uint32_t		get_header(const t_macho_input input_file);
int				exec_handler(const t_handler_func funcs[], t_macho_input input_file);


#endif