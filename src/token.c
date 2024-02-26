/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvega-g <alvega-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 12:00:16 by alvega-g          #+#    #+#             */
/*   Updated: 2024/02/26 13:42:39 by alvega-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*
-> EVALUATE
Tokenization [ft_strtok()]
	Read input [ft_strchr()]
	Discard extra control characters (' ', \t, etc.) 
	Identify special tokens (|, >, >>, etc.)
	Create token list to be passed for next steps [malloc()?]
Parsing
	Read token list
	Check for syntax correctness (ex. ls > | echo) [ifs]
	If syntax is not correct, flow halts and returns an error, back to displaying default prompt 
Set up table of commands
	Read token list
	Breaks a pipeline into commands (command name/path, flags, redirections)
*/

void ft_pipe_token(t_data *data, char *next_cmd) // Redirect STD_OUT to STD_IN
{
		
}

void ft_input_token(t_data *data, char *infile) // Redirect STD_IN to INFILE
{
	data->infile = infile;
}

void ft_output_token(t_data *data, char *outfile, int mode) // Redirect STD_OUT to OUTFILE
{
	if (mode == 0)
		data->mode = "O_TRUNC";
	else
		data->mode = "O_APPEND";
	data->outfile = outfile;
}


void ft_special_tokens(char **tokens, t_data *data)
{
	int i;

	i = -1;
	while (tokens[++i])
	{
		if (ft_strncmp(tokens[i], "|", 1))
			ft_pipe_token(data, tokens[i + 1]);
		else if (ft_strncmp(tokens[i], "<", 1))
			ft_input_token(data, tokens[i + 1]);
		else if (ft_strncmp(tokens[i], ">", 0))
			ft_output_token(data, tokens[i + 1], 0);
		else if (ft_strncmp(tokens[i], ">>", 1))
			ft_output_token(data, tokens[i + 1], 1);
	}
}

int ft_syntax_tokens(char **tokens)
{
	
}

void ft_parse_tokens(char **tokens)
{
	int i;

	if (ft_syntax_tokens(tokens))
		perror("Error:\nIncorrect syntax.");
	i = -1;
	while (tokens[++i])
	{
		
	}
}

void ft_tokenization(t_data *data)
{
	printf("minishell$ %s\n", data->command);
	char *str;
	int i;
	
	data->tokens = (char **)malloc(sizeof(char *));
	str = ft_strtok(data->command, " \t");
	i = 0;
	while (str)
	{
		data->tokens[i++] = str;
		str = ft_strtok(NULL, " \t");
	}
	data->tokens[i] = NULL;
	ft_special_tokens(data->tokens, data);
	// ft_parse_tokens(data->tokens);
	for (int x = 0; data->tokens[x]; x++)
		printf("%s\n", data->tokens[x]);
}