/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvega-g <alvega-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 16:32:48 by alvega-g          #+#    #+#             */
/*   Updated: 2024/03/27 17:19:20 by alvega-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <libft.h>
# include <readline/history.h>
# include <readline/readline.h>

typedef struct s_env
{
	char		*var;
	t_env		*next;

}	t_env;

typedef struct s_redirect
{
	int			in_fd;
	int			out_fd;

}	t_redirect;

typedef struct s_cmd
{
	char		*cmd;
	char		*args;
	t_redirect	*redirect;
	t_cmd		*next;

}	t_cmd;

typedef struct s_data
{
	t_cmd		*cmds;
	t_env		*env;
	
}	t_data;

// Parse
char **ft_parse_env(char **env);
char **ft_parsing(char *prompt);
char **ft_redirections(char **cmds);
char **ft_clean_cmds(char **cmds);
// CLeanup
void ft_clean_double_ptr(char **ptr);

#endif