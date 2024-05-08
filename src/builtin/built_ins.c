/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albagar4 <albagar4@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 16:56:45 by albagar4          #+#    #+#             */
/*   Updated: 2024/05/08 18:02:36 by albagar4         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	built_in_checker(char *str)
{
	if (!ft_strncmp(str, "echo", 5) || !ft_strncmp(str, "cd", 3)
		|| !ft_strncmp(str, "pwd", 4) || !ft_strncmp(str, "export", 7)
		|| !ft_strncmp(str, "unset", 6) || !ft_strncmp(str, "env", 4)
		|| !ft_strncmp(str, "exit", 5))
		return (1);
	else
		return (0);
}

void	built_in_selector(t_env **env, char **str)
{
	if (!ft_strncmp(str[0], "echo", 5))
		ft_echo(str);
	else if (!ft_strncmp(str[0], "cd", 3))
		ft_cd(str, env);
	else if (!ft_strncmp(str[0], "pwd", 4))
		ft_pwd();
	else if (!ft_strncmp(str[0], "export", 7))
		ft_export(env, str[1]);
	else if (!ft_strncmp(str[0], "unset", 6))
	{
		ft_unset(env, str[1]);
		printf("*env == %s\n", (*env)->name);	
	}
	else if (!ft_strncmp(str[0], "env", 4))
		ft_env(env);
	else if (!ft_strncmp(str[0], "exit", 5))
		ft_exit(str);
}
