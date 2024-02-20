/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvega-g <alvega-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 16:26:41 by alvega-g          #+#    #+#             */
/*   Updated: 2024/01/18 17:54:38 by alvega-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	*ft_bzero(void *str, size_t n)
{
	unsigned int	i;
	char			*temp;

	i = 0;
	temp = str;
	while (i != n)
	{
		temp[i] = 0;
		i++;
	}
	return (str);
}
