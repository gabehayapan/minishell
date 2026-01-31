/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/31 19:50:38 by hanakamu          #+#    #+#             */
/*   Updated: 2026/02/01 08:26:32 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "env_var.h"
#include "ft_dprintf.h"
#include "builtin.h"

int	export_no_args(t_env *env_lst)
{
	while (env_lst != NULL)
	{
		if (env_lst->is_env == EXPORT_VAR)
			ft_printf("declare -x %s\n", env_lst->key);
		else
			ft_printf("declare -x %s=\"%s\"\n", env_lst->key, env_lst->value);
		env_lst = env_lst->next;
	}
	return (SUCCESS);
}

int	check_invalid_identifier(char *str)
{
	char	*cp_str;
	int		is_success;

	cp_str = str;
	is_success = SUCCESS;
	if (ft_isalpha(*str) == 0)
		is_success = FAILURE;
	else
	{
		while (*str != '\0' && *str != '=')
		{
			if (ft_isalnum(*str) == 0)
			{
				is_success = FAILURE;
				break ;
			}
			str++;
		}
	}
	if (is_success == FAILURE)
		ft_dprintf(2, "-minishell: export: '%s': not a valid identifier\n",
			cp_str);
	return (is_success);
}

int	update_env_value(t_env *target, char *new_env)
{
	free(target->value);
	target->value = get_env_value(new_env);
	if (target->value == NULL)
		return (FAILURE);
	return (SUCCESS);
}

int	store_new_env_var(t_env **env_lst, char *new_env)
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
	new_env_ptr->is_env = ENV_VAR;
	last_env = get_last_env(*env_lst);
	if (last_env == NULL)
		*env_lst = new_env_ptr;
	else
		last_env->next = new_env_ptr;
	return (SUCCESS);
}

int	export(char **strs, t_env **env_lst, t_to_free *to_free)
{
	t_env	*target;
	int		is_success;
	int		ret;

	strs = strs + 1;
	if (*strs == NULL)
		return (export_no_args(*env_lst));
	ret = SUCCESS;
	while (*strs != NULL)
	{
		is_success = check_invalid_identifier(*strs);
		if (ret == SUCCESS)
			ret = is_success;
		if (is_success == SUCCESS)
		{
			is_success = check_existence(&target, env_lst, *strs, to_free);
			if (target != NULL && is_success == SUCCESS)
				is_success = update_env_value(target, *strs);
			else if (is_success == SUCCESS)
				is_success = store_new_env_var(env_lst, *strs);
		}
		strs++;
	}
	return (ret);
}
