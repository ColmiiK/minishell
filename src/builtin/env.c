/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvega-g <alvega-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 17:51:20 by albagar4          #+#    #+#             */
/*   Updated: 2024/05/06 15:19:50 by alvega-g         ###   ########.fr       */
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
		if ((*link_list)->content)
			printf("%s=%s\n", (*link_list)->name, (*link_list)->content);
		*link_list = (*link_list)->next;
	}
	*link_list = tmp;
	return (0);
}
