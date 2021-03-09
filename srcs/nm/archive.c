/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   archive.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagroy- <alagroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 14:45:40 by alagroy-          #+#    #+#             */
/*   Updated: 2021/03/09 15:29:11 by alagroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

static char		*get_member_name(void *ptr)
{
	int		i;

	if (!ft_strncmp(((t_arhdr *)ptr)->ar_name, "#1/", 3))
		return (ptr + sizeof(t_arhdr));
	else
	{
		i = 16;
		while (--i && ((t_arhdr *)ptr)->ar_name[i] == ' ')
			((t_arhdr *)ptr)->ar_name[i] = 0;
		return (((t_arhdr *)ptr)->ar_name);
	}
}

void			process_archive(t_file *file, t_nm nm)
{
	void		*ptr;
	void		*hdrptr;
	t_file		filetmp;

	ptr = file->ptr + SARMAG;
	ptr += ft_atoi(((t_arhdr *)ptr)->ar_size) + sizeof(t_arhdr);
	while (ptr < file->end)
	{
		ft_printf("\n%s(%s):\n", file->filename, get_member_name(ptr));
		hdrptr = ptr + sizeof(t_arhdr) + ft_atoi(((t_arhdr *)ptr)->ar_name + 3);
		filetmp = *file;
		filetmp.ptr = hdrptr;
		parse_magic(*(uint32_t *)hdrptr, &filetmp);
		ptr += ft_atoi(((t_arhdr *)ptr)->ar_size) + sizeof(t_arhdr);
		ft_process_file(filetmp, nm);
	}
}
