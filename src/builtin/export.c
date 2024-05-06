/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvega-g <alvega-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 12:43:24 by albagar4          #+#    #+#             */
/*   Updated: 2024/05/06 15:23:57 by alvega-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	free_node(t_env **node)
{
	free((*node)->name);
	if ((*node)->content)
		free((*node)->content);
	free(*node);
}

t_env	*create_single_cpy(char *name, char *content)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->name = ft_strdup(name);
	if (content != NULL)
		node->content = ft_strdup(content);
	node->next = NULL;
	return (node);
}

t_env	*ft_cpy_list(t_env **env)
{
	t_env	*tmp;
	t_env	*cpy_head;
	t_env	*cpy_tail;

	tmp = *env;
	cpy_head = create_single_cpy((*env)->name, (*env)->content);
	*env = (*env)->next;
	while (*env)
	{
		cpy_tail = create_single_cpy((*env)->name, (*env)->content);
		add_back(&cpy_head, cpy_tail);
		*env = (*env)->next;
	}
	*env = tmp;
	return (cpy_head);
}

void	ft_order_alpha(t_env **env, int size)
{
	t_env	*node;
	t_env	*tmp;
	int		i;

	tmp = ft_cpy_list(env);
	while (tmp->next)
	{
		i = 0;
		while (i < size)
		{
			if (ft_strcmp(tmp->name, tmp->next->name) < 0)
				swap(&tmp);
			else
			{
				node = pop_first(&tmp);
				add_back(&tmp, node);
				i++;
			}
		}
		size--;
		smart_print(tmp);
		node = pop_first(&tmp);
		free_node(&node);
	}
	smart_print(tmp);
}

int	ft_export(t_env **env, char *argv)
{
	char	*name;
	char	*content;
	int		size;

	if (argv == NULL)
	{
		size = list_length(env);
		ft_order_alpha(env, size);
	}
	else
	{
		if (check_correct_input(argv) == 0)
		{
			name = get_name_env(argv);
			content = get_content_env(argv);
			if (check_existent_var(env, name, content) != 1)
				create_new_var(env, name, content);
		}
		else
			return (1);
	}
	return (0);
}
