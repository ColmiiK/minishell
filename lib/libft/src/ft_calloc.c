/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvega-g <alvega-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 11:23:23 by alvega-g          #+#    #+#             */
/*   Updated: 2024/01/18 17:54:40 by alvega-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	*ft_calloc(size_t n, size_t size)
{
	void	*memory;

	memory = (void *)malloc(n * size);
	if (!memory)
		return (0);
	ft_bzero(memory, n * size);
	return (memory);
}
