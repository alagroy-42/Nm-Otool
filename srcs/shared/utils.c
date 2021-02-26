/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagroy- <alagroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 14:17:43 by alagroy-          #+#    #+#             */
/*   Updated: 2021/02/25 11:44:54 by alagroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shared.h"

void		ft_freefile(t_file file)
{
	munmap(file.ptr, file.size);
	ft_strdel(&file.filename);
	close(file.fd);
}
