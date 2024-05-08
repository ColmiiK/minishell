/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albagar4 <albagar4@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 17:51:20 by albagar4          #+#    #+#             */
/*   Updated: 2024/05/08 16:14:54 by albagar4         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	free_list(t_env **link_list)
{
	t_env	*tmp;

	while (*link_list != NULL)
	{
		tmp = *link_list;
		*link_list = (*link_list)->next;
		free(tmp->name);
		if (tmp->content)
			free(tmp->content);
		free(tmp);
	}
}

int	ft_env(t_env **link_list)
{
	t_env	*tmp;

	tmp = *link_list;
	while (*link_list)
	{
		if ((*link_list)->content != NULL)
			printf("%s=%s\n", (*link_list)->name, (*link_list)->content);
		*link_list = (*link_list)->next;
	}
	*link_list = tmp;
	return (0);
}
