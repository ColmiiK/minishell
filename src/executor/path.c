/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvega-g <alvega-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 18:10:59 by alvega-g          #+#    #+#             */
/*   Updated: 2024/05/07 13:44:43 by alvega-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char **ft_find_path_env(t_env *env)
{
	while (env)
	{
		if (ft_strnstr(env->name, "PATH", 4))
			return (ft_split(env->var + 5, ':'));
		env = env->next;
	}
	return (NULL);
}

char *ft_find_access(char *path, char *cmd)
{
	char *temp;

	temp = ft_strjoin(path, "/");
	temp = ft_strjoin_ex(temp, cmd, 1);
	if (access(temp, F_OK) != -1 && access(temp, X_OK) != -1)
		return (temp);
	free(temp);
	return (NULL);
}

int ft_find_path(t_data data)
{
	char **path;
	char *full_path;
	int i;

	path = ft_find_path_env(data.env);
	if (!path)
		return (1);
	while (data.cmds)
	{
		if (built_in_checker(data.cmds->cmd))
			;
		else
		{
			i = -1;
			while (path[++i])
			{
				full_path = ft_find_access(path[i], data.cmds->cmd);
				if (full_path)
				{
					free(data.cmds->cmd);
					data.cmds->cmd = full_path;
					break;
				}
			}
		}
		if (data.cmds->next)
			data.cmds = data.cmds->next;
		else
			break;
	}
	ft_clean_double_ptr(path);
	return (0);
}
