/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvega-g <alvega-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 13:30:20 by alvega-g          #+#    #+#             */
/*   Updated: 2024/05/11 17:46:53 by alvega-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char* ft_add_infile(char *cmd, char *re)
{
	char *temp;
	int i;
	int j;

	i = -1;
	while (cmd[++i] != '<')
		;
	while (cmd[i] == ' ')
		i++;
	if (cmd[i] == '<')
		i++;
	while (cmd[i] == ' ')
		i++;
	j = 0;
	while (cmd[i + j] && cmd[i + j] != ' ')
		j++;
	temp = ft_substr(cmd, i, j);
	free(re);
	return (ft_strjoin_ex("IN:", temp, 2));
}

static char *ft_add_outfile_append(char *cmd, char *re)
{
	char *temp;
	int i;
	int j;
	

	
	re = ft_strjoin_ex(re, " OUT(A):", 1);
	i = 0;
	while (cmd[i] != '>')
		i++;
	while (cmd[i] == ' ')
		i++;
	while (cmd[i] == '>')
		i++;
	while (cmd[i] == ' ')
		i++;
	j = 0;
	while (cmd[i + j] && cmd[i + j] != ' ')
		j++;
	temp = ft_substr(cmd, i, j);
	re = ft_strjoin_ex(re, temp, 3);
	return (re);
}

static char *ft_add_outfile(char *cmd, char *re)
{
	char *temp;
	int i;
	int j;
	
	re = ft_strjoin_ex(re, " OUT:", 1);
	i = 0;
	while (cmd[i] != '>')
		i++;
	while (cmd[i] == ' ')
		i++;
	if (cmd[i] == '>')
		i++;
	while (cmd[i] == ' ')
		i++;
	j = 0;
	while (cmd[i + j] && cmd[i + j] != ' ')
		j++;
	temp = ft_substr(cmd, i, j);
	re = ft_strjoin_ex(re, temp, 3);
	return (re);
}

static char	*ft_capture_files(char *cmd, char *re)
{
	if (ft_strchr(cmd, '<') && !ft_strnstr(cmd, "\\<", ft_strlen(cmd)))
		re = ft_add_infile(cmd, re);
	else
		re = ft_strdup_ex("IN:0", re);
	if (ft_strchr(cmd, '>') && !ft_strnstr(cmd, "\\>", ft_strlen(cmd)))
	{
		if (ft_strnstr(cmd, ">>", ft_strlen(cmd))
			&& !ft_strnstr(cmd, "\\>>", ft_strlen(cmd)))
			re = ft_add_outfile_append(cmd, re);
		else
			re = ft_add_outfile(cmd, re);
	}
	else
		re = ft_strjoin_ex(re, " OUT:1", 1);
	re[ft_strlen(re)] = 0;
	return (re);
}

char	**ft_redirections(char **cmds)
{
	char	**redirect;
	int		i;

	i = 0;
	while (cmds[i])
		i++;
	redirect = ft_calloc(i + 1, sizeof(char *));
	i = -1;
	while (cmds[++i])
		redirect[i] = ft_capture_files(cmds[i], redirect[i]);
	i = 0;
	while (redirect[i])
		i++;
	redirect[i] = NULL;
	return (redirect);
}
