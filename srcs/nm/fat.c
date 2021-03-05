/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagroy- <alagroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 14:41:21 by alagroy-          #+#    #+#             */
/*   Updated: 2021/03/05 17:26:54 by alagroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

static void	process_fat_64(t_file *file, t_nm nm)
{
	t_file		filetmp;
	void		*end;
	void		*ptr;

	ptr = file->ptr + sizeof(t_fathdr);
	end = file->ptr + sizeof(t_fathdr)
		+ get_uint32(((t_fathdr *)file->ptr)->nfat_arch, file->endian)
			* sizeof(t_fatarch64);
	while (ptr < end)
	{
		if (get_uint32(((t_fathdr *)file->ptr)->nfat_arch, file->endian) > 1)
			ft_printf("\n%s (for architecture %s):\n", file->filename,
				get_cpu_type_name(get_uint32(*(cpu_type_t *)ptr,
					file->endian)));
		filetmp = *file;
		filetmp.ptr = file->ptr + get_uint32(((t_fatarch64 *)ptr)->offset,
			file->endian);
		parse_magic(*(uint32_t *)filetmp.ptr, &filetmp);
		ft_process_mo(filetmp, nm);
		ptr += sizeof(t_fatarch64);
	}
}

void		process_fat(t_file *file, t_nm nm)
{
	t_file		filetmp;
	void		*end;
	void		*ptr;

	if (file->arch == FAT_64)
		return (process_fat_64(file, nm));
	ptr = file->ptr + sizeof(t_fathdr);
	end = file->ptr + sizeof(t_fathdr)
		+ get_uint32(((t_fathdr *)file->ptr)->nfat_arch, file->endian)
			* sizeof(t_fatarch);
	while (ptr < end)
	{
		if (get_uint32(((t_fathdr *)file->ptr)->nfat_arch, file->endian) > 1)
			ft_printf("\n%s (for architecture %s):\n", file->filename,
				get_cpu_type_name(get_uint32(*(cpu_type_t *)ptr,
					file->endian)));
		filetmp = *file;
		filetmp.ptr = file->ptr + get_uint32(((t_fatarch *)ptr)->offset,
			file->endian);
		parse_magic(*(uint32_t *)filetmp.ptr, &filetmp);
		ft_process_mo(filetmp, nm);
		ptr += sizeof(t_fatarch);
	}
}