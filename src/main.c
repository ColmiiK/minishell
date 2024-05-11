/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvega-g <alvega-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 16:32:38 by alvega-g          #+#    #+#             */
/*   Updated: 2024/05/11 21:20:28 by alvega-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/* TODO

	command not found error message
	pwd seg fault?
	export a then again export a seg fault?
	fd leak when multiple commands

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

int ft_check_fds(t_data data)
{
	if (data.cmds)
	{
		if (data.cmds->redirect->in_fd == -1)
			return (1);
		if (data.cmds->redirect->out_fd == -1)
			return (1);			
		data.cmds = data.cmds->next;
	}
	return (0);
}

int	main(int ac, char **av, char **env)
{
	t_data	data;

	(void)ac;
	(void)av;
	signal(SIGINT, ft_handle_sigint);
	signal(SIGQUIT, SIG_IGN);
	tcgetattr(STDIN_FILENO, &data.termios);
	data.env = ft_getenv(env);
	exit_status(&data.env);
	while (true)
	{
		g_signal = 1;
		if (ft_parsing_loop(&data))
			break ;
		ft_find_path(data);
		ft_debug(data);
		g_signal = 3;
		signal(SIGQUIT, ft_handle_sigquit);
		if (ft_check_fds(data))
			ft_putendl_fd("minishell: No such file or directory", 2);
		else if (data.cmds)
			ft_execute(&data);
		signal(SIGQUIT, SIG_IGN);
		ft_annihilation(&data);
	}
	rl_clear_history();
	ft_cleanup_env(data.env);
	return (0);
}
