/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvega-g <alvega-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 12:43:56 by albagar4          #+#    #+#             */
/*   Updated: 2024/05/06 15:19:50 by alvega-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	smart_print(t_env *node)
{
	if (node->content)
		printf("%s=%s\n", node->name, node->content);
	else
		printf("%s\n", node->name);
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
		if (!ft_strncmp(tmp->name, name, ft_strlen(tmp->name)) && tmp->content)
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
			|| (str[i] > 90 && str[i] < 97) || str[i] > 122)
		{
			printf("%s %c %i\n", str, str[i], i);
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
	if (content)
		node->content = ft_strdup(content);
	else
		node->content = NULL;
	node->next = NULL;
	add_back(env, node);
	return (0);
}
