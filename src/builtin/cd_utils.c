/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvega-g <alvega-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 12:07:50 by albagar4          #+#    #+#             */
/*   Updated: 2024/05/06 15:19:50 by alvega-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	update_location(t_env **node, char *new, char *old)
{
	t_env	*tmp;

	tmp = *node;
	while (*node)
	{
		if (!ft_strncmp((*node)->name, "PWD", 4))
			(*node)->content = new;
		if (!ft_strncmp((*node)->name, "OLDPWD", 7))
			(*node)->content = old;
		*node = (*node)->next;
	}
	*node = tmp;
	return (0);
}
