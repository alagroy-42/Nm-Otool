/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symtab.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagroy- <alagroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 13:13:52 by alagroy-          #+#    #+#             */
/*   Updated: 2021/03/01 16:09:24 by alagroy-         ###   ########.fr       */
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
	return (0);
}

static t_sym	create_sym(void *nlist_ptr, char *strtab, int arch)
{
	t_sym	sym;

	ft_bzero(&sym, sizeof(t_sym));
	if (arch == ARCH_64)
	{
		sym.name = ft_strdup(strtab + ((t_nlist64 *)nlist_ptr)->n_un.n_strx);
		ft_memcpy(&sym.nlist, nlist_ptr, sizeof(t_nlist64));
	}
	else if (arch == ARCH_32)
	{
		sym.name = ft_strdup(strtab + ((t_nlist32 *)nlist_ptr)->n_un.n_strx);
		ft_memcpy(&sym.nlist, nlist_ptr, sizeof(t_nlist32));
	}
	return (sym);
}

t_list			*get_symlist(t_file file, t_symtab *symtab_lc)
{
	t_list		*beg;
	t_list		*elem;
	t_nlist32		*symtab;
	t_sym		sym;
	uint32_t	i;

	i = -1;
	beg = NULL;
	symtab = file.ptr + symtab_lc->symoff;
	while (++i < symtab_lc->nsyms)
	{
		sym = create_sym(symtab + i, file.ptr + symtab_lc->stroff, ARCH_32);
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
		sym = create_sym(symtab + i, file.ptr + symtab_lc->stroff, ARCH_64);
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
