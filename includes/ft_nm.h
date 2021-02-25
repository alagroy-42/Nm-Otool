/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagroy- <alagroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 13:32:52 by alagroy-          #+#    #+#             */
/*   Updated: 2021/02/24 15:21:26 by alagroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_NM_H
# define FT_NM_H
# include "shared.h"

typedef struct		s_nm
{
	char	g;
	char	j;
	char	u;
	char	**filelist;
}					t_nm;

t_nm				parse_args(int ac, char **av);

#endif
