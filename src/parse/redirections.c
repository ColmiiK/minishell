/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvega-g <alvega-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 13:30:20 by alvega-g          #+#    #+#             */
/*   Updated: 2024/03/28 12:12:47 by alvega-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char *ft_upd(char *redirect, char *new_value)
{
	free(redirect);
	return new_value;
}

static char *ft_capture_files(char *cmd, char *re)
{
	if (ft_strchr(cmd, '<'))
		re = ft_upd(re, ft_strjoin("IN:", ft_strnstr(cmd, "<", ft_strlen(cmd)) + 2));
	else
		re = ft_upd(re, ft_strdup("IN:0"));
	if (ft_strchr(cmd, '>'))
	{
		if (ft_strnstr(cmd, ">>", ft_strlen(cmd)))
		{
			re = ft_strjoin_ex(re, " OUT(A):", 1);
			re = ft_strjoin_ex(re, ft_strnstr(cmd, ">", ft_strlen(cmd)) + 3, 1);
		}
		else
		{
			re = ft_strjoin_ex(re, " OUT:", 1);
			re = ft_strjoin_ex(re, ft_strnstr(cmd, ">", ft_strlen(cmd)) + 2, 1);
		}
	}
	else
		re = ft_strjoin_ex(re, " OUT:1", 1);
	re[ft_strlen(re)] = 0;
	return (re);
}

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

static char *ft_trim_redirect(char *str, char chr)
{
	char *ptr;
	char *trimmed;
	int len;
	
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

char **ft_clean_cmds(char **cmds)
{
	char *temp;
	int i;

	i = -1;
	while (cmds[++i])
	{
		if (ft_strrchr(cmds[i], '<'))
		{
			temp = cmds[i];	
			cmds[i] = ft_trim_redirect(temp, '<');
			free(temp);
		}
		else if (ft_strrchr(cmds[i], '>'))
		{
			temp = cmds[i];
			cmds[i] = ft_trim_redirect(temp, '>');
			free(temp);
		}
	}
	return (cmds);
}
