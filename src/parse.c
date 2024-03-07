/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvega-g <alvega-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 15:17:50 by alvega-g          #+#    #+#             */
/*   Updated: 2024/03/07 13:31:17 by alvega-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// Crea un archivo temporal para el here_doc
static void ft_here_doc_temp(char *str)
{
	int fd;

	fd = open(".here_doc",  O_WRONLY | O_CREAT | O_TRUNC, 0644);
	write(fd, str, (ft_strlen(str) - 1) * sizeof(char));
	close(fd);
	free(str);
}

// Bucle del here_doc
static void ft_here_doc_loop(char *prompt)
{
	char *temp;
	char *joined;
	char *new_joined;
	char *delimiter;
	int len;

	delimiter = ft_strtok(prompt, " ");
	len = ft_strlen(delimiter);		
	joined = ft_calloc(1, 1);
	if (!joined)
		return ;
	temp = readline("> ");
	while (ft_strncmp(temp, delimiter, len))
	{
		new_joined = ft_strjoin(joined, temp);
		free(joined);
		joined = new_joined;
		new_joined = ft_strjoin(joined, "\n");
		free(joined);
		joined = new_joined;
		free(temp);
		temp = readline("> ");
	}
	free(temp);
	ft_here_doc_temp(joined);
}

static char *ft_here_doc_pipe(char *sub, char *str)
{
	char *input;
	char *trimmed;
	char *temp;
	
	input = readline("> ");
	trimmed = ft_strtrim(sub, "| ");
	temp = ft_strjoin(trimmed, " < .here_doc | ");
	free(trimmed);
	str = ft_strjoin(temp, input);
	free(temp);
	free(input);
	return (str);
}
// Here_doc
static char *ft_here_doc(char *prompt, bool pipe)
{
	char *str;
	char *before;
	char *sub;

	str = NULL;
	before = ft_strdup(prompt);
	ft_here_doc_loop(prompt + 3);
	sub = ft_strnstr(before, ft_strtok(NULL, " "), ft_strlen(before));
	if (pipe)
		str = ft_here_doc_pipe(sub, str);
	else
		str = ft_strjoin(sub, " < .here_doc");
	free(before);
	return (str);
}
// Splitear el prompt para la tabla de comandos
char **ft_parsing(char *prompt)
{
	char **cmds;
	char *temp;
	char *str;
	int i;

	if (ft_strnstr(prompt, "<<", 3))
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
