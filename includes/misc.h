/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 22:52:36 by gpouyat           #+#    #+#             */
/*   Updated: 2018/04/24 09:24:28 by gpouyat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MISC_H
# define MISC_H

#include "libft.h"

typedef struct g_macho_input {
    const void *data;
    size_t length;
} t_macho_input;

int     map_file(const char *path, t_macho_input *input_file);

#endif