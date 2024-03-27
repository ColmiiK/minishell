 /* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvega-g <alvega-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 16:32:38 by alvega-g          #+#    #+#             */
/*   Updated: 2024/03/07 13:40:17 by alvega-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*
	Things to implement:
	Execute commands with the right path env
	Handle ' (single quote) which should prevent the shell from interpreting the metacharacters in the sentence
	Handle " (double quote) which should prevent the shell from interpreting the metacharacters in the sentence besides $ (dollar sign)
	DON'T INTERPRET ANY SPECIAL CHARACTER NOT REQUIRED OR SPECIFIED BY THE SUBJECT ('\', ';', '&', ...)
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

Shell initialization -> READ user input -> EVALUATE input -> PRINT result -> repeat

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

*Set signals for the status of READ [signal functios]
*ctrl-C, ctrl-D and ctrl-\ must work as they do in bash (signal interpetation)

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

-> PRINT
Execution [execve()]
Handle redirects (check files, opening them if needed)
Check if
	it has absolute path, otherwise [access()]
	if it's found in $PATH [access()]
	if it's a builtin
Commands must be run within forks [fork()]
Output might be printed anywhere (Redirected STD_OUT) [dup2()]
Careful with redirects, if they are captured in the command table, they must be implemented in the executor inside each fork for each command separately
Error messages must always be printed in STD_ERR (Don't implement special characters not in the subject, ie. '&')
Write error messages in case of syntax / execution / read error
Set variable '$?' to the return code of the command on the last round of execution. TEST WITH BASH HEAVILY

The shell has two modes
-> INTERACTIVE MODE
User provides input commands in real-time.
Shell displays a prompt to indicate it's ready for user input.
Commands are executed immediately after the user hits the "Enter" key.
The shell displays command output immediately after execution.
The shell might have features like command history and autocompletion to assist the user.


-> NON-INTERACTIVE MODE
Shell doesn't wait for user input
Commands are provided to the shell through a script file or command-line arguments.
The shell doesn't display a prompt.
Commands can be executed in sequence without user intervention.
Output might not be displayed unless explicitly redirected to a file or shown using other means.

Repeat :)
	
	


Resources
(video walkthrough) https://lzcorp-my.sharepoint.com/personal/thelazyprogrammer_lzcorp_onmicrosoft_com/_layouts/15/onedrive.aspx?ga=1&id=%2Fpersonal%2Fthelazyprogrammer%5Flzcorp%5Fonmicrosoft%5Fcom%2FDocuments%2FPublic%20ALX%20Resources%2FVideo%20Tutorials%2FPLD%20Sessions%2FCodeMinds
(part 1) https://www.youtube.com/watch?v=2xayf6AMNtU
(part 2) https://youtu.be/_Eioyt7C67M?si=Ej8yp6gDnRbNM2Yy
(unix shell scripting) https://www.evernote.com/shard/s594/client/snv?isnewsnv=true&noteGuid=66a64240-fec1-5d15-6e3e-b03d1b4a1f59&noteKey=5e8Bavzw33bFvGEs5PSnNDNSBmB7nBrz2Alfnq2Okfme6-1Gk6QOkdWNSA&sn=https%3A%2F%2Fwww.evernote.com%2Fshard%2Fs594%2Fsh%2F66a64240-fec1-5d15-6e3e-b03d1b4a1f59%2F5e8Bavzw33bFvGEs5PSnNDNSBmB7nBrz2Alfnq2Okfme6-1Gk6QOkdWNSA&title=UNIX%2BSHELL%2BSCRIPTING%253A%2BBEGINNER%2BTO%2BPRO%2521
(pipe and minishell in c) https://www.youtube.com/watch?v=nbtU83qcOw8
(tutorial to write a shell) https://brennan.io/2015/01/16/write-a-shell-in-c/
(bash commands) https://www.tutorialspoint.com/unix_commands/bash.htm
(explanation of functions) https://velog.io/@chez_bono/Minishell
(shell tutorial) https://www.linkedin.com/pulse/tutorial-code-simple-shell-c-ricardo-hincapi%C3%A9-trujillo/
(building a mini bash) https://m4nnb3ll.medium.com/minishell-building-a-mini-bash-a-42-project-b55a10598218
(shell code explained) https://www.youtube.com/playlist?list=PLbtzT1TYeoMhF4hcpEiCsOeN13zqrzBJq
(project explanation) https://github.com/iciamyplant/Minishell
(project explanation) https://github.com/madebypixel02/minishell
(project explanation) https://github.com/maiadegraaf/minishell
(writing your own shell) https://www.cs.purdue.edu/homes/grr/SystemsProgrammingBook/Book/Chapter5-WritingYourOwnShell.pdf
(shell syntax) https://pubs.opengroup.org/onlinepubs/009695399/utilities/xcu_chap02.html

Resurces read/seen
(flow chart) https://whimsical.com/minishell-architecture-big-picture-7b9N8PL3qHrddbs977mQ2J
(creating a shell) https://www.evernote.com/shard/s594/client/snv?isnewsnv=true&noteGuid=d209ab02-e7d4-caaf-7074-635bae7448ee&noteKey=SsUOMz7JffGp5fODLf0fWd9F4FDN-T2AvUc0eX3YxI8zx2PtsCghkqffmQ&sn=https%3A%2F%2Fwww.evernote.com%2Fshard%2Fs594%2Fsh%2Fd209ab02-e7d4-caaf-7074-635bae7448ee%2FSsUOMz7JffGp5fODLf0fWd9F4FDN-T2AvUc0eX3YxI8zx2PtsCghkqffmQ&title=CREATING%2BA%2BSIMPLE%2BSHELL
(process management) https://www.evernote.com/shard/s594/client/snv?isnewsnv=true&noteGuid=e6d2df45-e604-b2d2-084a-fa35a7a7a69f&noteKey=q9NOiJqlklzDUAu2MsGPUW4IuUpWa6fhNEowLdfHGo5dhHqz54F94V76Rw&sn=https%3A%2F%2Fwww.evernote.com%2Fshard%2Fs594%2Fsh%2Fe6d2df45-e604-b2d2-084a-fa35a7a7a69f%2Fq9NOiJqlklzDUAu2MsGPUW4IuUpWa6fhNEowLdfHGo5dhHqz54F94V76Rw&title=PROCESS%2BMANAGEMENT

*/

