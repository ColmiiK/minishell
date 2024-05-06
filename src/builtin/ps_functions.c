/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_functions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvega-g <alvega-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 16:55:35 by albagar4          #+#    #+#             */
/*   Updated: 2024/05/06 15:19:50 by alvega-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	swap(t_env **env)
{
	t_env	*first_pos;
	t_env	*sec_pos;

	if (!(*env) || !(*env)->next)
		return ;
	first_pos = pop_first(env);
	sec_pos = pop_first(env);
	add_front(env, first_pos);
	add_front(env, sec_pos);
}

void	add_front(t_env **env, t_env *node)
{
	if (!node)
		return ;
	node->next = *env;
	*env = node;
}

void	add_back(t_env **env, t_env *new)
{
	t_env	*tmp;

	if (!(*env))
	{
		*env = new;
	}
	else
	{
		tmp = *env;
		while ((*env)->next)
			*env = (*env)->next;
		(*env)->next = new;
		*env = tmp;
	}
}

t_env	*pop_first(t_env **env)
{
	t_env	*excluded;

	if (!(*env))
		return (0);
	excluded = *env;
	*env = (*env)->next;
	excluded->next = NULL;
	return (excluded);
}
