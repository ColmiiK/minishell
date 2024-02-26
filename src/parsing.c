/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvega-g <alvega-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 12:50:00 by alvega-g          #+#    #+#             */
/*   Updated: 2024/02/26 16:26:16 by alvega-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_parse_envp(t_data *data, char **envp)
{
	int	i;
	int	j;

	i = -1;
	while (envp[++i])
	{
		if (ft_strnstr(envp[i], "PATH=", 5))
		{
			data->path = ft_split(envp[i] + 5, ':');
			i = -1;
			while (data->path[++i])
			{
				j = ft_strlen(data->path[i]);
				data->path[i] = ft_realloc(data->path[i], j + 2);
				if (!data->path[i])
					perror("Error: unable to realloc (data->path[i]).");
				data->path[i][j] = '/';
				data->path[i][j + 1] = 0;
			}
			return ;
		}
	}
}
