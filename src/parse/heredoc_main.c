/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvega-g <alvega-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 15:17:50 by alvega-g          #+#    #+#             */
/*   Updated: 2024/05/11 17:10:55 by alvega-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	ft_hd_after_first(char **joined, char **temp,
	char **delimiter, t_data *data)
{
	while (!(ft_strncmp(*temp, *delimiter, ft_strlen(*delimiter)) == 0
			&& ft_strlen(*temp) == ft_strlen(*delimiter)))
	{
		*joined = ft_strjoin_ex(ft_strjoin_ex(*joined, *temp, 3), "\n", 1);
		*temp = ft_hd_process(data->termios);
		if (g_signal == 4)
		{
			free(*delimiter);
			free(*joined);
			free(*temp);
			return (1);
		}
		if (!*temp)
			*temp = ft_strdup(*delimiter);
	}
	return (0);
}

static void	ft_here_doc_loop(char *prompt, t_data *data)
{
	char	*temp;
	char	*joined;
	char	*delimiter;

	delimiter = ft_find_delimiter(prompt + 2);
	temp = ft_hd_process(data->termios);
	if (g_signal == 4)
	{
		free(delimiter);
		free(temp);
		return ;
	}
	if (!temp)
		temp = ft_strdup(delimiter);
	joined = ft_calloc(1, 1);
	if (!joined)
		return ;
	if (ft_hd_after_first(&joined, &temp, &delimiter, data))
		return ;
	while (ft_strnstr(joined, "$", ft_strlen(joined)))
		joined = ft_expand_variables(joined, data->env);
	free(delimiter);
	ft_hd_finish(temp, joined);
}

static char	*ft_here_doc_pipe(char *sub, char *str, t_data *data)
{
	char	*input;
	char	*trimmed;

	input = ft_hd_process(data->termios);
	if (!input)
	{
		printf("minishell: syntax error: unexpected end of file\n");
		return (ft_calloc(1, 1));
	}
	trimmed = ft_strtrim(sub, "| ");
	trimmed = ft_strjoin_ex(trimmed, " < .here_doc | ", 1);
	str = ft_strjoin_ex(trimmed, input, 3);
	return (str);
}

static char *ft_find_command_after(char *prompt)
{
	char *temp;
	int i;

	i = 0;

	while (prompt[i] && prompt[i] == ' ')
		i++;
	while (prompt[i] && prompt[i] != ' ')
		i++;
	while (prompt[i] && prompt[i] == ' ')
		i++;
	temp = ft_substr(prompt, i, ft_strlen(prompt + i));
	return (temp);
}

char	*ft_here_doc(char *prompt, bool pipe, t_data *data)
{
	char	*str;
	char	*sub;

	str = NULL;
	prompt = ft_fix_prompt(prompt);
	ft_here_doc_loop(ft_strnstr(prompt, "<<", ft_strlen(prompt)), data);
	sub = ft_find_command_after(prompt + 2);
	if (!pipe)
	{
		str = ft_strjoin(sub, " < .here_doc");
		if (ft_strchr(str, '>'))
			str = ft_fix_hd_outfile(str);
	}
	else if (pipe)
		str = ft_here_doc_pipe(sub, str, data);
	free(sub);
	free(prompt);
	if (g_signal == 4)
	{
		free(str);
		return (ft_calloc(1, 1));
	}
	return (str);
}
