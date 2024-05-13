/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvega-g <alvega-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 12:15:22 by alvega-g          #+#    #+#             */
/*   Updated: 2024/05/13 14:52:08 by alvega-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	**ft_here_doc_capture(char *prompt, t_data *data)
{
	char	*str;
	char	**cmds;

	g_signal = 2;
	if (ft_strrchr(prompt, '|'))
		str = ft_here_doc(prompt, true, data);
	else
		str = ft_here_doc(prompt, false, data);
	while (ft_strnstr(str, "$", ft_strlen(str))
		&& !ft_strnstr(str, "\\$", ft_strlen(str)))
		str = ft_expand_variables(str, data->env);
	cmds = ft_split(str, '|');
	free (str);
	printf("cmds: %s\n", cmds[0]);
	return (cmds);
}

static int ft_check_syntax(char *str, bool first, bool d_flag, bool s_flag)
{
	while (*str)
	{
		if (!s_flag && *str == '\"')
			d_flag = !d_flag;
		if (!d_flag && *str == '\'')
			s_flag = !s_flag;
		if ((!s_flag || !d_flag ) && first == true && *str == '|')
			return (1);
		if ((!s_flag && !d_flag ) && ft_check_metachars(*str, 3))
		{
			str++;
			if (*str == '<' || *str == '>')
				str++;
			while (*str && *str == ' ')
				str++;
			if (!*str || ft_check_metachars(*str, 3))
				return (1);
			return (0);
		}
		if (!ft_check_metachars(*str, 3) && *str != ' ')
			first = false;
		str++;
	}
	return (0);
}

static char	**ft_parsing(char *prompt, t_data *data)
{
	char	**cmds;
	char	*temp;
	int		i;

	if (ft_check_syntax(prompt, true, false, false))
	{
		ft_putendl_fd("minishell: syntax error near unexpected token", 2);
		return (ft_split(" ", ' '));
	}
	if (ft_strnstr(prompt, "<<", ft_strlen(prompt)))
		cmds = ft_here_doc_capture(prompt, data);
	else if (!ft_strnstr(prompt, "\\|", ft_strlen(prompt))) // echo '|' | "a"
		cmds = ft_split(prompt, '|');
	else
		cmds = ft_split(prompt, '\0');
	g_signal = 1;
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


int ft_count_chars(char *str, char c, bool s_flag, bool d_flag)
{
	int count;

	count = 0;
	while (*str)
	{
		if (!s_flag && *str == '\"')
			d_flag = !d_flag;
		if (!d_flag && *str == '\'')
			s_flag = !s_flag;
		if ((!s_flag && !d_flag ) && *str == c)
			count++;
		str++;
	}
	return (count);
}


char *ft_fix_multiple_out(char *cmd)
{
	int i;
	int j;
	char **temp;
	char *str;

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
		str = ft_substr(cmd, 0 , j + 1);
		str = ft_strjoin_ex(str, temp[i], 1);
		free(cmd);
		ft_clean_double_ptr(temp);
		return (str);
	}
	return(cmd);
}

char **ft_multiple_redirections(char **cmds)
{
	int i;

	i = -1;
	while (cmds[++i])
		cmds[i] = ft_fix_multiple_out(cmds[i]);
	return (cmds);
}

int	ft_parsing_loop(t_data *data)
{
	char	*prompt;
	char	**cmds;
	char	**redirect;

	g_signal = 1;
	prompt = readline(MINI_PROMPT);
	if (!prompt)
		return (printf(MINI_EXIT));
	if (prompt[0] != '\0')
		add_history(prompt);
	prompt = ft_handle_quotes(prompt, false, false);
	if (ft_all_same(prompt, ' ') || ft_all_same(prompt, '\t'))
		prompt = ft_strdup_ex("", prompt);
	cmds = ft_parsing(prompt, data);
	cmds = ft_multiple_redirections(cmds);
	redirect = ft_redirections(cmds);
	cmds = ft_clean_cmds(cmds);
	data->cmds = ft_setup_nodes(cmds, redirect, data->env);
	data->n_of_cmds = ft_double_ptr_amount(cmds);
	ft_clean_double_ptr(cmds);
	ft_clean_double_ptr(redirect);
	free(prompt);
	return (0);
}
