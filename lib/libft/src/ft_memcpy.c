/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frangome <frangome@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 17:59:19 by frangome          #+#    #+#             */
/*   Updated: 2023/04/26 18:07:06 by frangome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	c;

	c = 0;
	if (!dest && !src)
		return (0);
	while (c < n)
	{
		*(unsigned char *)dest = *(unsigned char *)src;
		dest++;
		src++;
		c++;
	}
	return (dest - c);
}
