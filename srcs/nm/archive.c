/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   archive.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagroy- <alagroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 14:45:40 by alagroy-          #+#    #+#             */
/*   Updated: 2021/03/05 15:58:24 by alagroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

static t_symtab	*find_symtab_64(t_file *file)
{
	void	*cmd;
	int		i;
	int		ncmds;

	i = -1;
	ncmds = get_uint32(((t_mh_64 *)(file->ptr))->ncmds, file->endian);
	cmd = file->ptr + sizeof(t_mh_64);
	while (++i < ncmds)
	{
		if (get_uint32(((t_lc *)cmd)->cmd, file->endian) == LC_SYMTAB)
			return (cmd);
		cmd += get_uint32(((t_lc *)cmd)->cmdsize, file->endian);
	}
	return (NULL);
}

static t_symtab	*find_symtab(t_file *file)
{
	void		*cmd;
	int			i;
	int			ncmds;

	if (file->arch == ARCH_64)
		return (find_symtab_64(file->ptr));
	if (file->arch != ARCH_64)
		return (NULL);
	i = -1;
	ncmds = get_uint32(((t_mh *)(file->ptr))->ncmds, file->endian);
	cmd = file->ptr + sizeof(t_mh);
	while (++i < ncmds)
	{
		if (get_uint32(((t_lc *)cmd)->cmd, file->endian) == LC_SYMTAB)
			return (cmd);
		cmd += get_uint32(((t_lc *)cmd)->cmdsize, file->endian);
	}
	return (NULL);
}

static t_sym	*get_arch_symlist(t_file file, t_symtab *symtab)
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
	t_sym		*symlist;
	t_file		filetmp;

	ptr = file->ptr + SARMAG;
	ptr += ft_atoi(((t_arhdr *)ptr)->ar_size) + sizeof(t_arhdr);
	while (ptr < file->ptr + file->size)
	{
		ft_printf("\n%s(%s):\n", file->filename, (ptr + sizeof(t_arhdr)));
		hdrptr = ptr + sizeof(t_arhdr) + ft_atoi(((t_arhdr *)ptr)->ar_name + 3);
		filetmp = *file;
		filetmp.ptr = hdrptr;
		parse_magic(*(uint32_t *)hdrptr, &filetmp);
		find_sect_index(&filetmp);
		if (!((symtab = find_symtab(&filetmp))
			&& (symlist = get_arch_symlist(filetmp, symtab))))
			continue ;
		display_syms(symlist, nm, filetmp, get_uint32(symtab->nsyms,
			file->endian));
		ptr += ft_atoi(((t_arhdr *)ptr)->ar_size) + sizeof(t_arhdr);
	}
}