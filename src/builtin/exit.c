/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvega-g <alvega-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 17:26:49 by albagar4          #+#    #+#             */
/*   Updated: 2024/05/13 12:13:13 by alvega-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_exit(t_data *data, int infd, int outfd)
{
	int	exit_status;
	
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
