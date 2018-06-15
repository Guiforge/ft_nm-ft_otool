/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_otool.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/15 19:18:16 by gpouyat           #+#    #+#             */
/*   Updated: 2018/06/15 21:16:32 by gpouyat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_OTOOL_H
# define FT_OTOOL_H

#include "misc.h"

#define PROGRAM "ft_otool"

typedef struct s_otool_flags {
	t_bool		t;
    t_bool      h;
	t_bool		print_arch;
	t_handler_func	*funcs;
}				t_nm_flags;

t_nm_flags		*get_otool_flags();
int				intern_nm_parse_option(int ac, const char **av);
int				handler_32(t_arch *input);

#endif