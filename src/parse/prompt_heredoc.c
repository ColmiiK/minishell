/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvega-g <alvega-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 15:17:50 by alvega-g          #+#    #+#             */
/*   Updated: 2024/04/05 17:04:05 by alvega-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int ft_hd_child(int fd[2])
{
	char *temp;

	close(fd[0]);
	temp = readline("> ");
	if (temp == NULL)
		exit(EXIT_FAILURE);
	write(fd[1], temp, ft_strlen(temp) + 1);
	close(fd[1]);
	free(temp);
	rl_clear_history();
	exit(EXIT_SUCCESS);
}

static char *ft_hd_parent_success(int fd[2], int status)
{
	char buffer[1024];

	if (WEXITSTATUS(status) == 1)
	{
		close(fd[0]);
		return (NULL);
	}
	if (WEXITSTATUS(status) == 0)
	{
		read(fd[0], buffer, sizeof(buffer));
		close(fd[0]);
		return (ft_strdup(buffer));
	}
	else
		return (NULL);
}

static char *ft_hd_parent_kill(int fd[2], pid_t pid, struct termios termios)
{
	close(fd[0]);
	kill(pid, SIGKILL);
	tcsetattr(STDIN_FILENO, TCSANOW, &termios);
	write(STDOUT_FILENO, "\n", 1);
	return (ft_calloc(1, 1));
}

static char *ft_here_doc_child(struct termios termios)
{
	int status;
	int fd[2];
	pid_t pid;


	status = 0;
	if (pipe(fd) == -1)
		return (NULL);
	pid = fork();
	if (pid == -1)
		return (NULL);	
	if(pid == 0)
		ft_hd_child(fd);
	else
	{
		close(fd[1]);
		while (true)
		{
			if (g_signal == SIGINT)
				return (ft_hd_parent_kill(fd, pid, termios));
			if (waitpid(pid, &status, WNOHANG) > 0)
				return (ft_hd_parent_success(fd, status));
		}
	}
	return (ft_calloc (1, 1));
}

static void ft_hd_finish(char *temp, char *joined)
{
	int fd;

	free(temp);
	fd = open(".here_doc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (joined[0] != '\0')
		write(fd, joined, (ft_strlen(joined) - 1) * sizeof(char));
	close(fd);
	free(joined);
}

static void	ft_here_doc_loop(char *prompt, t_data *data)
{
	char	*temp;
	char	*joined;
	char	*delimiter;

	delimiter = ft_strtok(prompt, " ");
	temp = ft_here_doc_child(data->termios);
	if (g_signal == SIGINT)
		return ;
	if (!temp)
		temp = ft_strdup(delimiter);
	joined = ft_calloc(1, 1);
	if (!joined)
		return ;
	while (ft_strncmp(temp, delimiter, ft_strlen(delimiter)))
	{
		joined = ft_strjoin_ex(ft_strjoin_ex(joined, temp, 3), "\n", 1);
		temp = ft_here_doc_child(data->termios);
		if (g_signal == SIGINT)
			return ;
		if (!temp)
			temp = ft_strdup(delimiter);
	}
	ft_hd_finish(temp, joined);
}

static char	*ft_here_doc_pipe(char *sub, char *str, t_data *data)
{
	char	*input;
	char	*trimmed;

	input = ft_here_doc_child(data->termios);
	if (!input)
	{
		printf("minishell: syntax error: unexpected end of file\n");
		return (ft_calloc(1, 1));
	}
	trimmed = ft_strtrim(sub, "| ");
	trimmed = ft_strjoin_ex(trimmed, " < .here_doc | ", 1);
	str = ft_strjoin_ex(trimmed, input, 3);
	return (str);
}

static char	*ft_fix_prompt(char *prompt)
{
	char	*fixed;
	char	*temp;
	int		i;

	if (!ft_strncmp(prompt, "<<", 2))
		return (ft_strdup(prompt));
	i = 0;
	while (prompt[i] != '<')
		i++;
	fixed = (char *)malloc(i * sizeof(char));
	if (!fixed)
		return (0);
	ft_strlcpy(fixed, prompt, i);
	fixed = ft_strjoin_ex(" ", fixed, 2);
	while (prompt[i] != '<')
		i++;
	fixed = ft_strjoin_ex(prompt, fixed, 2);
	temp = ft_strdup(fixed + i);
	free(fixed);
	return (temp);
}

char	*ft_here_doc(char *prompt, bool pipe, t_data *data)
{
	char	*str;
	char	*before;
	char	*sub;

	str = NULL;
	prompt = ft_fix_prompt(prompt);
	before = ft_strdup(prompt);
	ft_here_doc_loop(ft_strnstr(prompt, "<<", ft_strlen(prompt)) + 3, data);
	sub = ft_strnstr(before, ft_strtok(NULL, " "), ft_strlen(before));
	if (pipe)
		str = ft_here_doc_pipe(sub, str, data);
	else
		str = ft_strjoin(sub, " < .here_doc");
	free(before);
	free(prompt);
	if (g_signal == SIGINT)
		return (ft_calloc(1, 1));
	return (str);
}
