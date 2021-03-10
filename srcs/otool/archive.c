/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   archive.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagroy- <alagroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 16:37:47 by alagroy-          #+#    #+#             */
/*   Updated: 2021/03/10 16:54:48 by alagroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

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

void		process_archive(t_file *file, t_otool *otool)
{
	void	*ptr;
	t_file	filetmp;
	void	*hdr;

	ptr = file->ptr + SARMAG;
	ptr += ft_atoi(((t_arhdr *)ptr)->ar_size) + sizeof(t_arhdr);
	while (ptr < file->end)
	{
		ft_printf("%s(%s):\n", file->filename, get_member_name(ptr));
		ft_memcpy(&filetmp, file, sizeof(t_file));
		hdr = ptr + sizeof(t_arhdr) + ft_atoi(((t_arhdr *)ptr)->ar_name + 3);
		filetmp.ptr = hdr;
		parse_magic(*(uint32_t *)filetmp.ptr, &filetmp);
		process_file(&filetmp, otool);
		ptr += ft_atoi(((t_arhdr *)ptr)->ar_size) + sizeof(t_arhdr);
	}
}