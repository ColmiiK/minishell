/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvega-g <alvega-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 13:45:24 by alvega-g          #+#    #+#             */
/*   Updated: 2024/05/13 16:49:46 by alvega-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*ft_fix_hd_outfile(char *s1)
{
	char	*str;
	char	*token;
	char	*temp;
	int		len;

	str = ft_strdup(s1);
	token = ft_strtok(str, " ");
	temp = ft_strdup(token);
	token = ft_strtok(NULL, " ");
	temp = ft_strjoin_ex(temp, " ", 1);
	temp = ft_strjoin_ex(temp, token, 1);
	len = ft_strlen(temp);
	s1 = ft_strjoin_ex(s1, " ", 1);
	s1 = ft_strjoin_ex(s1, temp, 3);
	free(str);
	temp = ft_strdup(s1 + len);
	free(s1);
	return (temp);
}

char	*ft_fix_prompt(char *prompt)
{
	char	*fixed;
	char	*temp;
	int		i;

	if (!ft_strncmp(prompt, "<<", 2))
		return (ft_strdup(prompt));
	i = 0;
	while (prompt[i] != '<')
		i++;
	fixed = (char *)malloc(i * sizeof(char));
	if (!fixed)
		return (0);
	ft_strlcpy(fixed, prompt, i);
	fixed = ft_strjoin_ex(" ", fixed, 2);
	while (prompt[i] != '<')
		i++;
	fixed = ft_strjoin_ex(prompt, fixed, 2);
	temp = ft_strdup(fixed + i);
	free(fixed);
	return (temp);
}

char	*ft_find_delimiter(char *prompt)
{
	char	*temp;
	int		i;
	int		j;

	i = 0;
	while (prompt[i] == ' ')
		i++;
	j = 0;
	while (prompt[i + j] && ft_isalnum(prompt[i + j]))
		j++;
	temp = ft_substr(prompt, i, j);
	return (temp);
}

char	*ft_multiple_hd(char *str)
{
	int	i;

	i = 2;
	while (str[i] == ' ')
		i++;
	while (str[i] != ' ')
		i++;
	while (str[i] == ' ')
		i++;
	return (str);
}

char	*ft_hd_recurse(char *sub, t_data *data)
{
	char	*temp;
	char	*temp2;

	temp2 = sub;
	sub = ft_multiple_hd(sub);
	sub = ft_fix_prompt(sub);
	ft_here_doc_loop(ft_strnstr(sub, "<<", ft_strlen(sub)), data);
	temp = sub;
	sub = ft_find_command_after(sub + 2);
	if (ft_strnstr(sub, "<<", ft_strlen(sub)))
		sub = ft_hd_recurse(sub, data);
	free(temp);
	free(temp2);
	return (sub);
}
