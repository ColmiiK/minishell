/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvega-g <alvega-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 16:32:48 by alvega-g          #+#    #+#             */
/*   Updated: 2024/05/07 11:35:26 by alvega-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <libft.h>
# include <signal.h>
# include <termios.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <sys/wait.h>

extern int	g_signal;

typedef struct s_env
{
	char			*name;
	char			*content;
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
	int				exit_status;
	
}	t_data;

// typedef enum e_tokens
// {
// 	PIPE = 0,
// 	GREAT,
// 	DOUBLE_GREAT,
// 	LESS,
// 	DOUBLE_LESS,
// 	FILE,
// 	COMMAND,
// 	ARG,
// }	t_tokens;

typedef struct s_lists
{
	char			*content;
	int				token;
	struct s_lists	*next;
}	t_lists;

// typedef struct s_cmd
// {
// 	char			**cmd_line;
// 	bool			delimiter;
// 	int				input;
// 	int				output;
// 	int				heredoc;
// 	int				append;
// 	int				builtin;
// 	struct s_cmd	*next;
// }	t_cmd;



// LEXER
// init
t_lists	*create_list_node(char *arg);
void	list_add_back(t_lists **list, t_lists *node);
// lexer
// lexer_utils
int		ft_precheck(char *line);
// EXPANDER
// expander
char	*ft_expand_var(char *str, t_env **env);
char	*correct_double_marks(char *content, t_env **env);
int		ft_expander(t_lists **link_list, t_env **env);
// expander_utils
int		mark_search(char *content);
int		nbr_of_marks(char *content, int c);
char	*search_var_name(char *name, t_env **env);
int		search_existing_var(char *str);

// BUILT-INS
// built-ins
int		built_in_checker(char *str);
void	built_in_selector(t_env **env, char **str);
// echo
int		ft_echo(char **arg);
//cd
char	*init_location(void);
char	*adjust_location(char *arg);
int		ft_rel_cd(char **arg);
int		ft_abs_cd(char **arg);
int		ft_cd(char **arg, t_env **node);
//cd_utils
int		update_location(t_env **node, char *new, char *old);
//exit
int		ft_exit(char **arg);
//env
void	free_list(t_env **link_list);
int		ft_env(t_env **link_list);
//preset_env
t_env	*arr_to_list(char **env_cpy, int size);
int		get_size_env(char **env_info);
t_env	*ft_getenv(char **env_info);
//preset_env_utils
void	free_arr(char **env_cpy, int size);
char	*get_name_env(char *str);
char	*get_content_env(char *str);
t_env	*create_node(char *str);
t_env	*next_node(t_env **node, t_env *new);
//export
void	free_node(t_env **node);
t_env	*create_single_cpy(char *name, char *content);
t_env	*ft_cpy_list(t_env **env);
void	ft_order_alpha(t_env **env, int size);
int		ft_export(t_env **env, char *argv);
//export_utils
int		list_length(t_env **env);
void	smart_print(t_env *node);
int		check_existent_var(t_env **env, char *name, char *content);
int		check_correct_input(char *str);
int		create_new_var(t_env **env, char *name, char *content);
//pwd
int		ft_pwd(void);
//unset
int		ft_unset(t_env **env, char *str);

// VARIOUS UTILS
//ps_functions
void	add_back(t_env **env, t_env *new);
void	add_front(t_env **env, t_env *node);
t_env	*pop_first(t_env **env);
void	swap(t_env **env);
//ft_strjoin_mod
char	*ft_strjoin_mod(char *s1, char *s2);




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


// EXECUTION
void	ft_execute(t_data *data);
int		ft_find_path(t_data data);



#endif