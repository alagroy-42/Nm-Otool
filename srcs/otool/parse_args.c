/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagroy- <alagroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 16:35:21 by alagroy-          #+#    #+#             */
/*   Updated: 2021/03/11 13:12:37 by alagroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

static void		enable_opt(t_otool *otool, char opt)
{
	if (opt == 'h')
		otool->h = 1;
	if (opt == 't')
		otool->t = 1;
}

static t_otool	get_options(int ac, char **av, int *offset)
{
	t_otool	otool;
	int		i;
	int		j;

	i = 0;
	ft_bzero(&otool, sizeof(t_otool));
	while (++i < ac && ft_strcmp(av[i], "--") && av[i][0] == '-')
	{
		j = 0;
		while (av[i][++j] != '\0')
		{
			if (ft_strchr("th", av[i][j]))
				enable_opt(&otool, av[i][j]);
			else
			{
				ft_dprintf(2, "ft_otool: Unknown char '%c' in flag %s.\n",
					av[i][j], av[i]);
				exit(EXIT_FAILURE);
			}
		}
	}
	if (i < ac && !ft_strcmp(av[i], "--"))
		i++;
	*offset = i - 1;
	return (otool);
}

t_otool			parse_args(int ac, char **av)
{
	t_otool	otool;
	int		offset;

	otool = get_options(ac, av, &offset);
	if (!(otool.t || otool.h))
	{
		ft_dprintf(2, "ft_otool: error : %s\n", ERROR_ARGS);
		exit(EXIT_FAILURE);
	}
	otool.filelist = get_files(ac, av, offset);
	return (otool);
}
