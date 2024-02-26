/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvega-g <alvega-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 10:47:58 by alvega-g          #+#    #+#             */
/*   Updated: 2024/02/26 16:42:26 by alvega-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void ft_read(char *input, t_data *data)
{
	char *str;

	str = ft_strdup(input);
	if (ft_strnstr(input, "<<", ft_strlen(input)))
	{
		data->here_doc = true;
		input = ft_strrchr(input, '<');
		data->delimiter = ft_strtok(++input, " ");
	}
	else
		data->here_doc = false;
	if (ft_strchr(str, '|'))
		data->here_doc_pipe = true;
	else
		data->here_doc_pipe = false;
}

void ft_here_doc(t_data *data) // Checks if there is a here_doc
{
	char *input;
	
	data->command = ft_strdup("");
	if (data->here_doc_pipe == false)
	{
		while (ft_strncmp(input, data->delimiter, ft_strlen(input)))
		{
			input = readline("> ");
			if (!ft_strncmp(input, data->delimiter, ft_strlen(input)))
				return ;
			data->command = ft_strjoin(data->command, input);
			data->command = ft_strjoin(data->command, "\n");
			free(input);
		}		
	}
	else
	{
		while (ft_strncmp(input, data->delimiter, ft_strlen(input)))
		{
			input = readline("> ");
			if (!ft_strncmp(input, data->delimiter, ft_strlen(input)))
				break ;
			data->command = ft_strjoin(data->command, input);
			data->command = ft_strjoin(data->command, "\n");
			free(input);
		}
		input = readline("> "); // Capture the command after the EOF
		data->command = ft_strjoin(data->command, input);
		data->command = ft_strjoin(data->command, "\n");
		free(input);
	}
}