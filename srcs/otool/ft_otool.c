/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_otool.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagroy- <alagroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 13:30:47 by alagroy-          #+#    #+#             */
/*   Updated: 2021/03/11 13:10:02 by alagroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

void		display_file_name(t_file *file)
{
	if (file->arch == ARCH_32 || file->arch == ARCH_64)
		ft_printf("%s:\n", file->filename);
	if (file->arch == ARCHIVE)
		ft_printf("Archive : %s\n", file->filename);
}

void		process_file(t_file *file, t_otool *otool)
{
	if (file->arch == ARCH_32 || file->arch == ARCH_64)
		process_macho(file, otool);
	if (file->arch == ARCHIVE)
		process_archive(file, otool);
	if (file->arch == FAT_32 || file->arch == FAT_64)
		process_fat(file, otool);
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
		if (check_file(file, STDOUT_FILENO) == EXIT_SUCCESS)
		{
			display_file_name(&file);
			process_file(&file, &otool);
		}
		else
			error = file.arch;
		ft_freefile(file);
		if (error == E_BADFILE)
			break ;
	}
	ft_2dstrdel(&otool.filelist);
	return (EXIT_SUCCESS);
}
