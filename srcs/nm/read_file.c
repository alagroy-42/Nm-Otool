/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagroy- <alagroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 11:43:54 by alagroy-          #+#    #+#             */
/*   Updated: 2021/03/03 15:48:41 by alagroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

static t_symtab	*find_symtab_64(t_file file)
{
	void	*cmd;
	int		i;
	int		ncmds;

	i = -1;
	ncmds = ((t_mh_64 *)(file.ptr))->ncmds;
	cmd = file.ptr + sizeof(t_mh_64);
	while (++i < ncmds)
	{
		if (((t_lc *)cmd)->cmd == LC_SYMTAB)
			return (cmd);
		cmd += ((t_lc *)cmd)->cmdsize;
	}
	return (NULL);
}

static t_symtab	*find_symtab(t_file file)
{
	void	*cmd;
	int		i;
	int		ncmds;

	i = -1;
	ncmds = ((t_mh *)(file.ptr))->ncmds;
	cmd = file.ptr + sizeof(t_mh);
	while (++i < ncmds)
	{
		if (((t_lc *)cmd)->cmd == LC_SYMTAB)
			return (cmd);
		cmd += ((t_lc *)cmd)->cmdsize;
	}
	return (NULL);
}

static void		ft_process_mo(t_file file, t_nm nm)
{
	t_symtab	*symtab;
	t_list		*symlist;

	if (file.arch == ARCH_64)
	{
		if (!(symtab = find_symtab_64(file)))
			return ;
		symlist = get_symlist_64(file, symtab);
	}
	else
	{
		if (!(symtab = find_symtab(file)))
			return ;
		symlist = get_symlist(file, symtab);
	}
	find_sect_index(&file);
	display_syms(symlist, nm, file);
}

void			ft_process_file(t_file file, t_nm nm)
{
	if (file.arch == ARCH_64 || file.arch == ARCH_32)
		return (ft_process_mo(file, nm));
	else if (file.arch == ARCHIVE)
	{
		process_archive(&file, nm);
	}
}
