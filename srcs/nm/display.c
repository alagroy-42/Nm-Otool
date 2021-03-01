/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagroy- <alagroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 16:01:41 by alagroy-          #+#    #+#             */
/*   Updated: 2021/03/01 13:15:18 by alagroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

void		display_syms(t_list *list, t_nm nm, t_file file)
{
	int		w;

	w = 16;
	if (file.arch == ARCH_32)
		w = 8;
	while (list)
	{
		if ((nm.g && !sym_is_global(list->content))
			|| (nm.u && !sym_is_undefined(list->content)))
		{
			list = list->next;
			continue ;
		}
		if (nm.j || nm.u)
			ft_putendl(((t_sym *)list->content)->name);
		else if (!sym_is_undefined(list->content))
			ft_printf("%0*llx %c %s\n", w, get_sym_value(list->content, w),
				get_sym_type(list->content, &file),
				((t_sym *)list->content)->name);
		else
			ft_printf("%*c %c %s\n", w, ' ', get_sym_type(list->content, &file),
				((t_sym *)list->content)->name);
		list = list->next;
	}
}
