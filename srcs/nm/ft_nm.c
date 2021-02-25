/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagroy- <alagroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 13:29:07 by alagroy-          #+#    #+#             */
/*   Updated: 2021/02/25 11:24:56 by alagroy-         ###   ########.fr       */
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
		check_file(file);
		ft_freefile(file);
	}
	return (0);
}
