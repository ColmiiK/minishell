/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvega-g <alvega-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 12:54:41 by alvega-g          #+#    #+#             */
/*   Updated: 2024/04/08 13:53:26 by alvega-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char *ft_insert_quotes(char *str, char quotes)
{
	bool flag;
    int i;
	int j;
	char *result;
	
	result = malloc((strlen(str) * 2 + 1) * sizeof(char));
	flag = false;
	i = -1;
	j = 0;
	while (str[++i])
    {
        if (str[i] == quotes)
            flag = !flag;
        if (flag && (str[i] == '$' || str[i] == '`' || str[i] == '\"' || str[i] == '\\'))
            result[j++] = '\\';
        result[j++] = str[i];
    }
    result[j] = '\0';
    return (result);
}

char *ft_handle_quotes(char *prompt)
{
	char *str;

	printf("after: %s\n", prompt);
	str = prompt;
	if (ft_strnstr(prompt, "\'", ft_strlen(prompt)))
		str = ft_insert_quotes(prompt, '\'');
	if (ft_strnstr(prompt, "\"", ft_strlen(prompt)))
		str = ft_insert_quotes(prompt, '\"');
	
	printf("before: %s\n", str);
	if (!str)
	{
		perror("Error: unclosed quotes not implemented\n");
		return (NULL); // o ft_strdup("") que si no da segfault
	}
	return (str);
	
}
