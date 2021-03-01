/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sections.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagroy- <alagroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 12:24:28 by alagroy-          #+#    #+#             */
/*   Updated: 2021/03/01 15:23:17 by alagroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

static void	loop_segs(t_file *file, t_seg *cmd, int *i_sect)
{
	int		nsects;
	void	*sect;
	int		i;

	i = -1;
	nsects = cmd->nsects;
	sect = (void *)cmd + sizeof(t_seg);
	if (!ft_strcmp(cmd->segname, "__TEXT"))
	{
		file->ntext = *i_sect;
		*i_sect += nsects;
		file->endtext = *i_sect;
	}
	else if (!ft_strcmp(cmd->segname, "__DATA"))
	{
		file->ndata = *i_sect;
		while (++i < nsects)
		{
			if (!ft_strcmp(((t_sect *)sect)->sectname, "__bss"))
				file->nbss = *i_sect;
			(*i_sect)++;
			sect += sizeof(t_sect);
		}
		file->endata = *i_sect;
	}
}

static void	loop_segs_64(t_file *file, t_seg64 *cmd, int *i_sect)
{
	int		nsects;
	void	*sect;
	int		i;

	i = -1;
	nsects = cmd->nsects;
	sect = (void *)cmd + sizeof(t_seg64);
	if (!ft_strcmp(cmd->segname, "__TEXT"))
	{
		file->ntext = *i_sect;
		*i_sect += nsects;
		file->endtext = *i_sect;
	}
	else if (!ft_strcmp(cmd->segname, "__DATA"))
	{
		file->ndata = *i_sect;
		while (++i < nsects)
		{
			if (!ft_strcmp(((t_sect64 *)sect)->sectname, "__bss"))
				file->nbss = *i_sect;
			(*i_sect)++;
			sect += sizeof(t_sect64);
		}
		file->endata = *i_sect;
	}
}

void		find_sect_index(t_file *file)
{
	void		*cmd;
	int			i;
	int			i_sect;
	int			ncmds;

	i = -1;
	if (file->arch == ARCH_64)
	{
		ncmds = ((t_mh_64 *)(file->ptr))->ncmds;
		cmd = file->ptr + sizeof(t_mh_64);
	}
	else
	{
		ncmds = ((t_mh *)(file->ptr))->ncmds;
		cmd = file->ptr + sizeof(t_mh);
	}
	i_sect = 1;
	while (++i < ncmds)
	{
		if (((t_lc *)cmd)->cmd == LC_SEGMENT)
			loop_segs(file, cmd, &i_sect);
		else if (((t_lc *)cmd)->cmd == LC_SEGMENT_64)
			loop_segs_64(file, cmd, &i_sect);
		cmd += ((t_lc *)cmd)->cmdsize;
	}
}
