/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_lookup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 13:54:46 by hanakamu          #+#    #+#             */
/*   Updated: 2026/02/03 09:49:08 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_var.h"

t_env	*env_find(t_env *env_lst, const char *target)
{
	while (env_lst != NULL)
	{
		if (ft_strcmp(env_lst->key, target) == 0)
			return (env_lst);
		env_lst = env_lst->next;
	}
	return (NULL);
}

char	*env_key(t_env *env_lst, const char *target)
{
	while (env_lst != NULL)
	{
		if (ft_strcmp(env_lst->key, target) == 0)
			return (env_lst->key);
		env_lst = env_lst->next;
	}
	return (NULL);
}

char	*env_value(t_env *env_lst, const char *target)
{
	while (env_lst != NULL)
	{
		if (ft_strcmp(env_lst->key, target) == 0)
			return (env_lst->value);
		env_lst = env_lst->next;
	}
	return (NULL);
}
