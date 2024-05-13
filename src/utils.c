/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvega-g <alvega-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 12:28:17 by alvega-g          #+#    #+#             */
/*   Updated: 2024/05/13 12:12:40 by alvega-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_handle_sigint(int signum)
{
	(void)signum;
	if (g_signal == 1)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		write(1, "\033[K\n", 5);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (g_signal == 2)
	{
		g_signal = 4;
		write(1, "\033[K\n", 5);
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (g_signal == 3)
	{
		write(1, "\033[K\n", 5);
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	ft_handle_sigquit(int signum)
{
	(void)signum;
	if (g_signal == 1)
		;
	else if (g_signal == 2)
		;
	else if (g_signal == 3)
	{
		write(1, "Quit: 3\n", sizeof(char) * 9);
		rl_replace_line("", 0);
		rl_redisplay();
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

void ft_first_setup(t_data *data, char **env)
{
	signal(SIGINT, ft_handle_sigint);
	signal(SIGQUIT, SIG_IGN);
	tcgetattr(STDIN_FILENO, &data->termios);
	data->env = ft_getenv(env);
	exit_status(&data->env);
	data->exit_status = 0;
}
