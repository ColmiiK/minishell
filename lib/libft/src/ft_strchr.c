/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frangome <frangome@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 17:19:38 by frangome          #+#    #+#             */
/*   Updated: 2023/04/25 20:33:30 by frangome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	char	*res;

	res = (char *)str;
	while (*res != (char)c)
	{
		if (*res == '\0')
			return (NULL);
		res++;
	}
	return (res);
}
