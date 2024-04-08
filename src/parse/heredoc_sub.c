/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_sub.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvega-g <alvega-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 10:54:14 by alvega-g          #+#    #+#             */
/*   Updated: 2024/04/08 11:10:39 by alvega-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	ft_hd_child(int fd[2])
{
	char	*temp;

	close(fd[0]);
	temp = readline("> ");
	if (!temp)
	{
		close(fd[1]);
		exit(EXIT_FAILURE);
	}
	write(fd[1], temp, ft_strlen(temp) + 1);
	close(fd[1]);
	free(temp);
	rl_clear_history();
	exit(EXIT_SUCCESS);
}

static char	*ft_hd_parent_success(int fd[2], int status)
{
	char	buffer[1024];

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

static char	*ft_hd_parent_kill(int fd[2], pid_t pid, struct termios termios)
{
	close(fd[0]);
	kill(pid, SIGKILL);
	tcsetattr(STDIN_FILENO, TCSANOW, &termios);
	write(STDOUT_FILENO, "\n", 1);
	return (ft_calloc(1, 1));
}

char	*ft_hd_process(struct termios termios)
{
	int		status;
	int		fd[2];
	pid_t	pid;

	status = 0;
	if (pipe(fd) == -1)
		return (NULL);
	pid = fork();
	if (pid == -1)
		return (NULL);
	if (pid == 0)
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

void	ft_hd_finish(char *temp, char *joined)
{
	int	fd;

	free(temp);
	fd = open(".here_doc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (joined[0] != '\0')
		write(fd, joined, (ft_strlen(joined) - 1) * sizeof(char));
	close(fd);
	free(joined);
}
