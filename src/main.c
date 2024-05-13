/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvega-g <alvega-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 16:32:38 by alvega-g          #+#    #+#             */
/*   Updated: 2024/05/13 17:28:40 by alvega-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	g_signal;

int	main(int ac, char **av, char **env)
{
	t_data	data;

	(void)ac;
	(void)av;
	ft_first_setup(&data, env);
	while (true)
	{
		if (ft_parsing_loop(&data))
			break ;
		ft_find_path(data);
		signal(SIGQUIT, ft_handle_sigquit);
		if (ft_check_fds(data))
			perror("minihell");
		else if (data.cmds)
			ft_execute(&data);
		signal(SIGQUIT, SIG_IGN);
		ft_annihilation(&data);
	}
	rl_clear_history();
	ft_cleanup_env(data.env);
	return (0);
}
