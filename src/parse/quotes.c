/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvega-g <alvega-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 12:54:41 by alvega-g          #+#    #+#             */
/*   Updated: 2024/05/02 12:26:22 by alvega-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

bool	ft_check_metachars(char *result, int i, bool flag, bool double_quote)
{
	if (double_quote == true)
	{
		if (flag && (result[i] == '\\' || result[i] == '|' || result[i] == '<'
				|| result[i] == '>' || result[i] == ' ' || result[i] == '\t'
				|| result[i] == '\n' || result[i] == '(' || result[i] == ')'
				|| result[i] == ';' || result[i] == '&' || result[i] == '\''))
			return (true);
	}
	else if (double_quote == false)
	{
		if (flag && (result[i] == '$' || result[i] == '\\' || result[i] == '|'
				|| result[i] == '<' || result[i] == '>' || result[i] == ' '
				|| result[i] == '\t' || result[i] == '\n' || result[i] == '('
				|| result[i] == ')' || result[i] == ';' || result[i] == '&'
				|| result[i] == '\"'))
			return (true);
	}
	return (false);
}

static char	*ft_single_quotes(char *str, char quotes)
{
	bool	flag;
	char	*result;
	int		i;

	result = ft_strdup_ex(str, str);
	i = -1;
	flag = false;
	while (result[++i])
	{
		if (i == 0 && result[i] == quotes)
			flag = !flag;
		else if (i != 0 && result[i - 1] != '\\' && result[i] == quotes)
			flag = !flag;
		if (ft_check_metachars(result, i, flag, false) == true)
			result = ft_strinsert(result, i++, "\\", 1);
	}
	if (flag == true)
	{
		free(result);
		return (ft_calloc(1, 1));
	}
	return (result);
}

static char	*ft_double_quotes(char *str, char quotes)
{
	bool	flag;
	char	*result;
	int		i;

	result = ft_strdup_ex(str, str);
	i = -1;
	flag = false;
	while (result[++i])
	{
		if (i == 0 && result[i] == quotes)
			flag = !flag;
		else if (i != 0 && result[i - 1] != '\\' && result[i] == quotes)
			flag = !flag;
		if (ft_check_metachars(result, i, flag, true) == true)
			result = ft_strinsert(result, i++, "\\", 1);
	}
	if (flag == true)
	{
		free(result);
		return (ft_calloc(1, 1));
	}
	return (result);
}

char	*ft_handle_quotes(char *prompt)
{
	char	*str;

	if (!*prompt)
		return (prompt);
	str = prompt;
	if (ft_strnstr(str, "\'", ft_strlen(str)))
		str = ft_single_quotes(str, '\'');
	if (ft_strnstr(str, "\"", ft_strlen(str)))
		str = ft_double_quotes(str, '\"');
	if (!str[0])
	{
		printf("Unclosed quotes not implemented\n");
		return (str);
	}
	return (str);
}
