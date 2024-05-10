/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albagar4 <albagar4@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/05/10 14:42:28 by albagar4         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	smart_print(t_env *node)
{
	while (node)
	{
		if (node->content && ft_strcmp(node->name, "?"))
			printf("%s=%s\n", node->name, node->content);
		else if (node->content == NULL && ft_strcmp(node->name, "?"))
			printf("%s\n", node->name);
		node = node->next;
	}
}

int	list_length(t_env **env)
{
	int		count;
	t_env	*tmp;

	tmp = *env;
	count = 0;
	while (tmp)
	{
		tmp = tmp->next;
		count++;
	}
	return (count);
}

int	check_existent_var(t_env **env, char *name, char *content)
{
	t_env	*tmp;

	tmp = *env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->name, name))
		{
			tmp->content = ft_strdup(content);
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

int	check_correct_input(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[0] >= '0' && str[0] <= '9')
		{
			printf("incorrect var name: it can't be started by a number\n");
			return (-1);
		}
		else if ((str[i] > 0 && str[i] < 48) || (str[i] > 57 && str[i] < 65)
			|| (str[i] > 90 && str[i] < 95) || (str[i] == 96) || (str[i] > 122))
		{
			printf("incorrect var nam: must only use alpha-numeric chars\n");
			return (-1);
		}
		i++;
	}
	return (0);
}

int	create_new_var(t_env **env, char *name, char *content)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node)
		return (-1);
	node->name = ft_strdup(name);
	if (content != NULL)
		node->content = ft_strdup(content);
	else
		node->content = NULL;
	node->next = NULL;
	add_back(env, node);
	return (0);
}
