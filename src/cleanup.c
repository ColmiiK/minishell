/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvega-g <alvega-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 13:36:48 by alvega-g          #+#    #+#             */
/*   Updated: 2024/05/09 14:20:57 by alvega-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_perror(char *str)
{
	perror(str);
	return (1);
}

void	ft_clean_double_ptr(char **ptr)
{
	int	i;

	i = -1;
	while (ptr[++i])
		free(ptr[i]);
	free(ptr);
}

/*
	t_list	*node;
	t_list	*next_node;

	if (!lst || !del)
		return ;
	node = *lst;
	while (node)
	{
		del(node->content);
		next_node = node->next;
		free(node);
		node = next_node;
	}
	*lst = 0;
*/

void	ft_annihilation(t_data *data)
{
	t_cmd *node;
	t_cmd *next_node;

	node = data->cmds;
	while (node)
	{
		free(node->cmd);
		ft_clean_double_ptr(node->args);
		if (node->redirect)
			free(node->redirect);
		next_node = node->next;
		free(node);
		node = next_node;
		
	}
	unlink(".here_doc");
}

void	ft_cleanup_env(t_env *env)
{
	t_env	*temp;

	while (env)
	{
		temp = env;
		env = env->next;
		free(temp->name);
		if (temp->content)
			free(temp->content);
		free(temp);
	}
}
