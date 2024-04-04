#include <minishell.h>
#include <stdlib.h>

static char		*get_env_path(t_env *env, const char *var, size_t len)
{
	char	*oldpwd;
	int		i;
	int		j;
	int		s_alloc;

	while (env && env->next != NULL)
	{
		if (ft_strncmp(env->var, var, len) == 0)
		{
			s_alloc = ft_strlen(env->var) - len;
			if (!(oldpwd = malloc(sizeof(char) * s_alloc + 1)))
				return (NULL);
			i = 0;
			j = 0;
			while (env->var[i++])
			{
				if (i > (int)len)
					oldpwd[j++] = env->var[i];
			}
			oldpwd[j] = '\0';
			return (oldpwd);
		}
		env = env->next;
	}
	return (NULL);
}

static int		update_oldpwd(t_env *env)
{
	char	cwd[PATH_MAX];
	char	*oldpwd;

	if (getcwd(cwd, PATH_MAX) == NULL)
		return (0);
	if (!(oldpwd = ft_strjoin("OLDPWD=", cwd)))
		return (0);
	if (is_in_env(env, oldpwd) == 0)
		env_add(oldpwd, env);
	ft_memdel(oldpwd);
	return (1);
}

static int		go_to_path(int option, t_env *env)
{
	int		ret;
	char	*env_path;

	env_path = NULL;
	if (option == 0)
	{
		update_oldpwd(env);
		env_path = get_env_path(env, "HOME", 4);
		if (!env_path)
			return (0);
	}
	else if (option == 1)
	{
		env_path = get_env_path(env, "OLDPWD", 6);
		if (!env_path)
			return (0);
		update_oldpwd(env);
	}
	ret = chdir(env_path);
	ft_memdel(env_path);
	return (ret);
}

int				ft_cd(t_cmd *data, t_env *env, t_redirect *address)
{
	int		cd_ret;

	if (!data->args[1])
		return (go_to_path(address->in_fd, env));
	else
	{
		update_oldpwd(env);
		cd_ret = chdir(data->args[1]);
		if (cd_ret < 0)
			cd_ret *= -1;
	}
	return (cd_ret);
}