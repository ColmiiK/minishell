#include "minishell.h"
#include <stdlib.h>

char *get_env_path(char **env, const char *var, size_t len)
{
    char *pwd;
    int i = 0;
    int j = 0;
    int reslen = 0;

    while (env[i])
    {
        if (ft_strncmp(env[i], var, len) == 0)
        {
            reslen = ft_strlen(env[i]) - len;
            if (!(pwd = malloc(sizeof(char) * (reslen + 1))))
                return (NULL);
            j = 0;
            while (env[i][j + len])
            {
                pwd[j] = env[i][j + len];
                j++;
            }
            pwd[j] = '\0';
            return (pwd);
        }
        i++;
    }
    return (NULL);
}

int get_path_id(char **env)
{
    int res;
    char *env_path;

    env_path = NULL;

    env_path = get_env_path(env, "PWD", 3);
    if (!env_path)
    {
        ft_putendl_fd("error", 1);
        return (0);
    }
    res = chdir(env_path);
    free(env_path);
    return (res);
}

int ft_cd(char **args, char **env)
{
    int cd;

    if (!args[1])
        return (chdir(get_env_path(env, "HOME", 4)));
    if (ft_strcmp(args[1], "-") == 0)
        cd = get_path_id(env);
    else
        cd = chdir(args[1]);
    return (cd);
}