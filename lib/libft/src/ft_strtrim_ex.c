/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim_ex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvega-g <alvega-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 16:29:04 by alvega-g          #+#    #+#             */
/*   Updated: 2024/04/08 16:30:26 by alvega-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_strtrim_ex(char *s1, char const *set, bool del)
{
	int		i;
	int		start;
	int		end;
	char	*trim;

	i = 0;
	start = 0;
	end = ft_strlen(s1);
	while (s1[start] && ft_strchr(set, s1[start]) != 0)
		start++;
	while (end > start && ft_strchr(set, s1[end - 1]) != 0)
		end--;
	trim = (char *)malloc(sizeof(char) * (end - start + 1));
	if (!trim)
		return (0);
	while (start < end)
	{
		trim[i] = s1[start];
		i++;
		start++;
	}
	trim[i] = 0;
	if (del == true)
		free(s1);
	return (trim);
}
