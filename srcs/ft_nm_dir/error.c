/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/01 09:53:13 by gpouyat           #+#    #+#             */
/*   Updated: 2018/05/08 13:06:29 by gpouyat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_nm.h"

void	print_error(const char *path, t_type_err type)
{
	if (type == ERR_INVALID)
		ft_dprintf(STDERR_FILENO, ERR_INVALID_FMT, PROGNAME, path);
	else if (type == ERR_MALFORMED)
		ft_dprintf(STDERR_FILENO, ERR_MALFORMED_FMT, PROGNAME, path);
	else
		ft_dprintf(STDERR_FILENO, "ERR UNDEFINED\n");
}

int		return_error(const char *path, t_type_err type, int ret)
{
	print_error(path, type);
	return (ret);
}