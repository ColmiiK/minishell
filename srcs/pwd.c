#include "minishell.h"
#include <limits.h>
#include <unistd.h>

//PATH_MAX comes from limits.h
//getcwd comes from unistd.h

void		ft_pwd(chart **redirect)
{
	char	pwd[PATH_MAX];

	if (getcwd(pwd, PATH_MAX))
	{
		ft_putendl_fd(pwd, redirect[0][0]);
	}
	else
		return;
}