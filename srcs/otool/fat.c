/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagroy- <alagroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 16:57:18 by alagroy-          #+#    #+#             */
/*   Updated: 2021/03/10 17:13:53 by alagroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

static int	host_arch(cpu_type_t cputype)
{
	if (cputype == CPU_TYPE_X86_64 && sizeof(void *) == 8)
		return (1);
	if (cputype == CPU_TYPE_I386 && sizeof(void *) == 4)
		return (1);
	return (0);
}

static void	process_fat_64(t_file *file, t_otool *otool)
{
	t_file		filetmp;
	t_fatarch64	*ptr;
	int			i;
	int			narch;

	narch = get_uint32(((t_fathdr *)file->ptr)->nfat_arch, file->endian);
	ptr = file->ptr + sizeof(t_fathdr);
	i = -1;
	while (++i < narch && ptr + i < (t_fatarch64 *)file->end)
	{
		if (narch > 1 && !i && host_arch(get_uint32(ptr[i + 1].cputype,
			file->endian)))
			continue ;
		if (narch > 1 && !host_arch(get_uint32(ptr[i].cputype, file->endian)))
			ft_printf("\n%s (architecture %s):\n", file->filename,
				get_cpu_type_name(get_uint32(ptr[i].cputype, file->endian)));
		filetmp = *file;
		filetmp.ptr = file->ptr + get_uint32(ptr[i].offset, file->endian);
		parse_magic(*(uint32_t *)filetmp.ptr, &filetmp);
		process_file(&filetmp, otool);
		if (host_arch(get_uint32(ptr[i].cputype, file->endian)))
			return ;
	}
}

static void	process_fat_32(t_file *file, t_otool *otool)
{
	t_file		filetmp;
	t_fatarch	*ptr;
	int			i;
	int			narch;

	narch = get_uint32(((t_fathdr *)file->ptr)->nfat_arch, file->endian);
	ptr = file->ptr + sizeof(t_fathdr);
	i = -1;
	while (++i < narch && ptr + i < (t_fatarch *)file->end)
	{
		if (narch > 1 && !i && host_arch(get_uint32(ptr[i + 1].cputype,
			file->endian)))
			continue ;
		if (narch > 1 && !host_arch(get_uint32(ptr[i].cputype, file->endian)))
			ft_printf("%s (architecture %s):\n", file->filename,
				get_cpu_type_name(get_uint32(ptr[i].cputype, file->endian)));
		filetmp = *file;
		filetmp.ptr = file->ptr + get_uint32(ptr[i].offset, file->endian);
		parse_magic(*(uint32_t *)filetmp.ptr, &filetmp);
		process_file(&filetmp, otool);
		if (host_arch(get_uint32(ptr[i].cputype, file->endian)))
			return ;
	}
}

void		process_fat(t_file *file, t_otool *otool)
{
	if (file->arch == FAT_64)
		return (process_fat_64(file, otool));
	else if (file->arch == FAT_32)
		return (process_fat_32(file, otool));
}
