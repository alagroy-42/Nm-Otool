/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symtab.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagroy- <alagroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 13:13:52 by alagroy-          #+#    #+#             */
/*   Updated: 2021/03/05 17:24:32 by alagroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

static void		sort_syms(t_sym *sym_list, int nsyms)
{
	int		i;
	int		j;
	t_sym	tmp;

	i = -1;
	while (++i < nsyms)
	{
		j= -1;
		while (++j < nsyms - 1)
		{
			if (ft_strcmp(sym_list[j].name, sym_list[j + 1].name) > 0
				|| (ft_strcmp(sym_list[j].name, sym_list[j + 1].name) == 0
					&& sym_list[j].nlist.nlist64.n_value
					> sym_list[j].nlist.nlist64.n_value))
			{
				tmp = sym_list[j];
				sym_list[j] = sym_list[j+ 1];
				sym_list[j + 1] = tmp;
			}
		}
	}
}

static void		swap_nlist(t_nlist *nlist, t_file *file)
{
	if (file->arch == ARCH_32)
	{
		nlist->nlist.n_un.n_strx = get_uint32(nlist->nlist.n_un.n_strx,
			file->endian);
		nlist->nlist.n_value = get_uint32(nlist->nlist.n_value, file->endian);
	}
	else if (file->arch == ARCH_64)
	{
		nlist->nlist64.n_un.n_strx = get_uint32(nlist->nlist64.n_un.n_strx,
			file->endian);
		nlist->nlist64.n_value = get_uint64(nlist->nlist64.n_value,
			file->endian);
	}
}

static t_sym	create_sym(void *nlist_ptr, char *strtab, t_file *file,
					uint32_t strsize)
{
	t_sym	sym;

	ft_bzero(&sym, sizeof(t_sym));
	if (file->arch == ARCH_64)
	{
		ft_memcpy(&sym.nlist, nlist_ptr, sizeof(t_nlist64));
		swap_nlist(&sym.nlist, file);
		if (sym.nlist.nlist64.n_un.n_strx < strsize)
			sym.name = ft_strdup(strtab
				+ sym.nlist.nlist64.n_un.n_strx);
		else
			sym.name = ft_strdup("bad string index");
	}
	else if (file->arch == ARCH_32)
	{
		ft_memcpy(&sym.nlist, nlist_ptr, sizeof(t_nlist32));
		swap_nlist(&sym.nlist, file);
		if (sym.nlist.nlist.n_un.n_strx < strsize)
			sym.name = ft_strdup(strtab
				+ sym.nlist.nlist.n_un.n_strx);
		else
			sym.name = ft_strdup("bad string index");
	}
	return (sym);
}

t_sym			*get_symlist(t_file file, t_symtab *symtab_lc)
{
	t_sym		*symlist;
	t_nlist32	*symtab;
	t_sym		sym;
	uint32_t	i;
	uint32_t	nsyms;

	i = -1;
	nsyms = get_uint32(symtab_lc->nsyms, file.endian);
	if (!(symlist = (t_sym *)malloc(nsyms * sizeof(t_sym))))
		return(NULL);
	symtab = file.ptr + get_uint32(symtab_lc->symoff, file.endian);
	while (++i < nsyms)
	{
		sym = create_sym(symtab + i, file.ptr + get_uint32(symtab_lc->stroff,
				file.endian), &file, get_uint32(symtab_lc->strsize,
					file.endian));
		symlist[i] = sym;
	}
	sort_syms(symlist, nsyms);
	return (symlist);
}


t_sym			*get_symlist_64(t_file file, t_symtab *symtab_lc)
{
	t_sym		*symlist;
	t_nlist64	*symtab;
	t_sym		sym;
	uint32_t	i;
	uint32_t	nsyms;

	i = -1;
	nsyms = get_uint32(symtab_lc->nsyms, file.endian);
	if (!(symlist = (t_sym *)malloc(nsyms * sizeof(t_sym))))
		return(NULL);
	symtab = file.ptr + get_uint32(symtab_lc->symoff, file.endian);
	while (++i < nsyms)
	{
		sym = create_sym(symtab + i, file.ptr + get_uint32(symtab_lc->stroff,
				file.endian), &file, get_uint32(symtab_lc->strsize,
					file.endian));
		symlist[i] = sym;
	}
	sort_syms(symlist, nsyms);
	return (symlist);
}
