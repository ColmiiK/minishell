/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fran <fran@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 14:59:47 by fran              #+#    #+#             */
/*   Updated: 2023/04/23 15:23:20 by fran             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*res;
	int		size_s1;
	int		size_s2;
	int		c;

	size_s1 = ft_strlen(s1);
	size_s2 = ft_strlen(s2);
	res = malloc(size_s1 + size_s2 + 1);
	if (!res)
		return (NULL);
	c = 0;
	while (c < size_s1)
	{
		res[c] = s1[c];
		c++;
	}
	c = 0;
	while (c < size_s2)
	{
		res[c + size_s1] = s2[c];
		c++;
	}
	res[c + size_s1] = '\0';
	return (res);
}
