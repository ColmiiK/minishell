/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_nodes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvega-g <alvega-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 12:12:10 by alvega-g          #+#    #+#             */
/*   Updated: 2024/05/11 18:27:14 by alvega-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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

static void ft_helper_fill(t_cmd *current, char *str, char *redirect, t_env *env)
{
	int j;

	current->args = ft_split_prev(str, ' ', '\\');
	if (!*current->args)
	{
		ft_clean_double_ptr(current->args);
		current->args = ft_split(str, ' ');
		if (!*current->args)
		{
			ft_clean_double_ptr(current->args);
			current->args = ft_split(" ", '\0');
		}
	}
	if (!*str)
		current->cmd = ft_strdup("");
	else
		current->cmd = ft_strdup(ft_strtok(str, " "));
	current->cmd = ft_argument_fix(current->cmd, env);
	current->redirect->in_fd = ft_determine_in_fd(redirect);
	current->redirect->out_fd = ft_determine_out_fd(redirect);
	j = -1;
	while (current->args[++j])
		current->args[j] = ft_argument_fix(current->args[j], env);
}

static t_cmd	*ft_fill_nodes(t_cmd *head, char **cmds,
	char **redirect, t_env *env)
{
	int		i;
	t_cmd	*current;

	i = -1;
	current = head;
	while (current)
	{
		i++;
		ft_helper_fill(current, cmds[i], redirect[i], env);
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
