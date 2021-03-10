/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_otool.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagroy- <alagroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 13:30:47 by alagroy-          #+#    #+#             */
/*   Updated: 2021/03/09 17:02:33 by alagroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

static void	process_file(t_file *file, t_otool *otool)
{
	if (file->arch == ARCH_32 || file->arch == ARCH_64)
		process_macho(file, otool);
}

int			main(int ac, char **av)
{
	t_otool	otool;
	t_file	file;
	int		i;
	uint8_t	error;

	i = -1;
	otool = parse_args(ac, av);
	while (otool.filelist[++i])
	{
		file = load_file(otool.filelist[i]);
		if (check_file(file) == EXIT_SUCCESS)
			process_file(&file, &otool);
		else
			error = file.arch;
		ft_freefile(file);
		if (error == E_BADFILE)
			break ;
	}
	return (EXIT_SUCCESS);
}
