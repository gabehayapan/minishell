/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/31 19:50:38 by hanakamu          #+#    #+#             */
/*   Updated: 2026/02/04 10:48:10 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "env_var.h"
#include "ft_dprintf.h"
#include "builtin.h"

static int	new_env_no_value(char *str, t_env **env_lst)
{
	t_env	*new_env;
	t_env	*last;

	new_env = (t_env *)malloc(sizeof(t_env));
	if (new_env == NULL)
		return (FAILURE);
	new_env->key = ft_strdup(str);
	if (new_env->key == NULL)
	{
		free(new_env);
		return (FAILURE);
	}
	new_env->value = NULL;
	new_env->is_env = EXPORT_VAR;
	new_env->next = NULL;
	last = get_last_env(*env_lst);
	if (last == NULL)
		*env_lst = new_env;
	else
		last->next = new_env;
	return (SUCCESS);
}

static int	update_env_value(t_env *target, char *new_env)
{
	free(target->value);
	target->value = ft_strdup(new_env);
	if (target->value == NULL)
		return (FAILURE);
	return (SUCCESS);
}

static int	store_new_env_var(t_env **env_lst, char *env_key, char *env_value)
{
	t_env	*new_env_ptr;
	t_env	*last_env;

	new_env_ptr = (t_env *)malloc(sizeof(t_env));
	if (new_env_ptr == NULL)
		return (FAILURE);
	if (set_env_key_and_value(new_env_ptr, env_key, env_value) == FAILURE)
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

static void	export_env_var(t_env **env_lst, char *str, t_to_free *to_free)
{
	char	*equal_ptr;
	t_env	*target;
	int		is_success;

	equal_ptr = ft_strnstr(str, "=", ft_strlen(str));
	if (equal_ptr != NULL)
		*equal_ptr = '\0';
	target = env_find(*env_lst, str);
	if (equal_ptr == NULL && target != NULL)
		return ;
	else if (equal_ptr == NULL && target == NULL)
		is_success = new_env_no_value(str, env_lst);
	else if (equal_ptr != NULL && target != NULL)
		is_success = update_env_value(target, equal_ptr + 1);
	else
		is_success = store_new_env_var(env_lst, str, equal_ptr + 1);
	if (is_success == FAILURE)
	{
		free_all(*env_lst, to_free);
		exit(EXIT_FAILURE);
	}
}

int	export(char **strs, t_env **env_lst, t_to_free *to_free)
{
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
			export_env_var(env_lst, *strs, to_free);
		strs++;
	}
	return (ret);
}
