/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frangome <frangome@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 16:59:06 by frangome          #+#    #+#             */
/*   Updated: 2023/04/25 20:29:01 by frangome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	int		size;
	int		c;
	char	*str;

	size = 0;
	while (s[size])
		size++;
	str = malloc(size + 1);
	if (!str)
		return (0);
	c = 0;
	while (c < size)
	{
		str[c] = s[c];
		c++;
	}
	str[c] = 0;
	return (str);
}
