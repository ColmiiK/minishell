/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strinsert.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvega-g <alvega-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 13:30:42 by alvega-g          #+#    #+#             */
/*   Updated: 2024/04/08 13:36:35 by alvega-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_strinsert(char *str, int pos, char *insert, int del)
{
	char	*new;
	int		i;
	int		j;

	new = malloc(ft_strlen(str) + ft_strlen(insert) + 1);
	if (!new)
		return (NULL);
	i = -1;
	j = -1;
	while (str[++i] && i < pos)
		new[++j] = str[i];
	i = -1;
	while (insert[++i])
		new[++j] = insert[i];
	i = pos - 1;
	while (str[++i])
		new[++j] = str[i];
	new[++j] = '\0';
	if (del == 1 || del == 3)
		free(str);
	if (del == 2 || del == 3)
		free(insert);
	return (new);
}
