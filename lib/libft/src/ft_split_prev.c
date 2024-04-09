/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_prev.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvega-g <alvega-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 12:55:46 by alvega-g          #+#    #+#             */
/*   Updated: 2024/04/09 13:00:31 by alvega-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

static int	word_count(const char *s, char c)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			while (s[i] && s[i] != c)
				i++;
			count++;
		}
		else
			i++;
	}
	return (count);
}

static char	*fill(const char *s, int start, int end)
{
	int		i;
	char	*dest;

	i = 0;
	dest = (char *)malloc((end - start + 1) * sizeof(char));
	if (!dest)
		return (0);
	while (start < end)
	{
		dest[i] = s[start];
		i++;
		start++;
	}
	dest[i] = 0;
	return (dest);
}

char	**ft_split_prev(char const *s, char c, char prev)
{
	unsigned int	i;
	unsigned int	j;
	int				index;
	char			**split;

	i = -1;
	j = 0;
	index = -1;
	split = (char **)malloc((word_count(s, c) + 1) * sizeof(char *));
	if (!s || !split)
		return (0);
	while (++i <= ft_strlen(s))
	{
		if (s[i] != c && index < 0)
			index = i;
		else if ((s[i] == c || i == ft_strlen(s)) && index >= 0
			&& s[i - 1] != prev)
		{
			split[j] = fill(s, index, i);
			index = -1;
			j++;
		}
	}
	split[j] = 0;
	return (split);
}
