/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvega-g <alvega-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 16:15:26 by alvega-g          #+#    #+#             */
/*   Updated: 2024/01/18 17:56:11 by alvega-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (n == 0)
		return (0);
	while ((n - 1) && s1[i] && (s1[i] == s2[j]))
	{
		i++;
		j++;
		n--;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[j]);
}
