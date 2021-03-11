/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagroy- <alagroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 12:17:45 by alagroy-          #+#    #+#             */
/*   Updated: 2021/03/11 13:12:07 by alagroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

static void	get_ppc_line(char *line, void *ptr, void *end, t_file *file)
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
		i_text++;
		line[i_line + 2] = convert[*(uint8_t *)(ptr + i_text) / 16];
		line[i_line + 3] = convert[*(uint8_t *)(ptr + i_text) % 16];
		i_text++;
		line[i_line + 4] = convert[*(uint8_t *)(ptr + i_text) / 16];
		line[i_line + 5] = convert[*(uint8_t *)(ptr + i_text) % 16];
		i_text++;
		line[i_line + 6] = convert[*(uint8_t *)(ptr + i_text) / 16];
		line[i_line + 7] = convert[*(uint8_t *)(ptr + i_text) % 16];
		line[i_line + 8] = ' ';
		i_line += 9;
	}
	line[i_line] = '\n';
}

void		get_line(char *line, void *ptr, void *end, t_file *file)
{
	int			i_line;
	int			i_text;
	static char	convert[] = "0123456789abcdef";

	if (get_uint32(*(cpu_type_t *)(file->ptr + sizeof(uint32_t)),
			file->endian) == CPU_TYPE_POWERPC)
		return (get_ppc_line(line, ptr, end, file));
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
