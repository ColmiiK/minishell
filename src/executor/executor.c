/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvega-g <alvega-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 17:10:25 by alvega-g          #+#    #+#             */
/*   Updated: 2024/05/07 13:19:07 by alvega-g         ###   ########.fr       */
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
		if (in_fd != 0)
		{
			dup2(in_fd, 0);
			close(in_fd);
		}
		if (out_fd != 1)
		{
			dup2(out_fd, 1);
			close(out_fd);
		}
		if (built_in_checker(cmd->cmd))
			built_in_selector(&env, cmd->args);
		else
		{
			variables = ft_get_variables(env);
			if (execve(cmd->cmd, cmd->args, variables) == -1)
				free(variables);
		}
		exit(1);
	}
	waitpid(pid, &status, 0);
	return (0);
}

void	ft_execute(t_data *data)
{
	int in_fd;
	int fd[2];

	in_fd = 0;
	while (data->cmds->next)
	{
		pipe(fd);
		ft_fork(data->cmds, data->env, in_fd, fd[1]);
		close(fd[1]);
		in_fd = fd[0];
		data->cmds = data->cmds->next;
	}
	ft_fork(data->cmds, data->env, in_fd, fd[1]);
	return ;
}
