/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albagar4 <albagar4@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 15:46:40 by albagar4          #+#    #+#             */
/*   Updated: 2024/05/08 16:42:33 by albagar4         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_unset(t_env **env, char *str)
{
	t_env	*tmp;

	tmp = *env;
	while ((*env)->next)
	{
		if (!ft_strcmp((*env)->next->name, str))
		{
			free((*env)->next->name);
			if ((*env)->next->content)
				free((*env)->next->content);
			(*env)->next = (*env)->next->next;
			free((*env)->next);
			*env = tmp;
			return (0);
		}
		*env = (*env)->next;
	}
	printf("variable not found: check if you wrote it correctly\n");
	*env = tmp;
	return (0);
}
