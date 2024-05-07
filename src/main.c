/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvega-g <alvega-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 16:32:38 by alvega-g          #+#    #+#             */
/*   Updated: 2024/05/07 17:54:30 by alvega-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*
	TESTS:
	exit sin argumentos
	

*/


int	g_signal;

void	ft_debug(t_data data)
{
	t_cmd	*current;

	current = data.cmds;
	while (current)
	{
		printf("\ncmd: %s\n", current->cmd);
		for (int i = 0; current->args[i]; i++)
			printf("arg[%d]: %s\n", i, current->args[i]);
		printf("in_fd: %d\n", current->redirect->in_fd);
		printf("out_fd: %d\n\n", current->redirect->out_fd);
		current = current->next;
	}
}

int	main(int ac, char **av, char **env)
{
	t_data	data;

	(void)ac;
	(void)av;
	
	g_signal = 0;
	signal(SIGINT, ft_handle_sigint);
	signal(SIGQUIT, ft_handle_sigquit);
	tcgetattr(STDIN_FILENO, &data.termios);
	data.env = ft_getenv(env);
	
	while (true)
	{
		if (ft_parsing_loop(&data))
			break ;
		ft_find_path(data);
		ft_debug(data);
		if (data.cmds)
			ft_execute(&data);
		ft_annihilation(&data);
		g_signal = 0;
		// break;
	}
	rl_clear_history();
	ft_cleanup_env(data.env);
	return (0);
}
