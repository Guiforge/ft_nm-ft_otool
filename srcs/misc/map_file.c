/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_file.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 22:54:19 by gpouyat           #+#    #+#             */
/*   Updated: 2018/10/08 12:29:46 by gpouyat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/misc.h"
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>

static int	static_intern_open(const char *prgm, const char *path)
{
	int		fd;

	if ((fd = open(path, O_RDONLY)) < 0)
	{
		ft_dprintf(STDERR_FILENO, ERR_OPEN_FMT, prgm, path);
		return (-1);
	}
	return (fd);
}

static int	static_intern_fstat(const char *prgm, int fd, struct stat *buf)
{
	if (fstat(fd, buf) != 0)
	{
		ft_dprintf(STDERR_FILENO, ERR_FSTAT_FMT, prgm, fd);
		return (1);
	}
	if (S_ISDIR(buf->st_mode))
	{
		ft_dprintf(STDERR_FILENO, ERR_IS_DIR_FMT, prgm, fd);
		return (1);
	}
	return (0);
}

static int	static_intern_mmap(const char *prgm, void **data, int fd,
																size_t size)
{
	*data = mmap(NULL, size, PROT_READ, MAP_FILE | MAP_PRIVATE, fd, 0);
	if (*data == MAP_FAILED)
	{
		ft_dprintf(STDERR_FILENO, ERR_MMAP_FMT, prgm, fd);
		return (1);
	}
	return (0);
}

static int	close_fd_return(int fd, int ret)
{
	close(fd);
	return (ret);
}

int			map_file(const char *prgm, const char *path, t_arch *arch)
{
	struct stat		buf;
	void			*data;
	int				fd;

	data = NULL;
	if ((fd = static_intern_open(prgm, path)) < 0)
		return (1);
	if (static_intern_fstat(prgm, fd, &buf))
		return (close_fd_return(fd, 1));
	if (static_intern_mmap(prgm, &data, fd, buf.st_size))
		return (close_fd_return(fd, 1));
	if (arch)
	{
		arch->path = ft_strdup(path);
		arch->data = data;
		arch->length = buf.st_size;
	}
	return (close_fd_return(fd, 0));
}
