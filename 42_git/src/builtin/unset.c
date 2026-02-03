/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/31 21:56:26 by hanakamu          #+#    #+#             */
/*   Updated: 2026/02/03 11:51:20 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_var.h"

static void	remove_env_var(t_env **env_lst, t_env *rm_env)
{
	t_env	*pre_rm_env;

	if (*env_lst == rm_env)
		*env_lst = rm_env->next;
	else
	{
		pre_rm_env = *env_lst;
		while (pre_rm_env->next != rm_env && pre_rm_env != NULL)
			pre_rm_env = pre_rm_env->next;
		pre_rm_env->next = rm_env->next;
	}
	free(rm_env->key);
	free(rm_env->value);
	free(rm_env);
}

int	unset(t_env **env_lst, char **strs)
{
	char	**rm_env_key;
	t_env	*rm_env;

	rm_env_key = strs + 1;
	while (*rm_env_key != NULL)
	{
		rm_env = env_find(*env_lst, *rm_env_key);
		if (rm_env != NULL)
			remove_env_var(env_lst, rm_env);
		rm_env_key++;
	}
	return (EXIT_SUCCESS);
}
