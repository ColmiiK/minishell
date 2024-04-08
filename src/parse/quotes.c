/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvega-g <alvega-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 12:54:41 by alvega-g          #+#    #+#             */
/*   Updated: 2024/04/08 17:24:11 by alvega-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char *ft_single_quotes(char *str, char quotes)
{
	bool flag;
	char *result;
	int i;

	i = -1;
	flag = false;
	while (str[++i])
	{
		if (str[i] == quotes)
			flag = !flag;
		if (flag && (str[i] == '$' || str[i] == '\\'))
			result = ft_strinsert(str, i, "\\", 1);
	}
	if (flag == true)
	{
		free(result);
		return (NULL);
	}
	return (result);
}

static char *ft_double_quotes(char *str, char quotes)
{
	bool flag;
	char *result;
	int i;

	i = -1;
	flag = false;
	while (str[++i])
	{
		if (str[i] == quotes)
			flag = !flag;
		if (flag && (str[i] == '$' || str[i] == '\\'))
			result = ft_strinsert(str, i, "\\", 1);
	}
	if (flag == true)
	{
		free(result);
		return (NULL);
	}
	return (result);
}

char *ft_handle_quotes(char *prompt)
{
	char *str;

	str = prompt;
	printf("1: %s\n", str);
	
	if (ft_strnstr(prompt, "\'", ft_strlen(prompt)))
		str = ft_single_quotes(prompt, '\'');
		
	printf("2: %s\n", str);
	
	if (ft_strnstr(prompt, "\"", ft_strlen(prompt)))
		str = ft_double_quotes(prompt, '\"');
	
	printf("3: %s\n", str);
	
	if (!str)
	{
		free(prompt);
		printf("Unclosed quotes not implemented\n");
		return (ft_calloc(1, 1));
	}
	return (str);
}
