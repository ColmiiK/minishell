/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvega-g <alvega-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 16:32:48 by alvega-g          #+#    #+#             */
/*   Updated: 2024/03/06 15:19:55 by alvega-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <libft.h>
# include <readline/history.h>
# include <readline/readline.h>

typedef struct s_data
{
	char **cmds;
	char **redirect;
	
}	t_data;

// Parse
char **ft_parsing(char *prompt);
char **ft_redirections(char **cmds);

#endif