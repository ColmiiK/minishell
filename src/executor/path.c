/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvega-g <alvega-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 18:10:59 by alvega-g          #+#    #+#             */
/*   Updated: 2024/05/13 16:24:47 by alvega-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	**ft_get_variables(t_env *env)
{
	int		i;
	int		len;
	char	**variables;

	i = -1;
	len = list_length(&env);
	variables = (char **)malloc(sizeof(char *) * (len + 1));
	if (!variables)
		return (NULL);
	while (++i < len)
	{
		variables[i] = ft_strdup(env->name);
		if (env->content)
		{
			variables[i] = ft_strjoin_ex(variables[i], "=", 1);
			variables[i] = ft_strjoin_ex(variables[i], env->content, 1);
		}
		env = env->next;
	}
	variables[i] = NULL;
	return (variables);
}

static char	**ft_find_path_env(t_env *env)
{
	while (env)
	{
		if (env->name)
		{
			if (ft_strnstr(env->name, "PATH", 4))
				return (ft_split(env->content + 5, ':'));
		}
		env = env->next;
	}
	return (NULL);
}

static char	*ft_find_access(char *path, char *cmd)
{
	char	*temp;

	temp = ft_strjoin(path, "/");
	temp = ft_strjoin_ex(temp, cmd, 1);
	if (access(temp, F_OK) != -1 && access(temp, X_OK) != -1)
		return (temp);
	free(temp);
	return (NULL);
}

static int	ft_find_path_helper(char **path, t_cmd *cmds)
{
	char	*full_path;
	int		i;

	i = -1;
	while (path[++i])
	{
		full_path = ft_find_access(path[i], cmds->args[0]);
		if (full_path)
		{
			free(cmds->cmd);
			cmds->cmd = full_path;
			return (1);
		}
	}
	return (0);
}

int	ft_find_path(t_data data)
{
	char	**path;

	path = ft_find_path_env(data.env);
	if (!path)
		return (1);
	while (data.cmds)
	{
		if (built_in_checker(data.cmds->cmd))
			;
		else
			ft_find_path_helper(path, data.cmds);
		if (data.cmds->next)
			data.cmds = data.cmds->next;
		else
			break ;
	}
	ft_clean_double_ptr(path);
	return (0);
}
