/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/31 19:50:38 by hanakamu          #+#    #+#             */
/*   Updated: 2026/01/23 18:46:39 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_var.h"
#include "ft_dprintf.h"

void	export_no_args(t_env *env_lst)
{
	while (env_lst != NULL)
	{
		ft_printf("declare -x %s=%s\n", env_lst->key, env_lst->value);
		env_lst++;
	}
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
	new_env_ptr->is_env = true;
	last_env = get_last_env(env_lst);
	if (last_env == NULL)
		env_lst = new_env_ptr;
	else
		last_env->next = new_env_ptr;
	return (SUCCESS);
}

int	export(char **strs, t_env *env_lst)
{
	t_env	*target;
	int		is_success;

	strs = strs + 1;
	if (*strs == NULL)
		export_no_args(env_lst);
	while (*strs != NULL)
	{
		if (ft_isalpha(**strs) == 0)
			ft_dprintf(2,
				"minishell: export: '%s': not a valid identifier", *strs);
		else
		{
			target = env_find(env_lst, *strs);
			if (target != NULL)
				is_success = update_env_value(target, *strs);
			else
				is_success = store_new_env_var(env_lst, *strs);
		}
		strs++;
	}
	return (is_success);
}
