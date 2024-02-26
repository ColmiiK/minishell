/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvega-g <alvega-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 12:50:00 by alvega-g          #+#    #+#             */
/*   Updated: 2024/02/26 13:49:46 by alvega-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void ft_check_access(char *temp, t_data *data, int k)
{
	if (access(temp, F_OK) != -1 && access(temp, X_OK) != -1)
	{
		data->flag = 0;
		data->command[++k] = ft_strdup(temp);
		if (!data->command[k])
			perror("Error: unable to strdup (data->command[k]).");
	}
}

static void	ft_access_cmds(t_data *data)
{
	char	*temp;
	int i;
	int j;
	int k;

	i = -1;
	k = -1;
	while (data->args[++i][0])
	{
		j = -1;
		while (data->path[++j])
		{
			temp = ft_strjoin(data->path[j], data->args[i][0]);
			ft_check_access(temp, data, k);
			free(temp);
		}
		if (data->flag == 1)
			data->command[++k] = ft_strdup("");
		data->flag = 1;
	}
	data->command[k + 1] = NULL;
}

static void	ft_parse_cmds(t_data *data, int ac, char **av)
{
	int	i;
	int	j;

	i = -1;
	j = 1;
	data->args = (char ***)ft_calloc(ac - 1, sizeof(char **));
	if (!data->args)
		ft_perror("Error: unable to malloc (data->args).");
	while (++j < (ac - 1))
		data->args[++i] = ft_split(av[j], ' ');
	data->args[++i] = malloc(sizeof(char *));
	if (!data->args[i])
		ft_perror("Error: unable to malloc (data-args[i])");
	data->args[i][0] = NULL;
	data->command = (char **)ft_calloc(ac - 2, sizeof(char *));
	if (!data->command)
		ft_perror("Error: unable to malloc (data->command).");
	return ;
}

void	ft_parse_envp(t_data *data, char **envp)
{
	int	i;
	int	j;

	i = -1;
	while (envp[++i])
	{
		if (ft_strnstr(envp[i], "PATH=", 5))
		{
			data->path = ft_split(envp[i] + 5, ':');
			i = -1;
			while (data->path[++i])
			{
				j = ft_strlen(data->path[i]);
				data->path[i] = ft_realloc(data->path[i], j + 2);
				if (!data->path[i])
					perror("Error: unable to realloc (data->path[i]).");
				data->path[i][j] = '/';
				data->path[i][j + 1] = 0;
			}
			return ;
		}
	}
}

void	ft_parse_commands(t_data *data, char **envp, int ac, char **av)
{
	int	i;

	i = -1;
	ft_parse_envp(data, envp);
	ft_parse_cmds(data, ac, av);
	ft_access_cmds(data);
	// while (data->args[++i] && data->args[i][0])
	// {
	// 	if (ft_strnstr(data->args[i][0], "awk", 4)
	// 		|| ft_strnstr(data->args[i][0], "sed", 4))
	// 		ft_fix_awk(data, av[i + 2]);
	// }
	return ;
}