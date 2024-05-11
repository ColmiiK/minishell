/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvega-g <alvega-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 13:59:36 by alvega-g          #+#    #+#             */
/*   Updated: 2024/05/11 17:19:51 by alvega-g         ###   ########.fr       */
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
