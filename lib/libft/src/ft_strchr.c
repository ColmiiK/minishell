/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvega-g <alvega-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 18:37:26 by alvega-g          #+#    #+#             */
/*   Updated: 2024/01/18 17:55:50 by alvega-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (c > 255)
		c -= 256;
	while (s[i])
	{
		if (c == s[i])
			return ((char *)&s[i]);
		else
			i++;
	}
	if (c == '\0')
		return ((char *)&s[i++]);
	return (0);
}
