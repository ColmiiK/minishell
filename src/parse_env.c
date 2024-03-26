/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvega-g <alvega-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 11:09:30 by alvega-g          #+#    #+#             */
/*   Updated: 2024/03/26 11:09:40 by alvega-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char **ft_parse_env(char **env)
{
	int i;
	char **array;

	i = -1;
	while (env[++i])
		;
	array = (char **)ft_calloc(i + 1, sizeof(char *));
	i = -1;
	while (env[++i])
		array[i] = ft_strdup(env[i]);
	return (array);
}
