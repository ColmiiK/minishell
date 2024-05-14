/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvega-g <alvega-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 16:56:45 by albagar4          #+#    #+#             */
/*   Updated: 2024/05/14 10:07:07 by alvega-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	exit_checker(char **str)
{
	if (str[1] != NULL && ft_isalpha_loop(str[1]) == 0 && str[2] != NULL)
		return (printf("exit: too many arguments\n"), 1);
	else
		return (0);
}

int	built_in_checker(char *str)
{
	if (!ft_strncmp(str, "echo", 5) || !ft_strncmp(str, "cd", 3)
		|| !ft_strncmp(str, "pwd", 4) || !ft_strncmp(str, "export", 7)
		|| !ft_strncmp(str, "unset", 6) || !ft_strncmp(str, "env", 4))
		return (1);
	else if (!ft_strncmp(str, "exit", 5))
		return (2);
	else
		return (0);
}

void	built_in_selector2(t_data *data, char **str)
{
	if (!ft_strncmp(str[0], "echo", 5))
		data->exit_status = ft_echo(str);
	else if (!ft_strncmp(str[0], "cd", 3))
		data->exit_status = ft_cd(str, &data->env);
	else if (!ft_strncmp(str[0], "pwd", 4))
		data->exit_status = ft_pwd();
}

void	built_in_selector(t_data *data, char **str, int infd, int outfd)
{
	int	i;

	i = 0;
	built_in_selector2(data, str);
	if (!ft_strncmp(str[0], "export", 7))
	{
		if (str[i + 1] == NULL)
			data->exit_status = ft_export(&data->env, NULL);
		while (str[++i] != NULL)
			data->exit_status = ft_export(&data->env, str[i]);
	}
	else if (!ft_strncmp(str[0], "unset", 6))
		while (str[++i] != NULL)
			data->exit_status = ft_unset(&data->env, str[i]);
	else if (!ft_strncmp(str[0], "env", 4))
		data->exit_status = ft_env(&data->env);
	else if (!ft_strncmp(str[0], "exit", 5))
	{
		if (exit_checker(str) == 0 && data->n_of_cmds == 1)
			data->exit_status = ft_exit(data, infd, outfd);
		else
			data->exit_status = 1;
	}
}
