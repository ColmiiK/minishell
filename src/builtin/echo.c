#include <minishell.h>

void		ft_echo(t_cmd *data, t_redirect *address)
{
	int		i;

	i = 1;
	while (data->args[i])
	{
		ft_putstr_fd(data->args[i], address->out_fd);
		i++;
	}
	return;
}