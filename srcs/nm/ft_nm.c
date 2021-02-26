/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagroy- <alagroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 13:29:07 by alagroy-          #+#    #+#             */
/*   Updated: 2021/02/25 12:37:27 by alagroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

int		main(int ac, char **av)
{
	t_file		file;
	t_nm		nm;
	int			i;

	i = -1;
	nm = parse_args(ac, av);
	while (nm.filelist[++i])
	{
		file = load_file(nm.filelist[i]);
		if (check_file(file) == EXIT_SUCCESS)
			ft_process_file(file, nm);
		ft_freefile(file);
	}
	ft_2dstrdel(&nm.filelist);
	return (0);
}
