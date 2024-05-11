/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvega-g <alvega-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 12:54:41 by alvega-g          #+#    #+#             */
/*   Updated: 2024/05/11 17:15:18 by alvega-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

bool	ft_check_metachars(char c, int mode)
{
	if (mode == 1)
	{
		if (c == '$' || c == '\\' || c == '|' || c == '<' || c == '>'
			|| c == ' ' || c == '\t' || c == '\n' || c == '(' || c == ')'
			|| c == ';' || c == '&' || c == '\"')
			return (true);
	}
	else if (mode == 2)
	{
		if (c == '\\' || c == '|' || c == '<' || c == '>' || c == ' '
			|| c == '\t' || c == '\n' || c == '(' || c == ')' || c == ';'
			|| c == '&' || c == '\'')
			return (true);
	}
	else if (mode == 3)
	{
		if (c == '\\' || c == '|' || c == '<' || c == '>'
			|| c == '\t' || c == '\n' || c == '(' || c == ')'
			|| c == ';' || c == '&')
			return (true);
	}
	return (false);
}

char *ft_single_quotes(char *str)
{
	char *temp;
	int i;

	temp = ft_strdup(str);
	i = -1;
	while (temp[++i])
	{
		if (ft_check_metachars(temp[i], 1))
		{
			temp = ft_strinsert(temp, i, "\\", 0);
			i++;
		}
	}
	
	return (temp);
}

char *ft_double_quotes(char *str)
{
	char *temp;
	int i;

	temp = ft_strdup(str);
	i = -1;
	while (temp[++i])
	{
		if (ft_check_metachars(temp[i], 2))
		{
			temp = ft_strinsert(temp, i, "\\", 0);
			i++;
		}
	}
	
	return (temp);
}

static bool ft_check_amount(char *str, bool flag_single, bool flag_double)
{
	int i;
	int counter_single;
	int counter_double;

	counter_single = 0;
	counter_double = 0;
	i = -1;
	while (str[++i])
	{
		if (!flag_double && str[i] == '\'')
		{
			flag_single = !flag_single;
			counter_single++;
		}
		if (!flag_single && str[i] == '\"')
		{
			flag_double = !flag_double;
			counter_double++;
		}
	}
	if (counter_single % 2 != 0 || counter_double % 2 != 0)
		return (true);
	return (false);
}

char *ft_handle_quotes(char *prompt, bool d_flag, bool s_flag)
{
	int i;

	if (ft_check_amount(prompt, false, false))
		return (printf("Unclosed quotes\n"), ft_strdup(""));
	i = -1;
	while (prompt[++i])
	{
		if (!s_flag && prompt[i] == '\"')
			d_flag = !d_flag;
		if (!d_flag && prompt[i] == '\'')
			s_flag = !s_flag;
		if (s_flag)
		{
			if (ft_check_metachars(prompt[i], 1))
				prompt = ft_strinsert(prompt, i++, "\\", 1);
		}
		else if (d_flag)
		{
			if (ft_check_metachars(prompt[i], 2))
				prompt = ft_strinsert(prompt, i++, "\\", 1);
		}
	}
	return (prompt);
}
