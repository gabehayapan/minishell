/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_to_envp.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 20:59:41 by hanakamu          #+#    #+#             */
/*   Updated: 2026/01/28 09:36:03 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	set_envp_info(t_env *env_lst, t_envp_len *envp_info)
{
	envp_info->len_key = ft_strlen(env_lst->key);
	envp_info->len_value = ft_strlen(env_lst->value);
	envp_info->size_len = envp_info->len_key + envp_info->len_value + 1;
}

void	fill_envp_str(char *envp, t_env *env_lst, t_envp_len envp_info)
{
	ft_strlcat(envp, env_lst->key, envp_info.len_key + 1);
	ft_strlcat(envp + envp_info.len_key, "=", 2);
	ft_strlcat(envp + envp_info.len_key + 1, env_lst->value,
		envp_info.len_value + 1);
}

int	set_env_ptr(t_env *env_lst, char **envp, char **head)
{
	t_envp_len	envp_info;

	set_envp_info(env_lst, &envp_info);
	*envp = (char *)ft_calloc(envp_info.size_len + 1, sizeof(char));
	if (*envp == NULL)
	{
		free_strs(head, envp - head);
		return (FAILURE);
	}
	fill_envp_str(*envp, env_lst, envp_info);
	return (SUCCESS);
}

char	**convert_to_envp(t_env *env_lst)
{
	char		**envp;
	char		**ret;
	size_t		size;
	int			is_success;

	size = count_size_env_lst(env_lst);
	envp = (char **)malloc(sizeof(char *) * (size + 1));
	if (envp == NULL)
		return (NULL);
	ret = envp;
	while (env_lst != NULL)
	{
		if (env_lst->is_env != ENV_VAR)
		{
			env_lst = env_lst->next;
			continue ;
		}
		is_success = set_env_ptr(env_lst, envp, ret);
		if (is_success == FAILURE)
			return (NULL);
		env_lst = env_lst->next;
		envp++;
	}
	*envp = NULL;
	return (ret);
}
