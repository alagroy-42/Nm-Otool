/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagroy- <alagroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/26 12:53:50 by alagroy-          #+#    #+#             */
/*   Updated: 2021/02/26 15:49:33 by alagroy-         ###   ########.fr       */
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

char		get_sym_type(t_sym *sym)
{
	char	c;

	if (sym_is_undefined(sym))
		c = 'U';
	else if (((sym->nlist.nlist64.n_type) & N_TYPE) == N_ABS)
		c = 'A';
	else
		c = 'T';
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
