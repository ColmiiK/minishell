#include "minishell.h"

void		ft_env(char **env)
{
	int	i;

	i = 0;
	while (env)
	{
		ft_putendl(env[i]);
		i++;
	}
	if (env)
		ft_putendl(env->value);
}