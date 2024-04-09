/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvega-g <alvega-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 16:10:47 by alvega-g          #+#    #+#             */
/*   Updated: 2024/04/09 16:11:57 by alvega-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_env	*ft_parse_env(char **env)
{
	int		i;
	t_env	*head;
	t_env	*current;
	t_env	*new_node;

	head = NULL;
	i = -1;
	while (env[++i])
	{
		new_node = malloc(sizeof(t_env));
		if (!new_node)
			return (NULL);
		new_node->var = ft_strdup(env[i]);
		new_node->next = NULL;
		if (head == NULL)
			head = new_node;
		else
			current->next = new_node;
		current = new_node;
	}
	return (head);
}
