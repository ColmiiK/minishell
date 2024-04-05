/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvega-g <alvega-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 13:12:11 by alvega-g          #+#    #+#             */
/*   Updated: 2024/01/18 17:56:29 by alvega-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	unsigned int	j;
	char			*subs;

	i = 0;
	j = 0;
	if (ft_strlen(s) < len)
		len = ft_strlen(s);
	subs = (char *)malloc(sizeof(char) * len + 1);
	if (!subs)
		return (0);
	while (s[i] && i < start)
		i++;
	while (s[i] && j < len)
	{
		subs[j] = s[i];
		i++;
		j++;
	}
	subs[j] = 0;
	return (subs);
}
