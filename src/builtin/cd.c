/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvega-g <alvega-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 17:40:17 by albagar4          #+#    #+#             */
/*   Updated: 2024/05/06 15:19:50 by alvega-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*init_location(void)
{
	char	*location;

	location = (char *)malloc(_PC_PATH_MAX * sizeof(char *));
	if (!location)
		return (NULL);
	location = getcwd(location, sizeof(location));
	location = getcwd(location, sizeof(location));
	return (location);
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
	settled = (char *)malloc((ft_strlen(arg) + 1) * sizeof(char *));
	if (!settled)
		return (NULL);
	settled = ft_strjoin(slash, arg);
	return (settled);
}

int	ft_rel_cd(char **arg)
{
	char	*location;
	char	*dest;
	char	*adjust;
	int		total_size;

	location = init_location();
	adjust = adjust_location(arg[1]);
	if (location != NULL)
	{
		total_size = ft_strlen(arg[1]) + ft_strlen(location);
		dest = (char *)malloc(total_size * sizeof(char *));
		if (!dest)
			return (-1);
		dest = ft_strjoin(location, adjust);
		if (chdir(dest) != 0)
			return (printf("error_manag\n"), -1);
		return (0);
	}
	else
		return (-1);
}

int	ft_abs_cd(char **arg)
{
	if (chdir(arg[1]) != 0)
		return (printf("error_manag\n"), -1);
	return (0);
}

int	ft_cd(char **arg, t_env **node)
{
	char	*location;
	int		size;

	/* if (arg[1] != 0)
		arg[1] = $HOME; */ //(Mirar en el expande como mandar la dirección de home)
	location = init_location();
	if (location != NULL)
	{
		size = ft_strlen(location);
		if (!ft_strncmp(location, arg[1], size))
			ft_abs_cd(arg);
		else
			ft_rel_cd(arg);
		update_location(node, init_location(), location);
		return (0);
	}
	else
		return (-1);
}
