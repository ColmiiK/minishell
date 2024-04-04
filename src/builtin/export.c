#include <minishell.h>


void			env_add(const char *value, t_env *env)
{
	t_env	*new;
	t_env	*tmp;

	if (env && env->var == NULL)
	{
		env->var = ft_strdup(value);
		return;
	}
	if (!(new = malloc(sizeof(t_env))))
		return;
	new->var = ft_strdup(value);
	while (env && env->next && env->next->next)
		env = env->next;
	tmp = env->next;
	env->next = new;
	new->next = tmp;
	return;
}

char		*get_env_name(char *dest, const char *src)
{
	int		i;

	i = 0;
	while (src[i] && src[i] != '=' && ft_strlen(src) < BUFF_SIZE)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

int			is_in_env(t_env *env, char *args)
{
	char	var_name[BUFF_SIZE];
	char	env_name[BUFF_SIZE];

	get_env_name(var_name, args);
	while (env && env->next)
	{
		get_env_name(env_name, env->var);
		if (ft_strcmp(var_name, env_name) == 0)
		{
			ft_memdel(env->var);
			env->var = ft_strdup(args);
			return (1);
		}
		env = env->next;
	}
	return (1);
}

int			ft_export(char **args, t_env *env, t_env *secret)
{
	int		new_env;
	int		error_ret;

	new_env = 0;
	if (!args[1])
	{
		print_sorted_env(secret);
		return (1);
	}
	else
	{
		error_ret = is_valid_env(args[1]);
		if (args[1][0] == '=')
			error_ret = -3;
		if (error_ret <= 0)
			return (print_error(error_ret, args[1]));
		new_env = error_ret == 2 ? 1 : is_in_env(env, args[1]);
		if (new_env == 0)
		{
			if (error_ret == 1)
				env_add(args[1], env);
			env_add(args[1], secret);
		}
	}
	return (1);
}