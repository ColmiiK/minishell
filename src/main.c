/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvega-g <alvega-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 16:32:38 by alvega-g          #+#    #+#             */
/*   Updated: 2024/02/20 17:19:22 by alvega-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*
	Things to implement:
	Execute commands with the right path env
	Handle ' (single quote) which should prevent the shell from interpreting the metacharacters in the sentence
	Handle " (double quote) which should prevent the shell from interpreting the metacharacters in the sentence besides $ (dollar sign)
	DON'T Interpret unclosed quotes, backslash or semicolon
	Redirections
		< should redirect input
		> should redirect output
		<< should be given a delimiter, then read the input until a line containing the delimiter is found (here_doc). It doesn't have to appear in the history
		>> should redirect output in append mode
	Pipes
	Handle environment variables ($ followed by sequence of characters) which should expand to their values
	Handle $? which should expand to the exit status of the most recently executed foreground pipeline
	Handle ctr-C, ctr-D and ctr-\ which should behave like in bash
	In interactive mode
		ctrl-C displays a new prompt on a new line
		ctrl-D exits the shell
		ctrl-\ does nothing
	Following builtins
		echo with -n
		cd with a relative or absolute path
		pwd with no options
		export with no options
		unset with no options
		env with no options or arguments
		exit with no options
	
*/

int main(int ac, char **av)
{
	(void)ac;
	(void)av;
	
	char *input;
	
	input = readline("minishell$> ");
	while (ft_strncmp(input, "EOF", ft_strlen(input)))
	{
		add_history(input);
		free(input);
		input = readline("minishell$> ");	
	}
	free(input);

	printf("History:\n");
	for (int i = history_length; i > 0; i--){
		HIST_ENTRY *entry = history_get(i);
		printf("%d: %s\n", i, entry->line);
	}
	
	
	return (0);
}