/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_lib.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/03 10:41:28 by gpouyat           #+#    #+#             */
/*   Updated: 2018/06/12 09:38:45 by gpouyat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"
#include <mach-o/ranlib.h>
#include <ar.h>

static void *go_end_string_table(t_arch *input, void *start)
{
	void *offset;

	offset = start;
	while ((offset = ft_memchr(offset, '#', input->data + input->length - offset)))
	{
		if (secure_add(*input, offset, 3) && !ft_memcmp(offset, "#1/", 3))
			return (offset);
		if (!(offset = secure_add_mv(*input, offset, 1)))
			return (NULL);
	}
	return (NULL);
}

static void new_tmp(t_arch *tmp, size_t length, void *offset, t_arch *input)
{
	tmp->data = secure_add_mv(*input, offset, ft_next_multiple(ft_atoi(offset + 3) + sizeof(struct ar_hdr), 8));
	tmp->length = length;
	tmp->path = input->path;
}

static int handle_lib_objects(t_arch *input, void *offset)
{
	t_arch			*tmp;
	t_handler_func	*handler_funcs;
	int				ret;

	handler_funcs = get_nm_flags()->funcs;
	tmp = NULL;
	ret = 0;
	while (offset || !secure_add(*input, offset, sizeof(struct ar_hdr)))
	{
		if (!(tmp = (t_arch *)ft_secu_malloc_lvl(sizeof(t_arch), MALLOC_LVL_FILE_MACH_O)))
			return (return_error(input->path, ERR_UNDIFINED, 1));
		if (!secure_string(*input, offset, 0))
			return (return_error(input->path, ERR_MALFORMED, 1));
		new_tmp(tmp, ft_atoi(((struct ar_hdr *)offset)->ar_size), offset, input);
		if (!tmp->data || !(secure_add(*input, tmp->data, tmp->length - ft_atoi(offset + 3))) || !secure_string(*input, offset + sizeof(struct ar_hdr), 0))
		 	return (return_error(input->path, ERR_MALFORMED, 1));
		ft_printf("\n%s(%s):\n", input->path, offset + sizeof(struct ar_hdr));
		if ((ret = exec_handler(handler_funcs, tmp)) == 2)
			return (return_error(input->path, ERR_INVALID, 1));
		if (offset + tmp->length + sizeof(struct ar_hdr)  ==  (input->data + input->length))
			break;
		if (!(offset = secure_add_mv(*input, offset, tmp->length + sizeof(struct ar_hdr))))
			return (return_error(input->path, ERR_INVALID, 1));
	}
	return(ret);
}

static int parse_lib(t_arch *input)
{
	void		*offset;

	if (!(offset = secure_add_mv(*input, input->data, AR_LEN_BEFORE_SYMTAB)))
		return (return_error(input->path, ERR_MALFORMED, 1));	
	if (!secure_add(*input, offset, sizeof(uint32_t) + 1))
		return (return_error(input->path, ERR_MALFORMED, 1));	
	if (!(offset = secure_add_mv(*input, offset, *(uint32_t *)offset + sizeof(uint32_t))))
		return (return_error(input->path, ERR_MALFORMED, 1));	
	if (!(offset = go_end_string_table(input, offset)))
		return (return_error(input->path, ERR_INVALID, 1));	
	return (handle_lib_objects(input, offset));
}

int handle_lib(t_arch *input)
{
	void			*copy_add;
	
	if (!(copy_add = secure_add_mv(*input, input->data, SARMAG + sizeof(struct ar_hdr))))
		return (return_error(input->path, ERR_MALFORMED, 1));
	if (!secure_add(*input, copy_add, AR_LONG_NAME))
		return (return_error(input->path, ERR_MALFORMED, 1));
	if (!ft_strncmp(SYMDEF, copy_add, AR_LONG_NAME) ||
		!ft_strncmp(SYMDEF_SORTED, copy_add, AR_LONG_NAME) ||
		!ft_strncmp(SYMDEF_64, copy_add, AR_LONG_NAME) ||
		!ft_strncmp(SYMDEF_64_SORTED, copy_add, AR_LONG_NAME))
		return (parse_lib(input));
	return (return_error(input->path, ERR_INVALID, 1));
}