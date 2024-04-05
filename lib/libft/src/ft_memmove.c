/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvega-g <alvega-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 17:18:04 by alvega-g          #+#    #+#             */
/*   Updated: 2024/01/18 17:55:29 by alvega-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned int	i;
	char			*t_dst;
	char			*t_src;

	i = 0;
	t_dst = (char *)dst;
	t_src = (char *)src;
	if (!src && !dst)
		return (dst);
	if (t_src < t_dst)
	{
		while (len-- > 0)
			t_dst[len] = t_src[len];
	}
	else if (t_src > t_dst)
	{
		while (i < len)
		{
			t_dst[i] = t_src[i];
			i++;
		}
	}
	return (dst);
}
