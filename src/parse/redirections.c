/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvega-g <alvega-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 13:30:20 by alvega-g          #+#    #+#             */
/*   Updated: 2024/05/08 16:51:28 by alvega-g         ###   ########.fr       */
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
	return (ft_strjoin("IN:", temp));
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
	re = ft_strjoin_ex(re, temp, 1);
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
	re = ft_strjoin_ex(re, temp, 1);
	return (re);
}

static char	*ft_capture_files(char *cmd, char *re)
{
	if (ft_strchr(cmd, '<') && !ft_strnstr(cmd, "\\<", ft_strlen(cmd)))
	{
		re = ft_add_infile(cmd, re);
	}
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
	printf("re: %s\n", re);
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

static char	*ft_trim_redirect(char *str, char chr)
{
	char	*ptr;
	char	*trimmed;
	int		len;

	ptr = ft_strrchr(str, chr);
	if (ptr)
	{
		len = ptr - str;
		trimmed = ft_calloc(len + 1, sizeof(char));
		ft_strlcpy(trimmed, str, len);
		trimmed[len] = 0;
		return (trimmed);
	}
	return (str);
}

char	**ft_clean_cmds(char **cmds)
{
	char	*temp;
	int		i;

	i = -1;
	while (cmds[++i])
	{
		if (ft_strrchr(cmds[i], '<')
			&& !ft_strnstr(cmds[i], "\\<", ft_strlen(cmds[i])))
		{
			temp = cmds[i];
			cmds[i] = ft_trim_redirect(temp, '<');
			free(temp);
		}
		if (ft_strrchr(cmds[i], '>')
			&& !ft_strnstr(cmds[i], "\\>", ft_strlen(cmds[i])))
		{
			temp = cmds[i];
			cmds[i] = ft_trim_redirect(temp, '>');
			free(temp);
		}
	}
	return (cmds);
}
