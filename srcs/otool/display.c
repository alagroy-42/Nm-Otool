/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagroy- <alagroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 11:38:49 by alagroy-          #+#    #+#             */
/*   Updated: 2021/03/11 13:11:42 by alagroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

static void	display_header64(t_file *file)
{
	t_mh_64		*header;

	header = (t_mh_64 *)file->ptr;
	ft_putendl("Mach header");
	ft_printf("% 11s %s %s  % -7s %s %s %- 10s %10s\n", "magic", "cputype",
		"cpusubtype", "caps", "filetype", "ncmds", "sizeofcmds", "flags");
	ft_printf("% #11lx %7d %10d  %-#7.2lx %8lu %5u %10u %#10.8x\n",
		header->magic,
		get_uint32(header->cputype, file->endian),
		(uint8_t)get_uint32(header->cpusubtype, file->endian),
		(get_uint32(header->cpusubtype, file->endian) & CPU_SUBTYPE_MASK) >> 24,
		get_uint32(header->filetype, file->endian),
		get_uint32(header->ncmds, file->endian),
		get_uint32(header->sizeofcmds, file->endian),
		get_uint32(header->flags, file->endian));
}

static void	display_header(t_file *file)
{
	t_mh		*header;

	header = (t_mh *)file->ptr;
	ft_putendl("Mach header");
	ft_printf("% 11s %s %s  % -7s %s %s %- 10s %10s\n", "magic", "cputype",
		"cpusubtype", "caps", "filetype", "ncmds", "sizeofcmds", "flags");
	ft_printf("% #11lx %7d %10d  %-#7.2lx %8lu %5u %10u %#10.8x\n",
		header->magic,
		get_uint32(header->cputype, file->endian),
		(uint8_t)get_uint32(header->cpusubtype, file->endian),
		(get_uint32(header->cpusubtype, file->endian) & CPU_SUBTYPE_MASK) >> 24,
		get_uint32(header->filetype, file->endian),
		get_uint32(header->ncmds, file->endian),
		get_uint32(header->sizeofcmds, file->endian),
		get_uint32(header->flags, file->endian));
}

static void	display_text(t_file *file, t_usect *text)
{
	uint32_t	address;
	uint32_t	end;
	void		*end_ptr;
	void		*ptr;
	char		line[49];

	end = get_uint32(text->section->addr, file->endian)
		+ get_uint32(text->section->size, file->endian);
	address = get_uint32(text->section->addr, file->endian);
	ptr = file->ptr + get_uint32(text->section->offset, file->endian);
	end_ptr = ptr + get_uint32(text->section->size, file->endian);
	while (address < end && ptr < file->end)
	{
		get_line(line, ptr, end_ptr, file);
		ft_printf("%08lx\t%.49s", address, line);
		address += 0x10;
		ptr += 0x10;
	}
}

static void	display_text64(t_file *file, t_usect *text)
{
	uint64_t	address;
	uint64_t	end;
	void		*end_ptr;
	void		*ptr;
	char		line[49];

	end = get_uint64(text->section64->addr, file->endian)
			+ get_uint64(text->section64->size, file->endian);
	address = get_uint64(text->section64->addr, file->endian);
	ptr = file->ptr + get_uint32(text->section64->offset, file->endian);
	end_ptr = ptr + get_uint64(text->section64->size, file->endian);
	while (address < end && ptr < file->end)
	{
		get_line(line, ptr, end_ptr, file);
		ft_printf("%016llx\t%.49s", address, line);
		address += 0x10;
		ptr += 0x10;
	}
}

void		display(t_file *file, t_otool *otool, t_usect *text)
{
	if (otool->t)
	{
		ft_putendl("Contents of (__TEXT,__text) section");
		if (file->arch == ARCH_64)
			display_text64(file, text);
		if (file->arch == ARCH_32)
			display_text(file, text);
	}
	if (otool->h)
	{
		if (file->arch == ARCH_64)
			display_header64(file);
		if (file->arch == ARCH_32)
			display_header(file);
	}
}
