/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_otool.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagroy- <alagroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 13:33:42 by alagroy-          #+#    #+#             */
/*   Updated: 2021/03/11 12:57:48 by alagroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_OTOOL_H
# define FT_OTOOL_H
# include "shared.h"

# define ERROR_ARGS "no arguments specified\nusage : ./ft_otool -[th] files"

typedef struct		s_otool
{
	uint8_t		h;
	uint8_t		t;
	char		**filelist;
}					t_otool;

typedef union		u_sect
{
	t_sect		*section;
	t_sect64	*section64;
}					t_usect;

t_otool				parse_args(int ac, char **av);
void				process_macho(t_file *file, t_otool *otool);
void				display(t_file *file, t_otool *otool, t_usect *text);
void				get_line(char *line, void *ptr, void *end, t_file *file);
void				process_file(t_file *file, t_otool *otool);
void				process_archive(t_file *file, t_otool *otool);
void				process_fat(t_file *file, t_otool *otool);
void				display_file_name(t_file *file);

#endif
