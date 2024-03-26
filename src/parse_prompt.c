/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_prompt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvega-g <alvega-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 15:17:50 by alvega-g          #+#    #+#             */
/*   Updated: 2024/03/26 19:08:48 by alvega-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// Bucle del here_doc
static void ft_here_doc_loop(char *prompt)
{
	char *temp;
	char *joined;
	char *delimiter;
	int len;
	int fd;

	delimiter = ft_strtok(prompt, " ");
	len = ft_strlen(delimiter);		
	joined = ft_calloc(1, 1);
	if (!joined)
		return ;
	temp = readline("> ");
	while (ft_strncmp(temp, delimiter, len))
	{
		joined = ft_strjoin_ex(joined, temp, 3);
		joined = ft_strjoin_ex(joined, "\n", 1);
		temp = readline("> ");
	}
	free(temp);
	fd = open(".here_doc",  O_WRONLY | O_CREAT | O_TRUNC, 0644);
	write(fd, joined, (ft_strlen(joined) - 1) * sizeof(char));
	close(fd);
	free(joined);
}

static char *ft_here_doc_pipe(char *sub, char *str)
{
	char *input;
	char *trimmed;
	
	input = readline("> ");
	trimmed = ft_strtrim(sub, "| ");
	trimmed = ft_strjoin_ex(trimmed, " < .here_doc | ", 1);
	str = ft_strjoin_ex(trimmed, input, 3);
	return (str);
}

static char *ft_fix_prompt(char *prompt)
{
	char *fixed;
	char *temp;
	int i;

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

// Here_doc
static char *ft_here_doc(char *prompt, bool pipe)
{
	char *str;
	char *before;
	char *sub;

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
// Splitear el prompt para la tabla de comandos
char **ft_parsing(char *prompt)
{
	char **cmds;
	char *temp;
	char *str;
	int i;

	if (ft_strnstr(prompt, "<<", ft_strlen(prompt)))
	{
		if (ft_strrchr(prompt, '|'))
			str = ft_here_doc(prompt, true);
		else
			str = ft_here_doc(prompt, false);
		cmds = ft_split(str, '|');
		free (str);
	}
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
