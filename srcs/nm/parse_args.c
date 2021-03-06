/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagroy- <alagroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 15:15:22 by alagroy-          #+#    #+#             */
/*   Updated: 2021/03/10 12:59:37 by alagroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

static void	check_opt(t_nm *nm, char opt)
{
	if ((opt == 'g' && nm->g) || (opt == 'u' && nm->u) || (opt == 'j' && nm->j))
	{
		ft_dprintf(2, "ft_nm: -%c option : may only occur 0 or 1 times\n", opt);
		exit(EXIT_FAILURE);
	}
	if (opt == 'g')
		nm->g = 1;
	if (opt == 'j')
		nm->j = 1;
	if (opt == 'u')
		nm->u = 1;
	if (opt == 'h')
	{
		ft_putendl("ft_nm: usage ./ftnm [-gjuh] filelist");
		exit(EXIT_SUCCESS);
	}
}

static t_nm	get_options(int ac, char **av, int *offset)
{
	t_nm	nm;
	int		i;
	int		j;

	i = 0;
	ft_bzero(&nm, sizeof(t_nm));
	while (++i < ac && ft_strcmp(av[i], "--") && av[i][0] == '-')
	{
		j = 0;
		while (av[i][++j] != '\0')
		{
			if (ft_strchr("gujh", av[i][j]))
				check_opt(&nm, av[i][j]);
			else
			{
				ft_dprintf(2, "ft_nm: Unknown command line argument '%s'.\n",
					av[i]);
				exit(EXIT_FAILURE);
			}
		}
	}
	if (i < ac && !ft_strcmp(av[i], "--"))
		i++;
	*offset = i - 1;
	return (nm);
}

t_nm		parse_args(int ac, char **av)
{
	t_nm	nm;
	int		offset;

	nm = get_options(ac, av, &offset);
	nm.filelist = get_files(ac, av, offset);
	return (nm);
}
