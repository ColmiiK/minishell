/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preset_env_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvega-g <alvega-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 19:07:10 by albagar4          #+#    #+#             */
/*   Updated: 2024/05/10 11:59:31 by alvega-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	free_arr(char **env_cpy, int size)
{
	int	i;

	i = 0;
	if (env_cpy == NULL)
		return ;
	while (i < size)
	{
		free(env_cpy[i]);
		i++;
	}
	free(env_cpy);
}

char	*get_name_env(char *str)
{
	char	*name;
	int		i;

	i = 0;
	while (str[i] != 61 && str[i] != '\0')
		i++;
	name = ft_substr(str, 0, i);
	return (name);
}

char	*get_content_env(char *str)
{
	char	*content;
	int		i;

	i = 0;
	while (str[i] != 61 && str[i] != '\0')
		i++;
	if (str[i] == 61)
		content = ft_substr(str, (i + 1), ft_strlen(str) - i);
	else
		content = NULL;
	return (content);
}

t_env	*create_node(char *str)
{
	t_env		*node;
	static int	i = 0;

	node = (t_env *)malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->name = get_name_env(str);
	node->content = get_content_env(str);
	node->next = NULL;
	i++;
	return (node);
}

t_env	*next_node(t_env **node, t_env *new)
{
	t_env	*tmp;

	if (!(*node))
		*node = new;
	else
	{
		tmp = *node;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	return (new);
}
