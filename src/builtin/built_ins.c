/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvega-g <alvega-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 16:56:45 by albagar4          #+#    #+#             */
/*   Updated: 2024/05/09 16:22:43 by alvega-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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

void	built_in_selector(t_data *data, char **str)
{
	if (!ft_strncmp(str[0], "echo", 5))
		ft_echo(str);
	else if (!ft_strncmp(str[0], "cd", 3))
		ft_cd(str, &data->env);
	else if (!ft_strncmp(str[0], "pwd", 4))
		ft_pwd();
	else if (!ft_strncmp(str[0], "export", 7))
		ft_export(&data->env, str[1]);
	else if (!ft_strncmp(str[0], "unset", 6))
		ft_unset(&data->env, str[1]);
	else if (!ft_strncmp(str[0], "env", 4))
		ft_env(&data->env);
	else if (!ft_strncmp(str[0], "exit", 5))
		ft_exit(str);
}
