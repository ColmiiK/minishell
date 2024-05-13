/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albagar4 <albagar4@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 16:32:38 by alvega-g          #+#    #+#             */
/*   Updated: 2024/05/13 15:39:38 by albagar4         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/* TODO

	pwd seg fault?
	export a then again export a seg fault?

	system("lsof -c minishell");
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
	ft_first_setup(&data, env);
	while (true)
	{
		if (ft_parsing_loop(&data))
			break ;
		ft_find_path(data);
		ft_debug(data);
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
