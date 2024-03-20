/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frangome <frangome@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 15:25:43 by fran              #+#    #+#             */
/*   Updated: 2023/04/24 15:58:43 by frangome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	get_start(char const *s1, char const *set)
{
	int	len;
	int	c;

	len = ft_strlen(s1);
	c = 0;
	while (c < len)
	{
		if (ft_strchr(set, s1[c]) == 0)
			break ;
		c++;
	}
	return (c);
}

int	get_end(char const *s1, char const *set)
{
	int	len;

	len = ft_strlen(s1);
	while (len > 0)
	{
		if (ft_strchr(set, s1[len - 1]) == 0)
			break ;
		len--;
	}
	return (len);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		end;
	char	*res;

	if (!s1)
		return (0);
	if (!set)
		return (ft_strdup(s1));
	start = get_start(s1, set);
	end = get_end(s1, set);
	if (start >= end)
		return (ft_strdup(""));
	res = malloc(end - start + 1);
	if (!res)
		return (0);
	ft_strlcpy(res, (char *)(s1 + start), end - start + 1);
	return (res);
}
