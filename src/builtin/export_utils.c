/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 18:54:51 by hanakamu          #+#    #+#             */
/*   Updated: 2026/02/04 10:35:21 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "env_var.h"
#include "ft_dprintf.h"

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

	cp_str = str;
	if (ft_isalpha(*str) == 0)
	{
		ft_dprintf(2, "-minishell: export: '%s': not a valid identifier\n",
			cp_str);
		return (FAILURE);
	}
	while (*str != '\0' && *str != '=')
	{
		if (ft_isalnum(*str) == 0)
		{
			ft_dprintf(2, "-minishell: export: '%s': not a valid identifier\n",
				cp_str);
			return (FAILURE);
		}
		str++;
	}
	return (SUCCESS);
}

int	set_env_key_and_value(t_env *env, char *key, char *value)
{
	env->key = ft_strdup(key);
	if (env->key == NULL)
		return (FAILURE);
	env->value = ft_strdup(value);
	if (env->value == NULL)
	{
		free(env->key);
		return (FAILURE);
	}
	return (SUCCESS);
}
