/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagroy- <alagroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 11:43:54 by alagroy-          #+#    #+#             */
/*   Updated: 2021/03/09 12:22:50 by alagroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

static t_symtab	*find_symtab_64(t_file file)
{
	void	*cmd;
	int		i;
	int		ncmds;

	i = -1;
	ncmds = get_uint32(((t_mh_64 *)(file.ptr))->ncmds, file.endian);
	cmd = file.ptr + sizeof(t_mh_64);
	while (++i < ncmds && cmd < file.end)
	{
		if (get_uint32(((t_lc *)cmd)->cmd, file.endian) == LC_SYMTAB)
			return (cmd);
		cmd += get_uint32(((t_lc *)cmd)->cmdsize, file.endian);
	}
	return (NULL);
}

static t_symtab	*find_symtab(t_file file)
{
	void	*cmd;
	int		i;
	int		ncmds;

	i = -1;
	ncmds = get_uint32(((t_mh *)(file.ptr))->ncmds, file.endian);
	cmd = file.ptr + sizeof(t_mh);
	while (++i < ncmds && cmd < file.end)
	{
		if (get_uint32(((t_lc *)cmd)->cmd, file.endian) == LC_SYMTAB)
			return (cmd);
		cmd += get_uint32(((t_lc *)cmd)->cmdsize, file.endian);
	}
	return (NULL);
}

void			ft_process_mo(t_file file, t_nm nm)
{
	t_symtab	*symtab;
	t_sym		*symlist;

	if (file.arch == ARCH_64)
	{
		if (!((symtab = find_symtab_64(file))
			&& (symlist = get_symlist_64(file, symtab))))
			return ;
	}
	else
	{
		if (!((symtab = find_symtab(file))
			&& (symlist = get_symlist(file, symtab))))
			return ;
	}
	find_sect_index(&file);
	display_syms(symlist, nm, file, get_uint32(symtab->nsyms, file.endian));
}

void			ft_process_file(t_file file, t_nm nm)
{
	if (file.arch == ARCH_64 || file.arch == ARCH_32)
		return (ft_process_mo(file, nm));
	else if (file.arch == ARCHIVE)
		return (process_archive(&file, nm));
	else if (file.arch == FAT_64 || file.arch == FAT_32)
		return (process_fat(&file, nm));
}
