/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macho.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagroy- <alagroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 16:54:49 by alagroy-          #+#    #+#             */
/*   Updated: 2021/03/10 16:27:03 by alagroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

static t_sect64	*get_text_section64(t_seg64 *seg, t_file *file)
{
	uint32_t	i;
	uint32_t	nsects;
	t_sect64	*sect;

	i = -1;
	nsects = get_uint32(seg->nsects, file->endian);
	sect = (void *)seg + sizeof(t_seg64);
	while (++i < nsects && (void *)sect < file->end)
	{
		if (!ft_strncmp(sect[i].sectname, SECT_TEXT, 6))
			return (sect);
	}
	return (NULL);
}

static t_sect64	*find_text_sect64(t_file *file)
{
	void		*cmd;
	uint32_t	i;
	uint32_t	ncmds;
	t_sect64	*sect;

	i = -1;
	ncmds = get_uint32(((t_mh_64 *)file->ptr)->ncmds, file->endian);
	cmd = file->ptr + sizeof(t_mh_64);
	while (++i < ncmds && cmd < file->end)
	{
		if (get_uint32(((t_lc *)cmd)->cmd, file->endian) == LC_SEGMENT_64
			&& (!ft_strncmp(((t_seg64 *)cmd)->segname, SEG_TEXT, 6)
				|| !((t_seg *)cmd)->segname[0]))
			if ((sect = get_text_section64(cmd, file)))
				return (sect);
		cmd += get_uint32(((t_lc *)cmd)->cmdsize, file->endian);
	}
	return (NULL);
}

static t_sect	*get_text_section(t_seg *seg, t_file *file)
{
	uint32_t	i;
	uint32_t	nsects;
	t_sect	*sect;

	i = -1;
	nsects = get_uint32(seg->nsects, file->endian);
	sect = (void *)seg + sizeof(t_seg);
	while (++i < nsects && (void *)sect < file->end)
	{
		if (!ft_strncmp(sect[i].sectname, SECT_TEXT, 6))
			return (sect);
	}
	return (NULL);
}

static t_sect	*find_text_sect(t_file *file)
{
	void		*cmd;
	uint32_t	i;
	uint32_t	ncmds;
	t_sect		*sect;

	i = -1;
	ncmds = get_uint32(((t_mh *)file->ptr)->ncmds, file->endian);
	cmd = file->ptr + sizeof(t_mh);
	while (++i < ncmds && cmd < file->end)
	{
		if (get_uint32(((t_lc *)cmd)->cmd, file->endian) == LC_SEGMENT
			&& (!ft_strncmp(((t_seg *)cmd)->segname, SEG_TEXT, 6)
				|| !((t_seg *)cmd)->segname[0]))
			if ((sect = get_text_section(cmd, file)))
				return (sect);
		cmd += get_uint32(((t_lc *)cmd)->cmdsize, file->endian);
	}
	return (NULL);
}

void			process_macho(t_file *file, t_otool *otool)
{
	t_usect		text;

	if (file->arch == ARCH_64 && otool->t)
	{
		if (!(text.section64 = find_text_sect64(file)))
			return ;
	}
	else if (file->arch == ARCH_32 && otool->t)
	{
		if (!(text.section = find_text_sect(file)))
			return ;
	}
	ft_putendl("display");
	display(file, otool, &text);
}