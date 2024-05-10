/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albagar4 <albagar4@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 12:07:50 by albagar4          #+#    #+#             */
/*   Updated: 2024/05/10 15:45:14 by albagar4         ###   ########.fr       */
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
			(*node)->content = new;
		if (!ft_strncmp((*node)->name, "OLDPWD", 7))
		{
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
