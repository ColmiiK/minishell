/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvega-g <alvega-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 16:32:48 by alvega-g          #+#    #+#             */
/*   Updated: 2024/04/30 18:11:30 by alvega-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <libft.h>
# include <signal.h>
# include <termios.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <wait.h>

extern int	g_signal;

typedef struct s_env
{
	char			*var;
	struct s_env	*next;
}	t_env;

typedef struct s_redirect
{
	int				in_fd;
	int				out_fd;
}	t_redirect;

typedef struct s_cmd
{
	char			*cmd;
	char			**args;
	t_redirect		*redirect;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_data
{
	t_cmd			*cmds;
	int				n_of_cmds;
	t_env			*env;
	struct termios	termios;
}	t_data;

// Signals
void	ft_handle_sigint(int signum);
void	ft_handle_sigquit(int signum);

// Main parsing loop
int		ft_parsing_loop(t_data *data);

// Parses env to the list
t_env	*ft_parse_env(char **env);
// Expands enviroment variables
char	*ft_expand_variables(char *prompt, t_env *env);
// Heredoc
char	*ft_here_doc(char *prompt, bool pipe, t_data *data);
char	*ft_hd_process(struct termios termios);
void	ft_hd_finish(char *temp, char *joined);
char	*ft_fix_hd_outfile(char *s1);
char	*ft_fix_prompt(char *prompt);
// Handle quotes
char	*ft_handle_quotes(char *prompt);
// Parses redirections
char	**ft_redirections(char **cmds);
// Cleans commands
char	**ft_clean_cmds(char **cmds);
// Setup nodes for the list
t_cmd	*ft_setup_nodes(char **cmds, char **redirect, t_env *env);

// Free double pointer used in parsing
void	ft_clean_double_ptr(char **ptr);
// Free commands, arguments and redirections for next loop
void	ft_annihilation(t_data *data);
// Free env list at the end of execution
void	ft_cleanup_env(t_env *env);
// Write given error message and return error (1)
int		ft_perror(char *str);

#endif