/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvega-g <alvega-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 17:10:25 by alvega-g          #+#    #+#             */
/*   Updated: 2024/05/13 17:40:47 by alvega-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	ft_fd_juggling(int in_fd, int out_fd)
{
	if (in_fd != 0)
	{
		dup2(in_fd, 0);
		if (close(in_fd) == -1)
			return (1);
	}
	if (out_fd != 1)
	{
		dup2(out_fd, 1);
		if (close(out_fd) == -1)
			return (1);
	}
	return (0);
}

static int	ft_builtin_execute(t_cmd *cmd, t_data *data, int in_fd, int out_fd)
{
	int	saved_in_fd;
	int	saved_out_fd;

	saved_in_fd = dup(0);
	saved_out_fd = dup(1);
	if (ft_fd_juggling(in_fd, out_fd))
		return (1);
	if (built_in_checker(cmd->cmd))
		built_in_selector(data, cmd->args, saved_in_fd, saved_out_fd);
	dup2(saved_in_fd, 0);
	dup2(saved_out_fd, 1);
	close(saved_in_fd);
	close(saved_out_fd);
	return (0);
}

static int	ft_fork(t_cmd *cmd, t_data *data, int in_fd, int out_fd)
{
	pid_t	pid;
	char	**variables;

	pid = fork();
	if (pid == -1)
		return (1);
	if (pid == 0)
	{
		data->fork_status = 127;
		if (ft_fd_juggling(in_fd, out_fd))
			return (1);
		variables = ft_get_variables(data->env);
		if (access(cmd->cmd, F_OK) == 0 && access(cmd->cmd, X_OK) == -1)
			data->fork_status = 126;
		else
			execve(cmd->cmd, cmd->args, variables);
		perror("minihell");
		if (data->n_of_cmds != 1)
			close(data->fd[0]);
		ft_clean_double_ptr(variables);
		ft_cleanup_env(data->env);
		ft_annihilation(data);
		exit(data->fork_status);
	}
	waitpid(pid, &data->fork_status, 0);
	return (data->fork_status);
}

static int	ft_execute_last(t_cmd *temp, t_data *data, int in_fd, int fd[2])
{
	fd[1] = temp->redirect->out_fd;
	if (built_in_checker(temp->args[0]))
	{
		if (built_in_checker(temp->args[0]) != 2)
			ft_builtin_execute(temp, data, in_fd, fd[1]);
		else if (built_in_checker(temp->args[0]) == 2 && data->n_of_cmds == 1)
			ft_builtin_execute(temp, data, in_fd, fd[1]);
	}
	else
		data->exit_status = ft_fork(temp, data, in_fd, fd[1]) % 255;
	if (in_fd != temp->redirect->in_fd)
		close(in_fd);
	if (temp->redirect->in_fd != 0)
		close(temp->redirect->in_fd);
	if (temp->redirect->out_fd != 1)
		close(temp->redirect->out_fd);
	return (0);
}

void	ft_execute(t_data *data)
{
	int		in_fd;
	t_cmd	*temp;

	g_signal = 3;
	temp = data->cmds;
	in_fd = data->cmds->redirect->in_fd;
	while (temp->next)
	{
		pipe(data->fd);
		if (built_in_checker(temp->args[0]))
		{
			if (built_in_checker(temp->args[0]) != 2)
				ft_builtin_execute(temp, data, in_fd, data->fd[1]);
		}
		else
			data->exit_status = ft_fork(temp, data, in_fd, data->fd[1]);
		close(data->fd[1]);
		if (in_fd != temp->redirect->in_fd)
			close(in_fd);
		in_fd = data->fd[0];
		temp = temp->next;
	}
	ft_execute_last(temp, data, in_fd, data->fd);
	status_update(&data->env, data->exit_status);
	return ;
}
