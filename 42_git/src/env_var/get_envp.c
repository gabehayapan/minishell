/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_envp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 20:59:41 by hanakamu          #+#    #+#             */
/*   Updated: 2026/01/09 17:46:36 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	set_envp_info(t_env *env_lst, t_envp_len *envp_info)
{
	envp_info->len_key = ft_strlen(env_lst->key);
	envp_info->len_value = ft_strlen(env_lst->value);
	envp_info->size_len = envp_info->len_key + envp_info->len_value + 2;
}

void	fill_envp_str(char *envp, t_env *env_lst, t_envp_len envp_info)
{
	ft_strlcat(envp, env_lst->key, envp_info.len_key + 1);
	ft_strlcat(envp + envp_info.len_key, "=", 2);
	ft_strlcat(envp + envp_info.len_key + 1, env_lst->value,
		envp_info.len_value + 1);
}

char	**get_envp(t_env *env_lst)
{
	char		**envp;
	char		**ret;
	size_t		size;
	t_envp_len	envp_info;

	size = count_size_env_lst(env_lst);
	envp = (char **)ft_calloc(size + 1, sizeof(char));
	if (envp == NULL)
		return (NULL);
	ret = envp;
	while (env_lst != NULL)
	{
		set_envp_info(env_lst, &envp_info);
		*envp = (char *)malloc(sizeof(char) * (envp_info.size_len + 1));
		if (*envp == NULL)
		{
			free_strs(ret, envp - ret);
			return (NULL);
		}
		fill_envp_str(*envp, env_lst, envp_info);
		env_lst = env_lst->next;
		envp++;
	}
	*envp = NULL;
	return (ret);
}
