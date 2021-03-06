/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagroy- <alagroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 13:32:52 by alagroy-          #+#    #+#             */
/*   Updated: 2021/03/05 16:58:42 by alagroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_NM_H
# define FT_NM_H
# include "shared.h"
# include <mach-o/stab.h>

typedef struct symtab_command	t_symtab;
typedef struct nlist			t_nlist32;
typedef struct nlist_64			t_nlist64;

typedef struct					s_nm
{
	uint8_t		g;
	uint8_t		j;
	uint8_t		u;
	char		**filelist;
}								t_nm;

typedef union					u_nlist
{
	t_nlist32	nlist;
	t_nlist64	nlist64;
}								t_nlist;

typedef struct					s_sym
{
	char		*name;
	t_nlist		nlist;
}								t_sym;

t_nm							parse_args(int ac, char **av);
void							ft_process_file(t_file file, t_nm nm);
t_sym							*get_symlist_64(t_file file, t_symtab *symtab);
t_sym							*get_symlist(t_file file, t_symtab *symtab);
void							display_syms(t_sym *list, t_nm nm, t_file file,
									uint32_t nsyms);
int								sym_is_global(t_sym *sym);
int								sym_is_undefined(t_sym *sym);
char							get_sym_type(t_sym *sym, t_file *file);
uint64_t						get_sym_value(t_sym *sym, int width);
void							find_sect_index(t_file *file);
void							process_archive(t_file *file, t_nm nm);
void							process_fat(t_file *file, t_nm nm);
void							ft_process_mo(t_file file, t_nm nm);

#endif
