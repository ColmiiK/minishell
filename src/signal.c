/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albagar4 <albagar4@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 13:59:36 by alvega-g          #+#    #+#             */
/*   Updated: 2024/05/06 17:39:21 by albagar4         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_handle_sigint(int signum)
{
	(void)signum;
	g_signal = SIGINT;
	// rl_on_new_line();
	// rl_redisplay()
	// printf("   \n");
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	ft_handle_sigquit(int signum)
{
	(void)signum;
	g_signal = SIGQUIT;
}
