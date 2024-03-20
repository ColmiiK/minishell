#include "minishell.h"

static	int		nb_args(char **args)
{
	int		size;

	size = 0;
	while (args[size])
		size++;
	return (size);
}

void    ft_echo(char **args)
{
	int		i;

	i = 1;
	if (nb_args(args) > 1)
	{
		while (args[i])
		{
			ft_putstr_fd(args[i], 1);
			i++;
		}
	}
}