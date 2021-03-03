/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagroy- <alagroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 12:05:06 by alagroy-          #+#    #+#             */
/*   Updated: 2021/03/03 15:27:26 by alagroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shared.h"

int			parse_magic(uint32_t magic, void *ptr)
{
	if (magic == MH_MAGIC || magic == MH_CIGAM)
		return (ARCH_32);
	else if (magic == MH_MAGIC_64 || magic == MH_CIGAM_64)
		return (ARCH_64);
	else if (!ft_strncmp((char *)ptr, ARMAG, SARMAG) || magic == OARMAG1
		|| magic == OARMAG2)
		return (ARCHIVE);
	else if (magic == FAT_MAGIC || magic == FAT_CIGAM)
		return (FAT_32);
	else if (magic == FAT_MAGIC_64 || magic == FAT_CIGAM_64)
		return (FAT_64);		
	else
		return (E_NOOBJ);
}

int			check_file(t_file file)
{
	if (file.arch && file.arch < E_NOOBJ)
		return (EXIT_SUCCESS);
	else if (file.arch == E_BADFILE)
		ft_dprintf(2, "error: %s : %s\n", file.filename, ERROR_OPEN);
	else if (file.arch == E_NOOBJ)
		ft_dprintf(2, "error : %s: %s\n", file.filename, ERROR_MAGIC);
	else if (file.arch == E_NOMEM)
	{
		ft_putstr_fd("error: Memory error, process cannot continue.\n", 2);
		exit(EXIT_FAILURE);
	}
	return (EXIT_FAILURE);
}

t_file		load_file(char *filename)
{
	t_file		file;
	struct stat	filestats;

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
	*(char *)((void *)file.ptr + file.size - 1) = 0;
	file.magic = *(uint32_t *)file.ptr;
	file.arch = parse_magic(file.magic, file.ptr);
	return (file);
}
