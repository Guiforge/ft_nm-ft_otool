/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_lib.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/03 10:41:28 by gpouyat           #+#    #+#             */
/*   Updated: 2018/06/04 23:47:07 by gpouyat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"
#include <mach-o/ranlib.h>
#include <ar.h>

static void *go_end_string_table(t_arch *input, void *start)
{
	void *offset;

	ft_putendl("1");	
	if (!(offset = secure_add_mv(*input, start, sizeof(char[4]))) || *(char *)start != 'h' || *((char*)start + 3))
		return(NULL);
	ft_putendl("1");
	while ((offset = ft_memchr(offset, 0, input->data + input->length - offset)))
	{
		if (secure_add(*input, offset, 4) && !ft_memcmp(offset, "\0\0\0\0", 4))
		{
			offset += 4;
			offset += ((uint32_t)(offset - input->data) % 8 ? (8 - (uint32_t)(offset - input->data) % 8) : 0);
			ft_printf("off = %x, %d\n", offset - input->data, (offset - input->data) % 8);
			return (offset);
		}
		if (!(offset = secure_add_mv(*input, offset, 1)))
			return (NULL);
	}
	ft_putendl("3");	
	return (NULL);
}

static int handle_lib_object(t_arch *input, void *offset)
{
	t_arch	*tmp;
	size_t	tmp_size;
	const t_handler_func handler_funcs[] = {
		{M_32, &handler_32},
		{M_64, &handler_64},
		{M_END, NULL}
	};
	tmp = NULL;
	int	toto;
	while (offset || !secure_add(*input, offset, sizeof(struct ar_hdr)))
	{
		ft_putendl("*");
		tmp_size = ft_atoi(((struct ar_hdr *)offset)->ar_size);

		if (!(tmp = (t_arch *)ft_memalloc(sizeof(t_arch))))
			return (return_error(input->path, ERR_UNDIFINED, 1));

		if (!secure_string(*input, offset, 0))
			return (return_error(input->path, ERR_MALFORMED, 1));

		//toto = ft_strlen(offset) + 1;
		//ft_printf("toto = %d, toto % 8 = %d, next = %d\n", toto, toto % 8, ft_next_multiple(toto, 8));
		//toto = (toto % 8 ? toto : toto + 1);
		char tutu[3];
		ft_memcpy(tutu, offset+ 3, 2);
		tutu[2] = 0;
		toto = ft_atoi(tutu) + sizeof(struct ar_hdr);
		tmp->data = secure_add_mv(*input, offset, ft_next_multiple(toto, 8));
		tmp->length = tmp_size;
		tmp->path = input->path;

		if (offset  + tmp->length + sizeof(struct ar_hdr)  ==  (input->data + input->length))
			break;
		if (!tmp->data || !(secure_add(*input, tmp->data, tmp->length)))
			return (return_error(input->path, ERR_MALFORMED, 1));
		ft_printf("--offset = %x\n", offset - input->data);		
		ft_printf("--Start = %x \n", tmp->data - input->data);
		if (exec_handler(handler_funcs, tmp) == 2)
			return (return_error(input->path, ERR_INVALID, 1));

		//5720
		ft_printf("+offset = %x + %d\n", offset - input->data, tmp->length + sizeof(struct ar_hdr));
		if (!(offset = secure_add_mv(*input, offset, tmp->length + sizeof(struct ar_hdr))))
			return (return_error(input->path, ERR_INVALID, 1));
		ft_printf("+offset = %x\n", offset - input->data);
	}
	return(0);
}

static int handle_lib_32(t_arch *input)
{
	void		*offset;

	if (!(offset = secure_add_mv(*input, input->data, AR_LEN_BEFORE_SYMTAB)))
		return (return_error(input->path, ERR_MALFORMED, 1));
	ft_printf("start + obj = %x\n", offset - input->data);
	if (!secure_add(*input, offset, sizeof(uint32_t) + 1))
		return (return_error(input->path, ERR_MALFORMED, 1));
	ft_printf("off = %x, %d\n", offset - input->data, *(uint32_t *)offset);
	if (!(offset = secure_add_mv(*input, offset, *(uint32_t *)offset + sizeof(uint32_t))))
		return (return_error(input->path, ERR_MALFORMED, 1));
	if (!(offset = go_end_string_table(input, offset)))
		return (return_error(input->path, ERR_INVALID, 1));
	ft_printf("()%x\n", offset - input->data);
	ft_printf("%x, %c\n", offset - input->data, *(char *)(offset - 1));	 
	return (handle_lib_object(input, offset));
}

static int handle_lib_64(t_arch *input)
{
	(void)input;
	ft_putendl("LIB 64");	
	return (0);
}

int handle_lib(t_arch *input)
{
	void			*copy_add;
	
	if (!(copy_add = secure_add_mv(*input, input->data, SARMAG + sizeof(struct ar_hdr))))
		return (return_error(input->path, ERR_MALFORMED, 1));
	if (!secure_add(*input, copy_add, AR_LONG_NAME))
		return (return_error(input->path, ERR_MALFORMED, 1));
	if (!ft_strncmp(SYMDEF, copy_add, AR_LONG_NAME) || !ft_strncmp(SYMDEF_SORTED, copy_add, AR_LONG_NAME))
		return (handle_lib_32(input));
	else if (!ft_strncmp(SYMDEF_64, copy_add, AR_LONG_NAME) || !ft_strncmp(SYMDEF_64_SORTED, copy_add, AR_LONG_NAME))
		return (handle_lib_64(input));
	return (return_error(input->path, ERR_INVALID, 1));
}