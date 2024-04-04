/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frangome <frangome@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 17:07:39 by frangome          #+#    #+#             */
/*   Updated: 2023/04/26 18:08:07 by frangome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *str, int c, size_t n)
{
	size_t	count;
	char	*str2;

	str2 = str;
	count = 0;
	while (count < n)
	{
		*(str2 + count) = (unsigned char)c;
		count++;
	}
	return (str);
}
