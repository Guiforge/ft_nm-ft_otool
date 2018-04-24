/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_file.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 22:54:19 by gpouyat           #+#    #+#             */
/*   Updated: 2018/04/24 09:27:55 by gpouyat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "misc.h"
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>

int     map_file(const char *path, t_macho_input *input_file)
{
    int fd ;
    if ((fd = open(path, O_RDONLY)) < 0)
    {
        ft_dprintf(STDERR_FILENO, "nm: open %s \n", path);
        return (1);
    }

    struct stat stbuf;
    if (fstat(fd, &stbuf) != 0) {
        ft_putstr("fstat()");
    }

    /* mmap */
    void *data = mmap(NULL, stbuf.st_size, PROT_READ, MAP_FILE|MAP_PRIVATE, fd, 0);
    if (data == MAP_FAILED)
        ft_putstr("mmap()");

    /* Parse */
    input_file->data = data;
    input_file->length = stbuf.st_size;
    return (1);
}