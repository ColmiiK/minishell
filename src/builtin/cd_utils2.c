/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albagar4 <albagar4@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 15:40:38 by albagar4          #+#    #+#             */
/*   Updated: 2024/05/10 15:42:37 by albagar4         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	oldpath_cd(t_env **node)
{
	char	*path;
	t_env	*tmp;

	tmp = *node;
	path = NULL;
	while (tmp)
	{
		if (!ft_strcmp(tmp->name, "OLDPWD") && tmp->content != NULL)
		{
			path = ft_strdup(tmp->content);
			ft_abs_cd(path);
			return (0);
		}
		tmp = tmp->next;
	}
	printf("cd: OLDPWD not set\n");
	return (0);
}

int	homepath_cd(t_env **node, char *location)
{
	char	*path;

	path = empty_cd(node);
	ft_abs_cd(path);
	update_location(node, init_location(), location);
	return (0);
}
