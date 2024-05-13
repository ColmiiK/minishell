/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvega-g <alvega-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 12:07:50 by albagar4          #+#    #+#             */
/*   Updated: 2024/05/13 11:38:11 by alvega-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*empty_cd(t_env **env)
{
	t_env	*path;

	path = *env;
	while (path)
	{
		if (!strcmp(path->name, "HOME"))
			return (path->content);
		path = path->next;
	}
	return (printf("cd: HOME not set\n"), NULL);
}

void	ft_create_pwd(t_env **env, char *str)
{
	char	*name;
	char	*joined;

	name = ft_strdup("OLDPWD=");
	joined = ft_strjoin_mod(name, str);
	ft_export(env, joined);
	free(joined);
}

int	update_location(t_env **node, char *new, char *old)
{
	t_env	*tmp;
	int		flag;

	tmp = *node;
	flag = 0;
	while (*node && strcmp(new, old))
	{
		if (!ft_strncmp((*node)->name, "PWD", 4))
		{
			if ((*node)->content)
				free((*node)->content);
			(*node)->content = ft_strdup(new);
		}
		if (!ft_strncmp((*node)->name, "OLDPWD", 7))
		{
			if ((*node)->content)
				free((*node)->content);
			(*node)->content = old;
			flag = 1;
		}
		*node = (*node)->next;
	}
	*node = tmp;
	if (flag == 0 && strcmp(new, old))
		ft_create_pwd(node, old);
	return (0);
}
