/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvega-g <alvega-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 11:31:28 by alvega-g          #+#    #+#             */
/*   Updated: 2024/05/11 13:04:44 by alvega-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_strdup(const char *s)
{
	int		i;
	char	*dest;

	i = 0;
	dest = (char *)malloc(sizeof(*s) * (ft_strlen(s) + 1));
	if (!dest)
		return (0);
	while (s[i])
	{
		dest[i] = s[i];
		i++;
	}
	dest[i] = 0;
	return (dest);
}

char	*ft_strndup(const char *s, int n)
{
	int		i;
	int		len;
	char	*dest;

	len = ft_strlen(s);
	if (n < len)
		len = n;
	i = 0;
	dest = (char *)malloc(sizeof(*s) * (len + 1));
	if (!dest)
		return (NULL);
	while (i < len)
	{
		dest[i] = s[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
