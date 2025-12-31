/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/31 19:50:38 by hanakamu          #+#    #+#             */
/*   Updated: 2025/12/31 19:58:22 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_var.h"

t_env	*get_last_env(t_env *env_lst)
{
	if (env_lst == NULL)
		return (NULL);
	while (env_lst->next != NULL)
		env_lst = env_lst->next;
	return (env_lst);
}

int	export(t_env *env_lst, char *new_env_var)
{
	t_env	*new_env_ptr;
	t_env	*last_env;
	int		is_success;

	new_env_ptr = (t_env *)malloc(sizeof(t_env));
	if (new_env == NULL)
		return (FAILURE);
	is_success = new_env_var(new_env_ptr, new_env_var);
	if (is_success == FAILURE)
	{
		free(new_env_ptr);
		return (FAILURE);
	}
	last_env = get_last_env(env_lst);
	last_env->next = new_env_ptr;
	return (SUCCESS);
}
