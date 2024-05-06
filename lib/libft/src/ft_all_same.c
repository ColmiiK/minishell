/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_all_same.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvega-g <alvega-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 10:53:06 by alvega-g          #+#    #+#             */
/*   Updated: 2024/05/02 10:57:00 by alvega-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

bool	ft_all_same(char *str, char c)
{
	while (*str && *str == c)
		str++;
	if (!*str)
		return (true);
	return (false);
}
