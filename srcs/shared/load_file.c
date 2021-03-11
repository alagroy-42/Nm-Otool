/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagroy- <alagroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 12:05:06 by alagroy-          #+#    #+#             */
/*   Updated: 2021/03/11 12:43:18 by alagroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shared.h"

void		parse_magic(uint32_t magic, t_file *file)
{
	if (magic == MH_MAGIC || magic == MH_CIGAM)
		file->arch = ARCH_32;
	else if (magic == MH_MAGIC_64 || magic == MH_CIGAM_64)
		file->arch = ARCH_64;
	else if (!ft_strncmp((char *)file->ptr, ARMAG, SARMAG) || magic == OARMAG1
		|| magic == OARMAG2)
		file->arch = ARCHIVE;
	else if (magic == FAT_MAGIC || magic == FAT_CIGAM)
		file->arch = FAT_32;
	else if (magic == FAT_MAGIC_64 || magic == FAT_CIGAM_64)
		file->arch = FAT_64;
	else
		file->arch = E_NOOBJ;
	if (magic == MH_CIGAM || magic == MH_CIGAM_64 || magic == FAT_CIGAM
		|| magic == FAT_CIGAM_64)
		file->endian = LENDIAN;
	else
		file->endian = BENDIAN;
}

int			check_file(t_file file, int nobj_fd)
{
	if (file.arch && file.arch < E_NOOBJ)
		return (EXIT_SUCCESS);
	else if (file.arch == E_BADFILE)
		ft_dprintf(2, "error: %s : %s\n", file.filename, ERROR_OPEN);
	else if (file.arch == E_NOOBJ)
		ft_dprintf(nobj_fd, ERROR_NOOBJ, file.filename);
	else if (file.arch == E_NOMEM)
	{
		ft_strdel(&file.filename);
		ft_putstr_fd("error: Memory error, process cannot continue.\n", 2);
		exit(EXIT_FAILURE);
	}
	else if (file.arch == E_TRUNC)
		ft_dprintf(2, "error : %s : %s\n", file.filename, ERROR_TRUNC);
	return (EXIT_FAILURE);
}

t_file		load_file(char *filename)
{
	t_file		file;
	struct stat	filestats;
	int			magic;

	ft_bzero(&file, sizeof(t_file));
	if (!(file.filename = ft_strdup(filename)))
		file.arch = E_NOMEM;
	if ((file.fd = open(filename, O_RDONLY)) == -1
		|| fstat(file.fd, &filestats) == -1)
		return (file);
	file.size = filestats.st_size;
	if ((file.ptr = mmap(NULL, file.size, PROT_READ | PROT_WRITE, MAP_PRIVATE,
		file.fd, 0)) == MAP_FAILED)
	{
		file.arch = E_NOMEM;
		return (file);
	}
	file.end = file.ptr + file.size - 1;
	magic = *(uint32_t *)file.ptr;
	parse_magic(magic, &file);
	if (file.ptr + get_uint32(((t_mh *)file.ptr)->sizeofcmds, file.endian)
		> file.end && (file.arch == ARCH_64 || file.arch == ARCH_32))
		file.arch = E_TRUNC;
	return (file);
}
