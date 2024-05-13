/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albagar4 <albagar4@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 12:15:58 by albagar4          #+#    #+#             */
/*   Updated: 2024/05/13 13:29:03 by albagar4         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_correct_flag(char *str)
{
	int	i;

	i = 1;
	while (str[i] != '\0')
	{
		if (str[i] == 'n')
			i++;
		else
			return (1);
	}
	return (0);
}

int	ft_echo(char **arg)
{
	int	i;

	i = 1;
	if (!arg[1])
		return (ft_printf("\n"), 0);
	while ((!ft_strncmp(arg[i], "-n", 2)) && ft_correct_flag(arg[i]) == 0)
		i++;
	while (arg[i] != NULL)
	{
		ft_printf("%s", arg[i]);
		if (arg[i + 1])
			ft_printf(" ");
		i++;
	}
	if ((ft_strncmp(arg[1], "-n", 2) && ft_correct_flag(arg[1]) == 0)
		|| ft_correct_flag(arg[1]) == 1)
		ft_printf("\n");
	return (0);
}
