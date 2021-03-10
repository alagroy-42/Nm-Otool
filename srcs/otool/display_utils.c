/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagroy- <alagroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 12:17:45 by alagroy-          #+#    #+#             */
/*   Updated: 2021/03/10 16:19:20 by alagroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

void		get_line(char *line, void *ptr, void *end, t_file *file)
{
	int			i_line;
	int			i_text;
	static char	convert[] = "0123456789abcdef";

	i_line = 0;
	i_text = -1;
	ft_bzero(line, 49);
	while (i_line < 48 && ++i_text < 16 && ptr + i_text < end
		&& ptr < file->end)
	{
		line[i_line] = convert[*(uint8_t *)(ptr + i_text) / 16];
		line[i_line + 1] = convert[*(uint8_t *)(ptr + i_text) % 16];
		line[i_line + 2] = ' ';
		i_line += 3;
	}
	line[i_line] = '\n';
}