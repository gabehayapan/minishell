/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/31 21:56:26 by hanakamu          #+#    #+#             */
/*   Updated: 2026/01/05 15:47:56 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../env_var.h"

t_env	*get_env_var_ptr(t_env *env_lst, char *rm_env_key)
{
	while (env_lst != NULL)
	{
		if (ft_strcmp(env_lst->key, rm_env_key) == 0)
			return (env_lst);
		env_lst = env_lst->next;
	}
	return (NULL);
}

void	remove_env_var(t_env **env_lst, t_env *rm_env)
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

void	unset(t_env **env_lst, char *rm_env_key)
{
	t_env	*rm_env;

	rm_env = get_env_var_ptr(*env_lst, rm_env_key);
	if (rm_env == NULL)
		return ;
	remove_env_var(env_lst, rm_env);
}
