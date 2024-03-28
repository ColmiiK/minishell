 /* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvega-g <alvega-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 16:32:38 by alvega-g          #+#    #+#             */
/*   Updated: 2024/03/07 13:40:17 by alvega-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void ft_debug(t_data data)
{
	t_cmd *current;

	current = data.cmds;
	while (current)
	{
		printf("\ncmd: %s\n", current->cmd);
		printf("args: %s\n", current->args);
		printf("in_fd: %d\n", current->redirect->in_fd);
		printf("out_fd: %d\n\n", current->redirect->out_fd);
		current = current->next;
	}
}

int main(int ac, char **av, char **env)
{
	t_data data;
	
	(void)ac;
	(void)av;
	data.env = ft_parse_env(env);
	while (true)
	{
		if (ft_parsing_loop(&data))
			return (1);
		
		ft_debug(data);
		
		ft_annihilation(&data);
		break;
	}
	ft_cleanup_env(data.env);
	return (0);
}
