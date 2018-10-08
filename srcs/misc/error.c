/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/01 09:53:13 by gpouyat           #+#    #+#             */
/*   Updated: 2018/10/08 11:55:57 by gpouyat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/misc.h"

void	print_error(const char *path, char *pgm, t_type_err type)
{
	if (type == ERR_INVALID)
		ft_dprintf(STDERR_FILENO, ERR_INVALID_FMT, pgm, path);
	else if (type == ERR_MALFORMED)
		ft_dprintf(STDERR_FILENO, ERR_MALFORMED_FMT, pgm, path);
	else
		ft_dprintf(STDERR_FILENO, "ERR UNDEFINED\n");
}

int		return_error(const char *path, char *pgm, t_type_err type, int ret)
{
	print_error(path, pgm, type);
	return (ret);
}
