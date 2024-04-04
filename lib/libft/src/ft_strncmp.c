/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frangome <frangome@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 17:42:05 by frangome          #+#    #+#             */
/*   Updated: 2023/04/26 18:11:36 by frangome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	counter;

	counter = 0;
	while ((*(s1 + counter) != '\0' || *(s2 + counter) != '\0') && counter < n)
	{
		if (*(s1 + counter) != *(s2 + counter))
			return ((unsigned char)*(s1 + counter)
				- (unsigned char)*(s2 + counter));
		counter++;
	}
	return (0);
}
