/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   archive.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagroy- <alagroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 14:45:40 by alagroy-          #+#    #+#             */
/*   Updated: 2021/03/03 13:32:03 by alagroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

static t_symtab	*find_symtab_64(void *ptr)
{
	void	*cmd;
	int		i;
	int		ncmds;

	i = -1;
	ncmds = ((t_mh_64 *)(ptr))->ncmds;
	cmd = ptr + sizeof(t_mh_64);
	while (++i < ncmds)
	{
		if (((t_lc *)cmd)->cmd == LC_SYMTAB)
			return (cmd);
		cmd += ((t_lc *)cmd)->cmdsize;
	}
	return (NULL);
}

static t_symtab	*find_symtab(void *ptr)
{
	void		*cmd;
	int			i;
	int			ncmds;
	uint32_t	magic;

	magic = *(uint32_t *)ptr;
	if (magic == MH_MAGIC_64 || magic == MH_CIGAM_64)
		return (find_symtab_64(ptr));
	if (magic != MH_MAGIC && magic != MH_CIGAM)
		return (NULL);
	i = -1;
	ncmds = ((t_mh *)(ptr))->ncmds;
	cmd = ptr + sizeof(t_mh);
	while (++i < ncmds)
	{
		if (((t_lc *)cmd)->cmd == LC_SYMTAB)
			return (cmd);
		cmd += ((t_lc *)cmd)->cmdsize;
	}
	return (NULL);
}

static t_list	*get_arch_symlist(t_file file, t_symtab *symtab)
{
	if (!symtab)
		return (NULL);
	if (file.arch == ARCH_64)
		return (get_symlist_64(file, symtab));
	if (file.arch == ARCH_32)
		return (get_symlist(file, symtab));
	return (NULL);
}

void			process_archive(t_file *file, t_nm nm)
{
	void		*ptr;
	void		*hdrptr;
	t_symtab	*symtab;
	t_list		*symlist;
	t_file		filetmp;

	ptr = file->ptr + SARMAG;
	ptr += ft_atoi(((t_arhdr *)ptr)->ar_size) + sizeof(t_arhdr);
	while (ptr < file->ptr + file->size)
	{
		ft_printf("\n%s(%s):\n", file->filename, (ptr + sizeof(t_arhdr)));
		hdrptr = ptr + sizeof(t_arhdr) + ft_atoi(((t_arhdr *)ptr)->ar_name + 3);
		filetmp = *file;
		filetmp.ptr = hdrptr;
		filetmp.arch = parse_magic(*(uint32_t *)hdrptr, hdrptr);
		find_sect_index(&filetmp);
		symtab = find_symtab(hdrptr);
		symlist = get_arch_symlist(filetmp, symtab);
		display_syms(symlist, nm, filetmp);
		ptr += ft_atoi(((t_arhdr *)ptr)->ar_size) + sizeof(t_arhdr);
	}
}