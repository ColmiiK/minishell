/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvega-g <alvega-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 17:08:40 by alvega-g          #+#    #+#             */
/*   Updated: 2024/01/18 17:55:24 by alvega-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	int				i;
	int				j;
	unsigned char	*c1;
	unsigned char	*c2;

	i = 0;
	j = 0;
	c1 = (unsigned char *)s1;
	c2 = (unsigned char *)s2;
	if (n == 0)
		return (0);
	while ((n - 1) && (c1[i] == c2[j]))
	{
		i++;
		j++;
		n--;
	}
	return (c1[i] - c2[j]);
}
