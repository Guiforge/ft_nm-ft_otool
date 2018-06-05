/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_fat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 09:41:59 by gpouyat           #+#    #+#             */
/*   Updated: 2018/06/03 14:00:17 by gpouyat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

static int	handle_fat_archs(t_arch *input, struct fat_header header, struct fat_arch *arch, t_list **lst_archs)
{
	t_arch		*tmp;
	const t_handler_func handler_funcs[] = {
		{M_32, &handler_32},
		{M_64, &handler_64},
		{M_END, NULL}
	};
	
	while (header.nfat_arch--)
	{
		if (!(tmp = create_new_arch(lst_archs)))
			return (return_error(input->path, ERR_UNDIFINED, 1));
		tmp->data = secure_add_mv(*input, input->data, ifswap32(input, arch->offset));
		tmp->length = ifswap32(input, arch->size);
		tmp->path = input->path;
		if (!tmp->data || !(secure_add(*input, tmp->data, tmp->length)))
			return (return_error(input->path, ERR_MALFORMED, 1));
		if (exec_handler(handler_funcs, tmp) == 2)
			return (1);
		if (!(arch = secure_add_mv(*input, arch, sizeof(struct fat_arch))))
			return (return_error(input->path, ERR_INVALID, 1));
	}
	return (0);
}

int handle_fat(t_arch *input)
{
	struct fat_header header;
	struct fat_arch *arch;
	t_list			*lst_archs;
	int				ret;

	lst_archs = NULL;
	get_nm_flags()->print_arch = True;
	if (get_header_fat(*input, input->data, &header))
		return(return_error(input->path, ERR_INVALID, 2));
	if (!(arch = secure_add_mv(*input, input->data, sizeof(struct fat_header))))
		return (return_error(input->path, ERR_INVALID, 2));
	ret = handle_fat_archs(input, header, arch, &lst_archs);
	return (ret);
}