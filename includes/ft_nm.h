/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagroy- <alagroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 13:32:52 by alagroy-          #+#    #+#             */
/*   Updated: 2021/02/26 13:29:12 by alagroy-         ###   ########.fr       */
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
	char		g;
	char		j;
	char		u;
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
t_list							*get_symlist_64(t_file file, t_symtab *symtab);
void							display_syms(t_list *list, t_nm nm, t_file f);
int								sym_is_global(t_sym *sym);
int								sym_is_undefined(t_sym *sym);
char							get_sym_type(t_sym *sym);
uint64_t						get_sym_value(t_sym *sym, int width);

#endif
