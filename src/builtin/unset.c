/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albagar4 <albagar4@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 15:46:40 by albagar4          #+#    #+#             */
/*   Updated: 2024/05/08 18:15:11 by albagar4         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_delete_first(t_env **env)
{
	t_env	*tmp;

	tmp = *env;
	*env = (*env)->next;
	free(tmp->name);
	if (tmp->content != NULL)
		free(tmp->content);
	if (tmp->var != NULL)
		free(tmp->var);
	tmp->next = NULL;
	free(tmp);
	printf("*env == %s\n", (*env)->name);
	return ;
}

int	ft_unset(t_env **env, char *str)
{
	t_env	*tmp;

	tmp = *env;
	while ((*env)->next)
	{
		// if (!ft_strcmp((*env)->name, str))
		// {
		// 	ft_delete_first(env);
		// 	printf("*env == %s\n", (*env)->name);
		// 	return (0);
		// }
		if (!ft_strcmp((*env)->next->name, str))
		{
			free((*env)->next->name);
			if ((*env)->next->content != NULL)
				free((*env)->next->content);
			if ((*env)->next->var != NULL)
				free((*env)->next->var);
			if ((*env)->next != NULL)
				free((*env)->next);
			(*env)->next = (*env)->next->next;
			*env = tmp;
			return (0);
		}
		*env = (*env)->next;
	}
	printf("variable not found: check if you wrote it correctly\n");
	*env = tmp;
	return (0);
}
