/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvega-g <alvega-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 15:46:40 by albagar4          #+#    #+#             */
/*   Updated: 2024/05/06 15:48:55 by alvega-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int		ft_unset(t_env **env, char *str)
{
	t_env	*tmp;

	tmp = *env;
	while (*env)
	{
		if (!ft_strncmp((*env)->next->name, str, ft_strlen((*env)->next->name)))
		{
			free((*env)->next->name);
			if ((*env)->next->content)
				free((*env)->next->content);
			(*env)->next = (*env)->next->next;
			free((*env)->next);
			break ;
		}
		*env = (*env)->next;
	}
	*env = tmp;
	return (0);
}
