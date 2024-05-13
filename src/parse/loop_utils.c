/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvega-g <alvega-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 16:35:30 by alvega-g          #+#    #+#             */
/*   Updated: 2024/05/13 17:28:53 by alvega-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_count_chars(char *str, char c, bool s_flag, bool d_flag)
{
	int	count;

	count = 0;
	while (*str)
	{
		if (!s_flag && *str == '\"')
			d_flag = !d_flag;
		if (!d_flag && *str == '\'')
			s_flag = !s_flag;
		if ((!s_flag && !d_flag) && *str == c)
			count++;
		str++;
	}
	return (count);
}

char	*ft_fix_multiple_out_append(char *cmd)
{
	int		i;
	int		j;
	char	**temp;
	char	*str;

	if (ft_count_chars(cmd, '>', false, false) > 2)
	{
		temp = ft_split(cmd, '>');
		i = 0;
		while (temp[++i + 1])
		{
			temp[i] = ft_strtrim_ex(temp[i], " ", true);
			close(open(temp[i], O_WRONLY | O_CREAT | O_TRUNC, 0644));
		}
		j = -1;
		while (cmd[++j] != '>')
			;
		str = ft_substr(cmd, 0, j + 2);
		str = ft_strjoin_ex(str, temp[i], 1);
		free(cmd);
		ft_clean_double_ptr(temp);
		return (str);
	}
	return (cmd);
}

char	*ft_append_or_trunc(char *cmd, char **temp, int j, int i)
{
	char	*str;
	int		z;

	z = ft_strlen(cmd);
	while (cmd[z--] != '>')
	{
		if (cmd[z] == '>' && cmd[z - 1] == '>')
		{
			str = ft_substr(cmd, 0, j + 2);
			str = ft_strjoin_ex(str, temp[i], 1);
			free(cmd);
			ft_clean_double_ptr(temp);
			return (str);
		}
		else if (cmd[z] == '>')
		{
			str = ft_substr(cmd, 0, j + 1);
			str = ft_strjoin_ex(str, temp[i], 1);
			free(cmd);
			ft_clean_double_ptr(temp);
			return (str);
		}
	}
	return (cmd);
}

char	*ft_fix_multiple_out(char *cmd)
{
	int		z;
	int		i;
	int		j;
	char	**temp;
	char	*str;

	if (ft_count_chars(cmd, '>', false, false))
	{
		temp = ft_split(cmd, '>');
		i = 0;
		while (temp[++i + 1])
		{
			temp[i] = ft_strtrim_ex(temp[i], " ", true);
			close(open(temp[i], O_WRONLY | O_CREAT | O_TRUNC, 0644));
		}
		j = -1;
		while (cmd[++j] != '>')
			;
		z = ft_strlen(cmd);
		str = ft_append_or_trunc(cmd, temp, j, i);
		return (str);			
	}
	return (cmd);
}

char	**ft_multiple_redirections(char **cmds)
{
	int	i;

	i = -1;
	while (cmds[++i])
	{
		if (ft_strnstr(cmds[i], ">", ft_strlen(cmds[i])))
			cmds[i] = ft_fix_multiple_out(cmds[i]);
	}
	return (cmds);
}
