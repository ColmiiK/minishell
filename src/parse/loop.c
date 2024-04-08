/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvega-g <alvega-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 12:15:22 by alvega-g          #+#    #+#             */
/*   Updated: 2024/04/08 11:09:04 by alvega-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	**ft_here_doc_capture(char *prompt, t_data *data)
{
	char	*str;
	char	**cmds;

	if (ft_strrchr(prompt, '|'))
		str = ft_here_doc(prompt, true, data);
	else
		str = ft_here_doc(prompt, false, data);
	while (ft_strnstr(str, "$", ft_strlen(str)))
		str = ft_expand_variables(str, data->env);
	cmds = ft_split(str, '|');
	free (str);
	return (cmds);
}

static char	**ft_parsing(char *prompt, t_data *data)
{
	char	**cmds;
	char	*temp;
	int		i;

	if (ft_strnstr(prompt, "<<", ft_strlen(prompt)))
		cmds = ft_here_doc_capture(prompt, data);
	else
		cmds = ft_split(prompt, '|');
	i = -1;
	while (cmds[++i])
	{
		temp = cmds[i];
		cmds[i] = ft_strtrim(temp, " ");
		free(temp);
	}
	cmds[i] = NULL;
	return (cmds);
}

int	ft_parsing_loop(t_data *data)
{
	char	*prompt;
	char	**cmds;
	char	**redirect;

	prompt = readline("minishell$ ");
	if (!prompt)
	{
		printf("\033[1Aminishell$ exit\n");
		return (1);
	}
	if (prompt[0] != '\0')
		add_history(prompt);
	while (ft_strnstr(prompt, "$", ft_strlen(prompt)))
		prompt = ft_expand_variables(prompt, data->env);
	cmds = ft_parsing(prompt, data);
	redirect = ft_redirections(cmds);
	cmds = ft_clean_cmds(cmds);
	data->cmds = ft_setup_nodes(cmds, redirect);
	data->n_of_cmds = ft_double_ptr_amount(cmds);
	ft_clean_double_ptr(cmds);
	ft_clean_double_ptr(redirect);
	free(prompt);
	return (0);
}
