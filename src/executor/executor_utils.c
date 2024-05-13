/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvega-g <alvega-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 17:50:47 by alvega-g          #+#    #+#             */
/*   Updated: 2024/05/13 17:52:50 by alvega-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_error_child(t_data *data)
{
	int	i;

	i = data->fork_status;
	perror("minihell");
	if (data->n_of_cmds != 1)
		close(data->fd[0]);
	ft_cleanup_env(data->env);
	ft_annihilation(data);
	exit(i);
}
