/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albagar4 <albagar4@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 17:26:49 by albagar4          #+#    #+#             */
/*   Updated: 2024/05/13 15:19:10 by albagar4         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_exit(t_data *data, int infd, int outfd)
{
	int	exit_status;

	write(2, "ayuda\n", 7);
	if (data->cmds->args[1] != NULL
		&& ft_isalpha_loop(data->cmds->args[1]) == 0)
		exit_status = ft_atoi(data->cmds->args[1]) % 256;
	else if (data->cmds->args[1] != NULL
		&& ft_isalpha_loop(data->cmds->args[1]) != 0)
		exit_status = 255;
	else
		exit_status = data->exit_status;
	close(infd);
	close(outfd);
	ft_cleanup_env(data->env);
	ft_annihilation(data);
	printf("exit\n");
	exit(exit_status);
}
