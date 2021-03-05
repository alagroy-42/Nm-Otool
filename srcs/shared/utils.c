/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagroy- <alagroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 14:17:43 by alagroy-          #+#    #+#             */
/*   Updated: 2021/03/05 16:58:56 by alagroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shared.h"

t_cpu		g_translation_tab[] =\
{
	{CPU_TYPE_ANY, "any"},
	{CPU_TYPE_VAX, "vax"},
	{CPU_TYPE_MC680x0, "mc680x0"},
	{CPU_TYPE_I386, "i386"},
	{CPU_TYPE_X86, "x86"},
	{CPU_TYPE_X86_64, "x86_64"},
	{CPU_TYPE_MC98000, "mc98000"},
	{CPU_TYPE_HPPA, "hppa"},
	{CPU_TYPE_ARM64, "arm64"},
	{CPU_TYPE_ARM64_32, "arm64_32"},
	{CPU_TYPE_ARM, "arm"},
	{CPU_TYPE_MC88000, "mc88000"},
	{CPU_TYPE_SPARC, "sparc"},
	{CPU_TYPE_I860, "i860"},
	{CPU_TYPE_POWERPC, "ppc"},
	{CPU_TYPE_POWERPC64, "ppc64"},
	{-5, "unknown"}
};

void		ft_freefile(t_file file)
{
	munmap(file.ptr, file.size + 1);
	ft_strdel(&file.filename);
	close(file.fd);
}

char		*get_cpu_type_name(cpu_type_t type)
{
	int		i;

	i = -1;
	while (g_translation_tab[++i].id != -5)
		if (type == g_translation_tab[i].id)
			return (g_translation_tab[i].name);
	return (g_translation_tab[i].name);
}
