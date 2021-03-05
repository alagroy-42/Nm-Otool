/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sections.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagroy- <alagroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 12:24:28 by alagroy-          #+#    #+#             */
/*   Updated: 2021/03/05 15:43:30 by alagroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

static void	loop_segs(t_file *file, t_seg *cmd, int *i_sect)
{
	int		nsects;
	void	*sect;
	int		i;

	i = -1;
	nsects = get_uint32(cmd->nsects, file->endian);
	sect = (void *)cmd + sizeof(t_seg);
	while (++i < nsects)
	{
		if (!ft_strcmp(((t_sect *)sect)->segname, "__TEXT")
			&& !ft_strcmp(((t_sect *)sect)->sectname, "__text"))
			file->text = *i_sect;
		if (!ft_strcmp(((t_sect *)sect)->segname, "__DATA")
			&& !ft_strcmp(((t_sect *)sect)->sectname, "__data"))
			file->data = *i_sect;
		if (!ft_strcmp(((t_sect *)sect)->segname, "__DATA")
			&& !ft_strcmp(((t_sect *)sect)->sectname, "__bss"))
			file->bss = *i_sect;
		(*i_sect)++;
		sect += sizeof(t_sect);
	}
}

static void	loop_segs_64(t_file *file, t_seg64 *cmd, int *i_sect)
{
	int		nsects;
	void	*sect;
	int		i;

	i = -1;
	nsects = get_uint32(cmd->nsects, file->endian);
	sect = (void *)cmd + sizeof(t_seg64);
	while (++i < nsects)
	{
		if (!ft_strcmp(((t_sect64 *)sect)->segname, "__TEXT")
			&& !ft_strcmp(((t_sect64 *)sect)->sectname, "__text"))
			file->text = *i_sect;
		if (!ft_strcmp(((t_sect64 *)sect)->segname, "__DATA")
			&& !ft_strcmp(((t_sect64 *)sect)->sectname, "__data"))
			file->data = *i_sect;
		if (!ft_strcmp(((t_sect64 *)sect)->segname, "__DATA")
			&& !ft_strcmp(((t_sect64 *)sect)->sectname, "__bss"))
			file->bss = *i_sect;
		(*i_sect)++;
		sect += sizeof(t_sect64);
	}
}

void		find_sect_index(t_file *file)
{
	void		*cmd;
	int			i;
	int			i_sect;
	int			ncmds;

	i = -1;
	if (!file->arch || file->arch > FAT_64)
		return ;
	if (file->arch == ARCH_64)
	{
		ncmds = get_uint32(((t_mh_64 *)(file->ptr))->ncmds, file->endian);
		cmd = file->ptr + sizeof(t_mh_64);
	}
	else
	{
		ncmds = get_uint32(((t_mh *)(file->ptr))->ncmds, file->endian);
		cmd = file->ptr + sizeof(t_mh);
	}
	i_sect = 1;
	while (++i < ncmds)
	{
		if (get_uint32(((t_lc *)cmd)->cmd, file->endian) == LC_SEGMENT)
			loop_segs(file, cmd, &i_sect);
		else if (get_uint32(((t_lc *)cmd)->cmd, file->endian) == LC_SEGMENT_64)
			loop_segs_64(file, cmd, &i_sect);
		cmd += get_uint32(((t_lc *)cmd)->cmdsize, file->endian);
	}
}
