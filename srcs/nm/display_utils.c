/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagroy- <alagroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/26 12:53:50 by alagroy-          #+#    #+#             */
/*   Updated: 2021/03/09 12:27:32 by alagroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

int			sym_is_global(t_sym *sym)
{
	if (sym->nlist.nlist64.n_type & N_EXT)
		return (1);
	return (0);
}

int			sym_is_undefined(t_sym *sym)
{
	if (((sym->nlist.nlist64.n_type) & N_TYPE) == N_UNDF)
		return (1);
	return (0);
}

static char	get_sect_type(int nsect, t_file *file)
{
	if (nsect == file->bss)
		return ('B');
	else if (nsect == file->text)
		return ('T');
	else if (nsect == file->data)
		return ('D');
	else
		return ('S');
}

char		get_sym_type(t_sym *sym, t_file *file)
{
	char	c;

	c = '?';
	if (((sym->nlist.nlist64.n_type) & N_TYPE) == N_STAB
		&& !sym->nlist.nlist64.n_type)
		c = '-';
	else if (sym_is_undefined(sym) && sym_is_global(sym)
		&& sym->nlist.nlist64.n_value)
		c = 'C';
	else if (sym_is_undefined(sym))
		c = 'U';
	else if (((sym->nlist.nlist64.n_type) & N_TYPE) == N_ABS)
		c = 'A';
	else if (((sym->nlist.nlist64.n_type) & N_TYPE) == N_INDR)
		c = 'I';
	else if (((sym->nlist.nlist64.n_type) & N_TYPE) == N_SECT
		&& sym->nlist.nlist64.n_sect)
		c = get_sect_type(sym->nlist.nlist64.n_sect, file);
	if (!sym_is_global(sym))
		c = ft_tolower(c);
	return (c);
}

uint64_t	get_sym_value(t_sym *sym, int width)
{
	if (width == 16)
		return (sym->nlist.nlist64.n_value);
	else
		return (sym->nlist.nlist.n_value);
}
