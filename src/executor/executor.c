/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvega-g <alvega-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 17:10:25 by alvega-g          #+#    #+#             */
/*   Updated: 2024/05/06 19:13:00 by alvega-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char **ft_get_variables(t_env *env)
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

int ft_fork_executor(char *path, char **args, char **env, int *exit_value)
{
	pid_t pid;

	pid = fork();
	if (pid == -1)
		return (1);
	if (pid == 0)
	{
		if (execve(path, args, env) == -1)
			exit (1);
	}
	else
	{
		waitpid(pid, exit_value, 0);
		if (*exit_value == 1)
			return (1);
	}
	return (0);
}

int ft_executor(t_data *data)
{
	char **variables;

	variables = ft_get_variables(data->env);
	while (data->cmds)
	{
		if (ft_fork_executor(data->cmds->cmd, data->cmds->args, variables, &(data->exit_status)))
			return (1);
		data->cmds = data->cmds->next;
	}
	return (0);
}
