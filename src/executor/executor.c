/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvega-g <alvega-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 17:10:25 by alvega-g          #+#    #+#             */
/*   Updated: 2024/05/08 12:47:39 by alvega-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>


static char **ft_get_variables(t_env *env)
{
	char *temp;
	char **variables;

	temp = ft_strdup("");
	while (env)
	{
		temp = ft_strjoin_ex(temp, env->var, 1);
		temp = ft_strjoin_ex(temp, "\n", 1);
		env = env->next;
	}
	variables = ft_split(temp, '\n');
	free(temp);
	return (variables);
}

static int ft_fd_juggling(int in_fd, int out_fd)
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

static int ft_builtin_execute(t_cmd *cmd, t_env *env, int in_fd, int out_fd)
{
	// int exit_value;
	int saved_in_fd;
	int saved_out_fd;

	saved_in_fd = dup(0);
	saved_out_fd = dup(1);

	if (ft_fd_juggling(in_fd, out_fd))
		return (1);

	if (built_in_checker(cmd->cmd))
		built_in_selector(&env, cmd->args);

	dup2(saved_in_fd, 0);
	dup2(saved_out_fd, 1);
	close(saved_in_fd);
	close(saved_out_fd);

	return (0);
	// return (exit_value);
	
}

static int ft_fork(t_cmd *cmd, t_env *env, int in_fd, int out_fd)
{
	pid_t pid;
	int status;
	char **variables;
	
	pid = fork();
	if (pid == -1)
		return (1);
	if (pid == 0)
	{
		if (ft_fd_juggling(in_fd, out_fd))
			return (1);
		variables = ft_get_variables(env);
		if (execve(cmd->cmd, cmd->args, variables) == -1)
			free(variables);
		exit(1);
	}
	waitpid(pid, &status, 0);
	return (status);
}

static int ft_execute_last(t_data data, int in_fd, int fd[2])
{
	fd[1] = data.cmds->redirect->out_fd;
	if (built_in_checker(data.cmds->cmd))
	{
		if (built_in_checker(data.cmds->cmd) != 2)
			data.exit_status = ft_builtin_execute(data.cmds, data.env, in_fd, fd[1]);
		else if (built_in_checker(data.cmds->cmd) == 2 && data.n_of_cmds == 1)
			data.exit_status = ft_builtin_execute(data.cmds, data.env, in_fd, fd[1]);
	}
	else
		data.exit_status = ft_fork(data.cmds, data.env, in_fd, fd[1]);
	if (in_fd != data.cmds->redirect->in_fd)
		close(in_fd);
	if (data.cmds->redirect->in_fd != 0)
		close(data.cmds->redirect->in_fd);
	if (data.cmds->redirect->out_fd != 1)
		close(data.cmds->redirect->out_fd);
	return (0);
}

void	ft_execute(t_data data)
{
	int in_fd;
	int fd[2];

	in_fd = data.cmds->redirect->in_fd;
	while (data.cmds->next)
	{
		pipe(fd);
		if (built_in_checker(data.cmds->cmd))
		{
			if (built_in_checker(data.cmds->cmd) != 2)
				data.exit_status = ft_builtin_execute(data.cmds, data.env, in_fd, fd[1]);
		}
		else
			data.exit_status = ft_fork(data.cmds, data.env, in_fd, fd[1]);
		close(fd[1]);
		if (in_fd != data.cmds->redirect->in_fd)
			close(in_fd);
		in_fd = fd[0];
		data.cmds = data.cmds->next;
	}
	ft_execute_last(data, in_fd, fd);
	return ;
}
