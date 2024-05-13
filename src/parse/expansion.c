/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvega-g <alvega-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 14:58:01 by alvega-g          #+#    #+#             */
/*   Updated: 2024/05/13 16:31:17 by alvega-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	*ft_loop_var(t_env *env, char *token)
{
	while (env)
	{
		if (!ft_strncmp(env->name, token + 1, ft_strlen(token)))
		{
			free(token);
			if (env->content)
				return (env->content);
			return (NULL);
		}
		env = env->next;
	}
	free(token);
	return (NULL);
}

static char	*ft_find_variable(char *prompt, t_env *env)
{
	int		j;
	char	*str;
	char	*token;
	char	*temp;

	str = ft_strdup(prompt);
	j = 0;
	while (str[++j] && (ft_isalpha(str[j]) || str[j] == '?'))
		;
	token = (char *)malloc((ft_strlen(str) + 1) * sizeof(char));
	if (!token)
		return (NULL);
	ft_strlcpy(token, str, j + 1);
	temp = ft_loop_var(env, token);
	temp = ft_strjoin_ex(temp, str + j, 0);
	free(str);
	if (temp)
		return (temp);
	return (NULL);
}

char	*ft_expand_variables(char *prompt, t_env *env)
{
	char	*str;
	char	*var;
	int		i;

	str = ft_calloc(ft_strlen(prompt) + 1, sizeof(char));
	if (!str)
		return (NULL);
	i = -1;
	while (prompt[++i] != '$')
		str[i] = prompt[i];
	var = ft_find_variable(prompt + i, env);
	if (var)
	{
		str = ft_strjoin_ex(str, var, 3);
		free(prompt);
		return (str);
	}
	free(str);
	str = ft_substr(prompt, 0, i);
	free(prompt);
	return (str);
}
