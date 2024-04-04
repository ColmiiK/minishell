/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frangome <frangome@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 11:37:22 by fran              #+#    #+#             */
/*   Updated: 2023/04/26 18:00:39 by frangome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*result;
	int		flag;

	flag = 0;
	if (!s)
		return (0);
	if ((unsigned int)ft_strlen(s) < start)
	{
		len = 0;
		start = 0;
		flag = 1;
	}
	if ((unsigned int)ft_strlen(s + start) < len && !flag)
		len = (unsigned int)ft_strlen(s + start);
	result = malloc((len + 1) * sizeof(char));
	if (!result)
		return (0);
	ft_strlcpy(result, (char *)(s + start), len + 1);
	return (result);
}
