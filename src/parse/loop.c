/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvega-g <alvega-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 12:15:22 by alvega-g          #+#    #+#             */
/*   Updated: 2024/04/01 13:03:24 by alvega-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_parsing_loop(t_data *data)
{
	char	*prompt;
	char	**cmds;
	char	**redirect;

	prompt = readline("minishell$ ");
	cmds = ft_parsing(prompt);
	redirect = ft_redirections(cmds);
	cmds = ft_clean_cmds(cmds);
	data->cmds = ft_setup_nodes(cmds, redirect);
	if (!data->cmds)
		return (1);
	data->n_of_cmds = ft_double_ptr_amount(cmds);
	add_history(prompt);
	
	ft_clean_double_ptr(cmds);
	ft_clean_double_ptr(redirect);
	free(prompt);
	
	return (0);
}
