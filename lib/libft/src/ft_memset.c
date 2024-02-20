/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvega-g <alvega-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 15:43:16 by alvega-g          #+#    #+#             */
/*   Updated: 2024/01/18 17:55:32 by alvega-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	*ft_memset(void *str, int c, size_t len)
{
	unsigned int	i;
	char			*temp;

	i = 0;
	temp = str;
	while (i != len)
	{
		temp[i] = c;
		i++;
	}
	return (str);
}
