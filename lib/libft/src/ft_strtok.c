/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvega-g <alvega-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 12:29:47 by alvega-g          #+#    #+#             */
/*   Updated: 2024/01/10 11:28:48 by alvega-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

static int	ft_in_set(char c, char *set)
{
	while (*set)
	{
		if (c == *set)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtok(char *str, char *del)
{
	static char	*next = NULL;
	char		*token;

	if (!str && !next)
		return (NULL);
	if (!str)
		str = next;
	while (*str && ft_in_set(*str, del))
		str++;
	if (!*str)
	{
		next = NULL;
		return (NULL);
	}
	token = str;
	while (*str && !ft_in_set(*str, del))
		str++;
	if (!*str)
		next = NULL;
	else
	{
		*str = '\0';
		next = str + 1;
	}
	return (token);
}
