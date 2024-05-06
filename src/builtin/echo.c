/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvega-g <alvega-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 12:15:58 by albagar4          #+#    #+#             */
/*   Updated: 2024/05/06 15:19:50 by alvega-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// Empieza en el 1 porque la posicion 0 deberia contener el comando echo
int	ft_echo(char **arg)
{
	int	i;

	i = 1;
	if (!arg[1])
		return (ft_printf("\n"), 0);
	if (ft_strncmp(arg[1], "-n", 3) == 0)
		i = 2;
	while (arg[i] != NULL)
	{
		ft_printf("%s", arg[i]);
		if (arg[i + 1])
			ft_printf(" ");
		i++;
	}
	if (ft_strncmp(arg[1], "-n", 3) != 0)
		ft_printf("\n");
	return (0);
}
