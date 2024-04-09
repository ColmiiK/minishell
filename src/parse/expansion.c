/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvega-g <alvega-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 14:58:01 by alvega-g          #+#    #+#             */
/*   Updated: 2024/04/09 15:57:55 by alvega-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	*ft_loop_var(t_env *env, char *token, char *str)
{
	int	i;

	while (env->next)
	{
		i = -1;
		while (env->var[++i] != '=')
			;
		if (!ft_strncmp(env->var, token + 1, i))
		{
			free(token);
			free(str);
			return (ft_strnstr(env->var, "=", ft_strlen(env->var)) + 1);
		}
		env = env->next;
	}
	return (NULL);
}

static char	*ft_find_variable(char *prompt, t_env *env)
{
	int		j;
	char	*str;
	char	*token;
	char	*temp;

	str = ft_strdup(prompt);
	j = -1;
	while (str[++j] && str[j] != ' ')
		;
	token = (char *)malloc((ft_strlen(str) + 1) * sizeof(char));
	if (!token)
		return (NULL);
	ft_strlcpy(token, str, j + 1);
	temp = ft_loop_var(env, token, str);
	if (temp)
		return (temp);
	free(token);
	free(str);
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
		str = ft_strjoin_ex(str, var, 1);
		while ((prompt[i] != ' ' && prompt[i] != '\n') && prompt[i])
			i++;
		str = ft_strjoin_ex(str, prompt + i, 1);
		free(prompt);
		return (str);
	}
	free(str);
	str = ft_substr(prompt, 0, i);
	free(prompt);
	return (str);
}
