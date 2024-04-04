#include <minishell.h>

void	ft_env(t_env *env)
{
	while (env && env->next != NULL)
	{
		ft_putendl(env->var);
		env = env->next;
	}
	if (env)
		ft_putendl(env->var);
	return;
}