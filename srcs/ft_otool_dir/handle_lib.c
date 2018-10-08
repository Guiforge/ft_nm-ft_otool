/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_lib.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/26 14:03:39 by gpouyat           #+#    #+#             */
/*   Updated: 2018/10/08 17:00:50 by gpouyat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_otool.h"
#include <mach-o/ranlib.h>

static void			*go_end_string_table(t_arch *input, void *start)
{
	void *offset;

	offset = start;
	while ((offset = ft_memchr(offset, '#', input->data +
													input->length - offset)))
	{
		if (secure_add(*input, offset, 3) && !ft_memcmp(offset, "#1/", 3))
			return (offset);
		if (!(offset = secure_add_mv(*input, offset, 1)))
			return (NULL);
	}
	return (NULL);
}

static t_arch		*new_tmp(t_arch *input, void *offset, size_t length)
{
	t_arch		*tmp;

	tmp = NULL;
	if (!(tmp = (t_arch *)ft_secu_malloc_lvl(sizeof(t_arch),
													MALLOC_LVL_FILE_MACH_O)))
		return (return_error_null(input->path, PROGRAM, ERR_UNDIFINED));
	if (!secure_string(*input, offset, 0))
		return (return_error_null(input->path, PROGRAM, ERR_MALFORMED));
	tmp->data = secure_add_mv(*input, offset,
			ft_next_multiple(ft_atoi(offset + 3) + sizeof(struct ar_hdr), 8));
	tmp->length = length;
	tmp->path = input->path;
	if (!tmp->data || !(secure_add(*input, tmp->data,
					tmp->length - ft_atoi(offset + 3))) ||
					!secure_string(*input, offset + sizeof(struct ar_hdr), 0))
		return (return_error_null(input->path, PROGRAM, ERR_MALFORMED));
	ft_printf("%s(%s):\n", input->path, offset + sizeof(struct ar_hdr));
	return (tmp);
}

static int			handle_lib_objects(t_arch *input, void *offset)
{
	t_arch			*tmp;
	t_handler_func	*handler_funcs;
	int				ret;

	handler_funcs = get_otool_flags()->funcs;
	tmp = NULL;
	ret = 0;
	while (offset || !secure_add(*input, offset, sizeof(struct ar_hdr)))
	{
		tmp = new_tmp(input, offset,
								ft_atoi(((struct ar_hdr *)offset)->ar_size));
		if (!tmp)
			return (1);
		if ((ret = exec_handler(handler_funcs, tmp)) == 2)
			return (return_error(input->path, PROGRAM, ERR_INVALID, 1));
		if (offset + tmp->length + sizeof(struct ar_hdr) == (input->data +
																input->length))
			break ;
		if (!(offset = secure_add_mv(*input, offset, tmp->length +
														sizeof(struct ar_hdr))))
			return (return_error(input->path, PROGRAM, ERR_INVALID, 1));
		ft_secu_free(tmp);
	}
	return (ret);
}

static int			parse_lib(t_arch *input)
{
	void		*offset;

	if (!(offset = secure_add_mv(*input, input->data, AR_LEN_BEFORE_SYMTAB)))
		return (return_error(input->path, PROGRAM, ERR_MALFORMED, 1));
	if (!secure_add(*input, offset, sizeof(uint32_t) + 1))
		return (return_error(input->path, PROGRAM, ERR_MALFORMED, 1));
	if (!(offset = secure_add_mv(*input, offset, *(uint32_t *)offset +
															sizeof(uint32_t))))
		return (return_error(input->path, PROGRAM, ERR_MALFORMED, 1));
	if (!(offset = go_end_string_table(input, offset)))
		return (return_error(input->path, PROGRAM, ERR_INVALID, 1));
	return (handle_lib_objects(input, offset));
}

int					handle_lib(t_arch *input)
{
	void			*copy_add;

	if (!(copy_add = secure_add_mv(*input, input->data, SARMAG +
														sizeof(struct ar_hdr))))
		return (return_error(input->path, PROGRAM, ERR_MALFORMED, 1));
	if (!secure_add(*input, copy_add, AR_LONG_NAME))
		return (return_error(input->path, PROGRAM, ERR_MALFORMED, 1));
	if (!ft_strncmp(SYMDEF, copy_add, AR_LONG_NAME) ||
		!ft_strncmp(SYMDEF_SORTED, copy_add, AR_LONG_NAME) ||
		!ft_strncmp(SYMDEF_64, copy_add, AR_LONG_NAME) ||
		!ft_strncmp(SYMDEF_64_SORTED, copy_add, AR_LONG_NAME))
		return (parse_lib(input));
	return (return_error(input->path, PROGRAM, ERR_INVALID, 1));
}
