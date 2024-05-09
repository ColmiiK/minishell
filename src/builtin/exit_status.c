/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albagar4 <albagar4@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 17:35:58 by albagar4          #+#    #+#             */
/*   Updated: 2024/05/09 17:53:24 by albagar4         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	exit_status(t_env **env)
{
	t_env	*exit_status;

	exit_status = malloc(sizeof(t_env));
	if (!exit_status)
		return ;
	exit_status->name = ft_strdup("?");
	exit_status->content = ft_strdup("0");
	exit_status->next = NULL;
	add_back(env, exit_status);
}

void	status_update(t_env **env, int exit_sts)
{
	t_env	*tmp;
	char	*str;

	tmp = *env;
	str = ft_itoa(exit_sts);
	while (tmp)
	{
		if (!ft_strcmp(tmp->name, "?"))
			tmp->content = ft_strdup_ex(str, tmp->content);
		tmp = tmp->next;
	}
	free(str);
}
