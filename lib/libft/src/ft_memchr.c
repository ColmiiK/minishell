/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frangome <frangome@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 15:51:49 by frangome          #+#    #+#             */
/*   Updated: 2023/04/26 18:06:12 by frangome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t		count;
	char		*str2;

	str2 = (char *)s;
	count = 0;
	while (count < n)
	{
		if (*(unsigned char *)str2 == (unsigned char)c)
			return ((void *)str2);
		str2++;
		count++;
	}
	return (0);
}
