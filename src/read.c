/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvega-g <alvega-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 10:47:58 by alvega-g          #+#    #+#             */
/*   Updated: 2024/02/26 11:51:40 by alvega-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*
-> READ
Start of loop
Display default prompt (minishell$ ) [readline()]
	if here_doc exists
		Capture it
		if it ends with a pipe
			Display prompt for further reading (> )
		if it doesn't
			Save the history [add_history()]
	if it doesn't
		if it ends with a pipe
			Display prompt for further reading (> )
		if it doesn't
			Save the history [add_history()]
Send the input to EVALUATE
*/

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

void ft_here_doc(t_data *data)
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
		input = readline("> ");
		data->command = ft_strjoin(data->command, input);
		data->command = ft_strjoin(data->command, "\n");
	}
}