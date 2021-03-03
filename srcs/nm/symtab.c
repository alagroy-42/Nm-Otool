/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symtab.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagroy- <alagroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 13:13:52 by alagroy-          #+#    #+#             */
/*   Updated: 2021/03/03 16:36:07 by alagroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

static int		compare_syms(t_list *elem1, t_list *elem2)
{
	if (!elem1 || !elem2)
		return (0);
	if (ft_strcmp(((t_sym *)elem1->content)->name,
		((t_sym *)elem2->content)->name) > 0)
		return (1);
	if (ft_strcmp(((t_sym *)elem1->content)->name,
		((t_sym *)elem2->content)->name) == 0
		&& ((t_sym *)elem1->content)->nlist.nlist64.n_value
		> ((t_sym *)elem1->content)->nlist.nlist64.n_value)
		return (1);
	return (0);
}

static t_sym	create_sym(void *nlist_ptr, char *strtab, int arch,
					uint32_t strsize)
{
	t_sym	sym;

	ft_bzero(&sym, sizeof(t_sym));
	if (arch == ARCH_64)
	{
		if (((t_nlist64 *)nlist_ptr)->n_un.n_strx < strsize)
			sym.name = ft_strdup(strtab
				+ ((t_nlist64 *)nlist_ptr)->n_un.n_strx);
		else
			sym.name = ft_strdup("bad string index");
		ft_memcpy(&sym.nlist, nlist_ptr, sizeof(t_nlist64));
	}
	else if (arch == ARCH_32)
	{
		if (((t_nlist32 *)nlist_ptr)->n_un.n_strx < strsize)
			sym.name = ft_strdup(strtab
				+ ((t_nlist32 *)nlist_ptr)->n_un.n_strx);
		else
			sym.name = ft_strdup("bad string index");
		ft_memcpy(&sym.nlist, nlist_ptr, sizeof(t_nlist32));
	}
	return (sym);
}

t_list			*get_symlist(t_file file, t_symtab *symtab_lc)
{
	t_list		*beg;
	t_list		*elem;
	t_nlist32	*symtab;
	t_sym		sym;
	uint32_t	i;

	i = -1;
	beg = NULL;
	symtab = file.ptr + symtab_lc->symoff;
	while (++i < symtab_lc->nsyms)
	{
		sym = create_sym(symtab + i, file.ptr + symtab_lc->stroff, file.arch,
			symtab_lc->strsize);
		if (!(elem = ft_lstnew(&sym, sizeof(t_sym))))
		{
			//do leaks
			break ;
		}
		ft_lstend(&beg, elem);
	}
	ft_lstsort(beg, compare_syms);
	return (beg);
}


t_list			*get_symlist_64(t_file file, t_symtab *symtab_lc)
{
	t_list		*beg;
	t_list		*elem;
	t_nlist64	*symtab;
	t_sym		sym;
	uint32_t	i;

	i = -1;
	beg = NULL;
	symtab = file.ptr + symtab_lc->symoff;
	while (++i < symtab_lc->nsyms)
	{
		sym = create_sym(symtab + i, file.ptr + symtab_lc->stroff, file.arch,
			symtab_lc->strsize);
		if (!(elem = ft_lstnew(&sym, sizeof(t_sym))))
		{
			//do leaks
			break ;
		}
		ft_lstend(&beg, elem);
	}
	ft_lstsort(beg, compare_syms);
	return (beg);
}
