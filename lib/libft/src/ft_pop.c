/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pop.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvega-g <alvega-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 16:45:02 by alvega-g          #+#    #+#             */
/*   Updated: 2024/04/24 17:36:38 by alvega-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_pop(char *str, char c, bool del)
{
	int		i;
	int		j;
	int		len;
	char	*new_str;

	len = ft_strlen(str);
	new_str = (char *)malloc(sizeof(char) * (len + 1));
	if (!new_str)
		return (NULL);
	i = -1;
	j = -1;
	while (++i <= len)
	{
		if (str[i] != c || (i > 0 && str[i - 1] == '\\' && c != '\\'))
			new_str[++j] = str[i];
	}
	new_str[j] = '\0';
	if (del == true)
		free(str);
	return (new_str);
}
