/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   endian.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagroy- <alagroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 12:31:20 by alagroy-          #+#    #+#             */
/*   Updated: 2021/03/05 13:13:10 by alagroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shared.h"

static uint32_t	swap_uint32(uint32_t byte)
{
	byte = ((byte << 8) & 0xFF00FF00 ) | ((byte >> 8) & 0xFF00FF ); 
    return (byte << 16) | (byte >> 16);
}

static uint64_t	swap_uint64(uint64_t byte)
{
	byte = ((byte << 8) & 0xFF00FF00FF00FF00ULL )
		| ((byte >> 8) & 0x00FF00FF00FF00FFULL );
    byte = ((byte << 16) & 0xFFFF0000FFFF0000ULL )
		| ((byte >> 16) & 0x0000FFFF0000FFFFULL );
    return (byte << 32) | (byte >> 32);
}

uint32_t		get_uint32(uint32_t byte, uint8_t endian)
{
	if (endian == LENDIAN)
		return (swap_uint32(byte));
	return (byte);
}

uint64_t		get_uint64(uint64_t byte, uint8_t endian)
{
	if (endian == LENDIAN)
		return (swap_uint64(byte));
	return (byte);
}
