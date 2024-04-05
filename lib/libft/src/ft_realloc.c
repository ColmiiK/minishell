/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvega-g <alvega-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 11:22:24 by alvega-g          #+#    #+#             */
/*   Updated: 2023/12/14 11:42:12 by alvega-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	*ft_realloc(void *ptr, size_t size)
{
	void	*new_ptr;

	new_ptr = NULL;
	if (size == 0)
		return (free(ptr), NULL);
	if (ptr == NULL)
		new_ptr = malloc(size);
	else
	{
		new_ptr = malloc(size);
		if (new_ptr)
		{
			ft_memcpy(new_ptr, ptr, size);
			free(ptr);
		}
	}
	return (new_ptr);
}
