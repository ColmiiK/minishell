/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvega-g <alvega-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 16:32:48 by alvega-g          #+#    #+#             */
/*   Updated: 2024/02/26 13:49:34 by alvega-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <libft.h>
# include <readline/history.h>
# include <readline/readline.h>

typedef struct s_commands
{
	char *cmd;
	int n_of_args;
	char **args;
	
}	t_commands;

typedef struct s_data
{
	
	bool here_doc;
	bool here_doc_pipe;
	char *delimiter;
	char *command;
	char **tokens;
	char *infile;
	char *outfile;
	char *mode;
	char **path;
	char ***args;
	bool flag;
	t_commands *table;

}	t_data;

void ft_read(char *input, t_data *data);
void ft_here_doc(t_data *data);
void ft_tokenization(t_data *data);
void	ft_parse_commands(t_data *data, char **envp, int ac, char **av);

#endif