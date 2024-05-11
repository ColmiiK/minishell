/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_nodes_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvega-g <alvega-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 17:12:31 by alvega-g          #+#    #+#             */
/*   Updated: 2024/05/11 17:51:02 by alvega-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_determine_in_fd(char *redirect)
{
	int		fd;
	int		i;
	char	*str;

	redirect = ft_strchr(redirect, ':');
	redirect++;
	i = -1;
	while (redirect[++i] != ' ')
		;
	str = ft_substr(redirect, 0, i);
	if (ft_isdigit(*redirect))
		fd = ft_atoi(redirect);
	else if (*str)
		fd = open(str, O_RDONLY);
	else
		fd = 0;
	free(str);
	return (fd);
}

int	ft_determine_out_fd(char *redirect)
{
	int		fd;

	redirect = ft_strrchr(redirect, ':');
	redirect++;
	if (ft_isdigit(*redirect))
		fd = ft_atoi(redirect);
	else if (ft_strnstr(redirect - 4, "(A)", ft_strlen(redirect)))
		fd = open(redirect, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = open(redirect, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	return (fd);
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
