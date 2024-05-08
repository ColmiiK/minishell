/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preset_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvega-g <alvega-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 19:06:56 by albagar4          #+#    #+#             */
/*   Updated: 2024/05/08 16:54:33 by alvega-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_env	*arr_to_list(char **env_cpy, int size)
{
	t_env	*list;
	t_env	*tmp;
	int		i;

	i = 0;
	list = create_node(env_cpy[i]);
	i++;
	tmp = list;
	while (i < size)
	{
		tmp = next_node(&list, create_node(env_cpy[i]));
		i++;
	}
	free_arr(env_cpy, size);
	return (list);
}

int	get_size_env(char **env_info)
{
	char	**env_ptr;
	int		str_nbr;

	env_ptr = env_info;
	str_nbr = 0;
	while (*env_ptr != NULL)
	{
		str_nbr++;
		env_ptr++;
	}
	return (str_nbr);
}

t_env	*ft_getenv(char **env_info)
{
	t_env		*link_list;
	char		**env_ptr;
	char		**copy_env;
	int			i;
	int			result;

	result = get_size_env(env_info);
	copy_env = malloc(sizeof(char *) * (result + 1));
	if (!copy_env)
		return (printf("error\n"), NULL);
	i = 0;
	env_ptr = env_info;
	while (*env_ptr != NULL)
	{
		copy_env[i] = ft_strdup(*env_ptr);
		env_ptr++;
		i++;
	}
	copy_env[i] = NULL;
	link_list = arr_to_list(copy_env, i);
	return (link_list);
}
