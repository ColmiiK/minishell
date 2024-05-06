/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preset_env_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvega-g <alvega-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 19:07:10 by albagar4          #+#    #+#             */
/*   Updated: 2024/05/06 15:31:55 by alvega-g         ###   ########.fr       */
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
	while (str[i] != 61 && str)
		i++;
	name = (char *)malloc((sizeof(char *) * i) + 1);
	if (!name)
		return (free(str), NULL);
	i = 0;
	while (str[i] != 61 && str)
	{
		name[i] = str[i];
		i++;
	}
	name[i] = '\0';
	return (name);
}

char	*get_content_env(char *str)
{
	char	*content;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (str[i] != 61)
	{
		if (str[i++] == '\0' && str[i] != 61)
			return (NULL);
		i++;
	}
	content = (char *)malloc(sizeof(char *) * (ft_strlen(str) - i) + 1);
	if (!content)
		return (free(str), NULL);
	i++;
	while (str[i] != '\0')
	{
		content[j] = str[i];
		j++;
		i++;
	}
	content[i] = '\0';
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
	node->var = ft_strdup(str);
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
