/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frangome <frangome@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 18:09:37 by frangome          #+#    #+#             */
/*   Updated: 2023/04/26 18:07:34 by frangome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, void *src, size_t n)
{
	char		*s;
	char		*d;
	size_t		c;

	s = (char *)src;
	d = (char *)dest;
	if (!dest && !src)
		return (0);
	c = 0;
	if (d > s)
	{
		while (n-- > 0)
			d[n] = s[n];
	}
	else
	{
		while (c < n)
		{
			d[c] = s[c];
			c++;
		}
	}
	return (dest);
}