void ft_debug_print(t_data data)
{
	printf("\nCMDS:\n");
	for (int i = 0; data.cmds[i]; i++)
		printf("%s\n", data.cmds[i]);
	printf("\nREDIRECT:\n");
	for (int i = 0; data.redirect[i]; i++)
		printf("%s\n", data.redirect[i]);
	// printf("\nENV:\n");
	// for (int i = 0; data.env[i]; i++)
	// 	printf("%s\n", data.env[i]);
}

int ft_determine_in_fd(char *str)
{
	int i;
	int fd;

	i = -1;
	while (str[++i] != ':')
		;
	if (ft_isdigit(str[i + 1]))
		return (ft_atoi(str + i));
	fd = open(str + i + 1, O_RDONLY);
	if (fd == -1)
		return (-1);
	return (fd);
}

int ft_determine_out_fd(char *str)
{
	int i;
	int fd;

	i = -1;
	while (str[++i] != ':')
		;
	if (ft_isdigit(str[i + 1]))
		return (ft_atoi(str + i));
	if (str[i - 1] == 'A')
	{
		fd = open(str + i + 1, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd == -1)
			return (-1);
		return (fd);
	}
	fd = open(str + i + 1, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (-1);
	return (fd);
}

int ft_setup_struct(t_data *data, char **cmds, char **redirect)
{
	int i;

	data->cmds = malloc(sizeof(t_cmd));
	if (!data->cmds)
		return (1);
	i = -1;
	while (cmds[++i])
	{
		data->cmds->cmd = ft_strdup(cmds[i]);
		data->cmds->args = ft_strdup(ft_strnstr(cmds[i], " ", ft_strlen(cmds[i])));
		data->cmds->redirect = malloc(sizeof(t_redirect));
		if (!data->cmds->redirect)
			return (1);
		data->cmds->redirect->in_fd = ft_determine_in_fd(redirect[i]);
		data->cmds->redirect->out_fd = ft_determine_out_fd(redirect[i]);
		if (data->cmds->redirect->in_fd == -1 || data->cmds->redirect->out_fd == -1)
			return (1);
		data->cmds->next = malloc(sizeof(t_cmd));
		if (!data->cmds->next)
			return (1);
		data->cmds = data->cmds->next;
	}
	return (0);
}

int ft_parsing_loop(t_data *data)
{
	char *prompt;
	char **cmds;
	char **redirect;

	prompt = readline("minishell$ ");
	// prompt = ft_strdup("cat -e < infile.txt | ls -lah >> outfile.txt");
	cmds = ft_parsing(prompt);
	redirect = ft_redirections(cmds);
	cmds = ft_clean_cmds(cmds);
	if (ft_setup_struct(data, cmds, redirect))
		return (1);
	ft_clean_double_ptr(cmds);
	ft_clean_double_ptr(redirect);
	return (0);
}


int main(int ac, char **av, char **env)
{
	t_data data;
	char *prompt;
	
	(void)ac;
	(void)av;

	data.env = ft_parse_env(env);
	while (true)
	{
		if (ft_parsing_loop(&data))
			return (1);


		
		// ft_debug_print(data);


		free(prompt);
		break;
	}
	ft_clean_double_ptr(data.env);
	return (0);
}
