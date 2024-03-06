/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvega-g <alvega-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 15:17:50 by alvega-g          #+#    #+#             */
/*   Updated: 2024/03/06 16:58:20 by alvega-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*
 cat -e < infile.txt
 cat -e > outifle.txt
 cat -e >> outfile.txt
 << EOF cat -e
 << EOF cat -e |
*/
// Crea un archivo temporal para el here_doc
static void ft_here_doc_temp(char *str)
{
	int fd;

	fd = open(".here_doc",  O_WRONLY | O_CREAT | O_TRUNC, 0644);
	write(fd, str, (ft_strlen(str) - 1) * sizeof(char));
	close(fd);
}
// Bucle del here_doc
static void ft_here_doc_loop(char *prompt)
{
	char *temp;
	char *joined;
	char *delimiter;
	int len;

	prompt += 3;
	delimiter = ft_strtok(prompt, " ");
	len = ft_strlen(delimiter);		
	joined = ft_calloc(1, 1);
	if (!joined)
		return ;
	temp = readline("> ");
	while (ft_strncmp(temp, delimiter, len))
	{
		joined = ft_strjoin(joined, temp);
		joined = ft_strjoin(joined, "\n");
		temp = readline("> ");
	}
	ft_here_doc_temp(joined);
}
// Here_doc
static char *ft_here_doc(char *prompt, bool pipe)
{
	char *str;
	char *temp;
	char *before;

	before = ft_strdup(prompt);
	ft_here_doc_loop(prompt);
	if (pipe == true)
	{
		temp = readline("> ");
		before = ft_strnstr(before, ft_strtok(NULL, " "), ft_strlen(before));
		before = ft_strtrim(before, "| ");
		str = ft_strjoin(before, " < .here_doc | ");
		str = ft_strjoin(str, temp);
		free (before);
	}
	else
	{
		temp = ft_strtok(NULL, " ");
		before = ft_strnstr(before, temp, ft_strlen(before));
		str = ft_strjoin(before, " < .here_doc");
	}
	return (str);
}
// Splitear el prompt para la tabla de comandos
char **ft_parsing(char *prompt)
{
	char **cmds;
	char *str;
	int i;

	if (ft_strnstr(prompt, "<<", 3))
	{
		if (ft_strrchr(prompt, '|'))
			str = ft_here_doc(prompt, true);
		else
			str = ft_here_doc(prompt, false);
		prompt = str;
	}
	cmds = ft_split(prompt, '|');
	i = -1;
	while (cmds[++i])
		cmds[i] = ft_strtrim(cmds[i], " ");
	cmds[i] = NULL;
	return (cmds); 	
}
// Rellenar el string de redirección con la info si la hay, o default si no
static char *ft_capture_files(char *cmd, char *redirect)
{
	if (ft_strchr(cmd, '<'))
		redirect = ft_strjoin("IN:", ft_strnstr(cmd, "<", ft_strlen(cmd)) + 2);
	else
		redirect = ft_strdup("IN:0");
	if (ft_strchr(cmd, '>'))
	{
		if (ft_strnstr(cmd, ">>", ft_strlen(cmd)))
		{
			redirect = ft_strjoin(redirect, " OUT(A):");
			redirect = ft_strjoin(redirect, ft_strnstr(cmd, ">", ft_strlen(cmd)) + 3);
		}
		else
		{
			redirect = ft_strjoin(redirect, " OUT:");
			redirect = ft_strjoin(redirect, ft_strnstr(cmd, ">", ft_strlen(cmd)) + 2);
		}
	}
	else
		redirect = ft_strjoin(redirect, " OUT:1");
	redirect[ft_strlen(redirect)] = 0;
	return (redirect);
}
// Crear array con redirecciones
char **ft_redirections(char **cmds)
{
	char **redirect;
	int i;

	i = 0;
	while (cmds[i])
		i++;
	redirect = ft_calloc(i + 1, sizeof(char*));
	i = -1;
	while (cmds[++i])
		redirect[i] = ft_capture_files(cmds[i], redirect[i]);
	i = 0;
	while (redirect[i])
		i++;
	redirect[i] = NULL;
	return (redirect);
}
