/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albagar4 <albagar4@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 17:40:17 by albagar4          #+#    #+#             */
/*   Updated: 2024/05/13 13:02:15 by albagar4         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*init_location(void)
{
	char	*location;

	location = NULL;
	return (getcwd(location, _PC_PATH_MAX));
}

char	*adjust_location(char *arg)
{
	char	*settled;
	char	*slash;

	slash = (char *)malloc(2 * sizeof(char *));
	if (!slash)
		return (NULL);
	slash[0] = 47;
	slash[1] = '\0';
	settled = ft_strjoin_ex(slash, arg, 1);
	return (settled);
}

int	ft_rel_cd(char *arg)
{
	char	*location;
	char	*dest;
	char	*adjust;
	int		total_size;

	location = init_location();
	adjust = adjust_location(arg);
	if (location != NULL)
	{
		total_size = ft_strlen(arg) + ft_strlen(location);
		dest = ft_strjoin_ex(location, adjust, 3);
		if (chdir(dest) != 0)
			return (printf("folder does not exist\n"), 1);
		free(dest);
		return (0);
	}
	else
		return (1);
}

int	ft_abs_cd(char *arg)
{
	if (chdir(arg) != 0)
		return (printf("folder does not exist\n"), 1);
	return (0);
}

int	ft_cd(char **arg, t_env **node)
{
	char	*temp;
	char	*location;
	int		size;

	location = init_location();
	if (arg[1] == NULL || !ft_strcmp(arg[1], "~"))
		homepath_cd(node, location);
	else if (!strcmp(arg[1], "-"))
		oldpath_cd(node);
	else if (location != NULL)
	{
		size = ft_strlen(location);
		if (!ft_strncmp(location, arg[1], size))
			ft_abs_cd(arg[1]);
		else
			ft_rel_cd(arg[1]);
		temp = init_location();
		update_location(node, temp, location);
		free(temp);
		temp = NULL;
	}
	else
		return (1);
	return (0);
}
