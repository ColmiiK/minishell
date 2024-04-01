/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvega-g <alvega-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 16:32:48 by alvega-g          #+#    #+#             */
/*   Updated: 2024/04/01 10:43:02 by alvega-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <libft.h>
# include <readline/history.h>
# include <readline/readline.h>

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
	char			*args;
	t_redirect		*redirect;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_data
{
	t_cmd			*cmds;
	int				n_of_cmds;
	t_env			*env;
}	t_data;

// Main parsing loop
int		ft_parsing_loop(t_data *data);

// Parses env to the list
t_env	*ft_parse_env(char **env);
// Parses commands and arguments
char	**ft_parsing(char *prompt);
// Parses redirections
char	**ft_redirections(char **cmds);
// Cleans commands
char	**ft_clean_cmds(char **cmds);
// Setup nodes for the list
t_cmd	*ft_setup_nodes(char **cmds, char **redirect);

// Free double pointer used in parsing
void	ft_clean_double_ptr(char **ptr);
// Free commands, arguments and redirections for next loop
void	ft_annihilation(t_data *data);
// Free env list at the end of execution
void	ft_cleanup_env(t_env *env);

#endif