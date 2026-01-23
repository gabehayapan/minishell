/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/31 19:50:38 by hanakamu          #+#    #+#             */
/*   Updated: 2026/01/23 15:28:04 by hanakamu         ###   ########.fr       */
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

int	update_env_value(t_env *target, char *new_env)
{
	free(target->value);
	target->value = get_env_value(new_env);
	if (target->value == NULL)
		return (FAILURE);
	return (SUCCESS);
}

int	store_new_env_var(t_env *env_lst, char *new_env)
{
	t_env	*new_env_ptr;
	t_env	*last_env;
	int		is_success;

	new_env_ptr = (t_env *)malloc(sizeof(t_env));
	if (new_env_ptr == NULL)
		return (FAILURE);
	is_success = new_env_var(new_env_ptr, new_env);
	if (is_success == FAILURE)
	{
		free(new_env_ptr);
		return (FAILURE);
	}
	last_env = get_last_env(env_lst);
	if (last_env == NULL)
		env_lst = new_env_ptr;
	else
		last_env->next = new_env_ptr;
	return (SUCCESS);
}

int	export(char **argv, t_env *env_lst)
{
	t_env	*target;
	int		is_success;

	arv = argv + 1;
	while (*argv != NULL)
	{
		target = env_find(env_lst, *new_env);
		if (target != NULL)
			is_success = update_env_value(target, *new_env);
		else
			is_success = store_new_env_var(env_lst, *new_env);
		argv++;
	}
	return (is_success);
}
