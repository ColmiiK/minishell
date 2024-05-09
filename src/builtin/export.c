/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvega-g <alvega-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 12:43:24 by albagar4          #+#    #+#             */
/*   Updated: 2024/05/09 17:13:31 by alvega-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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

void	ft_swap_env(t_env **first, t_env **second)
{
	(*first)->name = (*second)->name;
	(*first)->content = (*second)->content;
}

void	ft_order_alpha(t_env **env)
{
	t_env	*tmp;
	t_env	*swap;

	tmp = *env;
	swap = malloc(sizeof(t_env));
	if (!swap)
		return ;
	while (tmp->next)
	{
		if (tmp->next && ft_strcmp(tmp->name, tmp->next->name) > 0)
		{
			ft_swap_env(&swap, &tmp);
			ft_swap_env(&tmp, &(tmp->next));
			ft_swap_env(&(tmp->next), &swap);
			tmp = *env;
		}
		else
			tmp = tmp->next;
	}
	tmp = *env;
	smart_print(tmp);
	free(swap);
}

int	ft_export(t_env **env, char *argv)
{
	char	*temp;
	char	*name;
	char	*content;
	t_env	*cpy;

	if (argv == NULL)
	{
		cpy = ft_cpy_list(env);
		ft_order_alpha(&cpy);
		free_list(&cpy);
	}
	else
	{
		temp = get_name_env(argv);
		if (check_correct_input(temp) == 0)
		{
			free(temp);
			name = get_name_env(argv);
			content = get_content_env(argv);
			if (check_existent_var(env, name, content) != 1)
				create_new_var(env, name, content);
			free(name);
			free(content);
		}
		else
			return(free(temp), 1);
	}
	return (0);
}
