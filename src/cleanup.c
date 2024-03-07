/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvega-g <alvega-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 13:36:48 by alvega-g          #+#    #+#             */
/*   Updated: 2024/03/07 13:36:59 by alvega-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void ft_annihilation(t_data data, char *prompt)
{
	int i;

	free(prompt);
	i = -1;
	while (data.cmds[++i])
	{
		free(data.cmds[i]);
		free(data.redirect[i]);
	}
	free(data.cmds);
	free(data.redirect);
}
