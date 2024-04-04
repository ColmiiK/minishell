#include "minishell.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] && s2[i] && i < n)
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	if (!s1[i] && ft_strlen(s1) && i == n)
		return (0);
	if (i == n && s1[i - 1] == s2[i - 1])
		return (0);
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int call_buildins(t_data data)
{
    if(!ft_strncmp(data->cmds[0], "env", 3))
        ft_env(data->env);
	if(!ft_strncmp(data->cmds[0], "echo", 3))
        ft_echo(data->cmds);
	if(!ft_strncmp(data->cmds[0], "pwd", 3))
        ft_pwd(data->cmds);
	if(!ft_strncmp(data->cmds[0], "cd", 2))
        ft_cd(data->cmds, data->env);
}

