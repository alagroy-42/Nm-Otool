/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagroy- <alagroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 16:01:41 by alagroy-          #+#    #+#             */
/*   Updated: 2021/03/05 15:34:05 by alagroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

static int	check_display(t_sym *sym)
{
	int		type;

	type = (sym->nlist.nlist64.n_type) & N_TYPE;
	if ((type != N_INDR && type != N_UNDF && type != N_ABS && type != N_SECT)
		|| !sym->name || sym->name[0] == 0 || (type == N_UNDF
			&& !sym_is_global(sym)))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

void		display_syms(t_sym *sym_list, t_nm nm, t_file file, uint32_t nsyms)
{
	int			w;
	uint32_t	i;

	w = 16;
	if (file.arch == ARCH_32)
		w = 8;
	i = -1;
	while (++i < nsyms)
	{
		if ((nm.g && !sym_is_global(&sym_list[i])) || (nm.u &&
			!sym_is_undefined(&sym_list[i])) || check_display(&sym_list[i]))
			continue ;
		if (nm.j || nm.u)
			ft_putendl(sym_list[i].name);
		else if (!sym_is_undefined(&sym_list[i]))
			ft_printf("%0*llx %c %s\n", w, get_sym_value(&sym_list[i], w),
				get_sym_type(&sym_list[i], &file),
				sym_list[i].name);
		else
			ft_printf("%*c %c %s\n", w, ' ', get_sym_type(&sym_list[i], &file),
				sym_list[i].name);
	}
	// free_syms(sym_list);
}
