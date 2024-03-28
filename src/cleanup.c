/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvega-g <alvega-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 13:36:48 by alvega-g          #+#    #+#             */
/*   Updated: 2024/03/28 12:06:06 by alvega-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void ft_clean_double_ptr(char **ptr)
{
	int i;

	i = -1;
	while (ptr[++i])
		free(ptr[i]);
	free(ptr);
}

void ft_annihilation(t_data *data)
{
	int i;
	t_cmd *prev;

	i = -1;
	while (++i < data->n_of_cmds)
	{
		free(data->cmds->cmd);
		free(data->cmds->args);
		free(data->cmds->redirect);
		prev = data->cmds;
		if (data->cmds->next)
			data->cmds = data->cmds->next;
		free(prev);
	}
}

void ft_cleanup_env(t_env *env)
{
	t_env *temp;

	while (env)
	{
		temp = env;
		env = env->next;
		free(temp->var);
		free(temp);
	}
}
