/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvega-g <alvega-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 15:17:50 by alvega-g          #+#    #+#             */
/*   Updated: 2024/04/03 16:41:43 by alvega-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	ft_here_doc_loop(char *prompt)
{
	char	*temp;
	char	*joined;
	char	*delimiter;
	int		fd;

	delimiter = ft_strtok(prompt, " ");
	joined = ft_calloc(1, 1);
	if (!joined)
		return ;
	temp = readline("> ");
	if (!temp)
		temp = ft_strdup(delimiter);
	while (ft_strncmp(temp, delimiter, ft_strlen(delimiter)))
	{
		joined = ft_strjoin_ex(ft_strjoin_ex(joined, temp, 3), "\n", 1);
		temp = readline("> ");
		if (!temp)
			temp = ft_strdup(delimiter);
	}
	free(temp);
	fd = open(".here_doc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (joined[0] != '\0')
		write(fd, joined, (ft_strlen(joined) - 1) * sizeof(char));
	close(fd);
	free(joined);
}

static char	*ft_here_doc_pipe(char *sub, char *str)
{
	char	*input;
	char	*trimmed;

	input = readline("> ");
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

static char	*ft_fix_prompt(char *prompt)
{
	char	*fixed;
	char	*temp;
	int		i;

	if (!ft_strncmp(prompt, "<<", 2))
		return (ft_strdup(prompt));
	i = 0;
	while (prompt[i] != '<')
		i++;
	fixed = (char *)malloc(i * sizeof(char));
	if (!fixed)
		return (0);
	ft_strlcpy(fixed, prompt, i);
	fixed = ft_strjoin_ex(" ", fixed, 2);
	while (prompt[i] != '<')
		i++;
	fixed = ft_strjoin_ex(prompt, fixed, 2);
	temp = ft_strdup(fixed + i);
	free(fixed);
	return (temp);
}

char	*ft_here_doc(char *prompt, bool pipe)
{
	char	*str;
	char	*before;
	char	*sub;

	str = NULL;
	prompt = ft_fix_prompt(prompt);
	before = ft_strdup(prompt);
	ft_here_doc_loop(ft_strnstr(prompt, "<<", ft_strlen(prompt)) + 3);
	sub = ft_strnstr(before, ft_strtok(NULL, " "), ft_strlen(before));
	if (pipe)
		str = ft_here_doc_pipe(sub, str);
	else
		str = ft_strjoin(sub, " < .here_doc");
	free(before);
	free(prompt);
	return (str);
}
