#include <minishell.h>
#include <limits.h>
#include <unistd.h>

//PATH_MAX comes from limits.h
//getcwd comes from unistd.h


void		ft_pwd(t_redirect address)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, PATH_MAX))
	{
		ft_putendl_fd(cwd, address);
		return;
	}
	return;
}