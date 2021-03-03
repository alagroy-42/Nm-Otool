/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shared.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagroy- <alagroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 13:34:12 by alagroy-          #+#    #+#             */
/*   Updated: 2021/03/03 13:54:52 by alagroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHARED_H
# define SHARED_H

# include <mach-o/loader.h>
# include <mach-o/nlist.h>
# include <mach-o/fat.h>
# include <mach-o/ranlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/mman.h>
# include <ar.h>
# include <fcntl.h>
# include "libft.h"
# include "ft_printf.h"

# define E_BADFILE 0
# define ARCH_64 1
# define ARCH_32 2
# define ARCHIVE 3
# define FAT_32 4
# define FAT_64 5
# define E_NOOBJ 6
# define E_NOMEM 7

# define ERROR_OPEN "File cannot be opened, check its existence and its rights"
# define ERROR_MAGIC "The file was not recognized as a valid object file"

typedef struct mach_header			t_mh;
typedef struct mach_header_64		t_mh_64;
typedef struct load_command			t_lc;
typedef struct segment_command		t_seg;
typedef struct segment_command_64	t_seg64;
typedef struct section				t_sect;
typedef struct section_64			t_sect64;
typedef struct ranlib				t_rlib;
typedef struct ar_hdr				t_arhdr;

typedef struct						s_file
{
	int			fd;
	void		*ptr;
	off_t		size;
	uint32_t	magic;
	int			arch;
	int			text;
	int			data;
	int			bss;
	char		*filename;
}									t_file;

t_file								load_file(char *filname);
void								ft_freefile(t_file file);
int									check_file(t_file file);
int									parse_magic(uint32_t magic, void *ptr);

#endif
