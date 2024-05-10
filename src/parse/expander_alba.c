/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_alba.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvega-g <alvega-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 12:51:19 by albagar4          #+#    #+#             */
/*   Updated: 2024/05/10 13:35:56 by alvega-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	mark_search(char *content)
{
	int	i;

	i = 0;
	while (content[i] != '\0')
	{
		if (content[i] == 34)
			return (1);
		else if (content[i] == 39)
			return (2);
		i++;
	}
	return (0);
}

int	nbr_of_marks(char *content, int c)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (content[i] != '\0')
	{
		if (content[i] == c)
			count++;
		i++;
	}
	return (count);
}

int	search_existing_var(char *str)
{
	int		i;
	int		count;
	int		start;
	char	*tmp;

	i = 0;
	count = 0;
	while (str[i] != '\0')
	{
		if (str[i] == 36)
		{
			start = ++i;
			while (str[i] != 36 && str[i] != 32 && str[i] != '\0'
				&& str[i] != 39)
				i++;
			tmp = ft_substr(str, start, i - start - 1);
			if (check_correct_input(tmp) == 0)
				count++;
			start = i;
		}
		i++;
	}
	return (count);
}

char	*search_var_name(char *name, t_env **env)
{
	t_env	*tmp;
	char	*space;

	tmp = *env;
	space = malloc(sizeof(char) * 2);
	if (!space)
		return (NULL);
	space[0] = 32;
	space[1] = '\0';
	while (tmp)
	{
		if (!ft_strncmp(name, tmp->name, ft_strlen(name)))
		{
			if (tmp->content)
				return (tmp->content);
			else
				return (space);
		}
		tmp = tmp->next;
	}
	return (space);
}

char	*ft_expand_var(char *s, t_env **env)
{
	char	*aux;
	char	*var_name;
	int		start;
	int		i;

	i = 0;
	start = 0;
	aux = NULL;
	var_name = NULL;
	printf("s: %s\n", s);
	
	while (s[i] != '\0')
	{
		if (s[i] == 36)
		{
			printf("%c ", s[i]);
			if (start == 0)
				aux = ft_substr(s, start, i - start);
			else
				aux = ft_strjoin_mod(aux, ft_substr(s, start, i - start));
			printf("aux: %s\n", aux);
			start = ++i;
			while (s[i] != 32 && s[i] != 36 && s[i] != '\0' && s[i] != 39)
				i++;
			var_name = ft_substr(s, start, i - start);
			printf("var: %s\n", var_name);
			var_name = ft_strdup(search_var_name(var_name, env));
			aux = ft_strjoin_mod(aux, var_name);
			start = i;
		}
		else
			i++;
	}
	var_name = ft_substr(s, start, i - start);
	aux = ft_strjoin_mod(aux, var_name);
	return (aux);
}

char	*correct_double_marks(char *content, t_env **env)
{
	int		i;
	char	*str;

	i = nbr_of_marks(content, 34);
	if (i > 0)
		str = ft_substr(content, 1, (ft_strlen(content) - 2));
	else
		str = ft_strdup(content);
	if (search_existing_var(str) > 0)
		str = ft_expand_var(str, env);
	return (str);
}

char	*ft_expander(char *str, t_env **env)
{
	if (mark_search(str) != 2)
	{
		if (search_existing_var(str) > 0)
			str = ft_expand_var(str, env);
	}
	if (mark_search(str) != 0)
		str = ft_substr(str, 1, (ft_strlen(str) - 2));
	return (str);
}
