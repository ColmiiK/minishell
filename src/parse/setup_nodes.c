/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_nodes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvega-g <alvega-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 12:12:10 by alvega-g          #+#    #+#             */
/*   Updated: 2024/05/06 15:27:23 by alvega-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	ft_determine_in_fd(char *redirect)
{
	int		fd;
	int		i;
	char	*str;

	redirect = ft_strchr(redirect, ':');
	redirect++;
	i = -1;
	while (redirect[++i] != ' ')
		;
	str = ft_substr(redirect, 0, i);
	if (ft_isdigit(*redirect))
		fd = ft_atoi(redirect);
	else
		fd = open(str, O_RDONLY);
	free(str);
	return (fd);
}

static int	ft_determine_out_fd(char *redirect)
{
	int		fd;

	redirect = ft_strrchr(redirect, ':');
	redirect++;
	if (ft_isdigit(*redirect))
		fd = ft_atoi(redirect);
	else if (ft_strnstr(redirect, "(A)", ft_strlen(redirect)))
		fd = open(redirect, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = open(redirect, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	return (fd);
}

static char	*ft_argument_fix(char *str, t_env *env)
{
	while (ft_strnstr(str, "$", ft_strlen(str))
		&& !ft_strnstr(str, "\\$", ft_strlen(str)))
		str = ft_expand_variables(str, env);
	str = ft_pop(str, '\"', true);
	str = ft_pop(str, '\'', true);
	str = ft_pop(str, '\\', true);
	if (ft_strnstr(str, "<\\<", 3))
		str = ft_strdup_ex("<<", str);
	if (ft_strnstr(str, ">\\>", 3))
		str = ft_strdup_ex(">>", str);
	return (str);
}

static t_cmd	*ft_fill_nodes(t_cmd *head, char **cmds,
	char **redirect, t_env *env)
{
	int		i;
	int		j;
	t_cmd	*current;

	i = -1;
	current = head;
	while (current)
	{
		current->args = ft_split_prev(cmds[++i], ' ', '\\');
		current->cmd = ft_strdup(ft_strtok(cmds[i], " "));
		current->cmd = ft_argument_fix(current->cmd, env);
		current->redirect->in_fd = ft_determine_in_fd(redirect[i]);
		current->redirect->out_fd = ft_determine_out_fd(redirect[i]);
		j = -1;
		while (current->args[++j])
			current->args[j] = ft_argument_fix(current->args[j], env);
		current = current->next;
	}
	return (head);
}

t_cmd	*ft_setup_nodes(char **cmds, char **redirect, t_env *env)
{
	int		i;
	t_cmd	*current;
	t_cmd	*new_node;
	t_cmd	*head;

	head = NULL;
	i = -1;
	while (cmds[++i])
	{
		new_node = malloc(sizeof(t_cmd));
		if (!new_node)
			return (NULL);
		new_node->redirect = malloc(sizeof(t_redirect));
		if (!new_node->redirect)
			return (NULL);
		new_node->next = NULL;
		if (head == NULL)
			head = new_node;
		else
			current->next = new_node;
		current = new_node;
	}
	head = ft_fill_nodes(head, cmds, redirect, env);
	return (head);
}
