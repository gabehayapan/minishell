/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 18:54:51 by hanakamu          #+#    #+#             */
/*   Updated: 2026/01/28 09:38:18 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "env_var.h"
#include "ft_dprintf.h"

int	new_env_no_value(char *str, t_env **env_lst)
{
	t_env	*new_env;
	t_env	*last;

	new_env = (t_env *)malloc(sizeof(t_env));
	if (new_env == NULL)
		return (FAILURE);
	new_env->key = str;
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

int	check_existence(t_env **target, t_env **env_lst, char *str, t_exec *top)
{
	char	**new_strs;

	new_strs = ft_split(str, '=');
	if (new_strs == NULL)
	{
		free_all(*env_lst, top);
		exit(1);
	}
	*target = env_find(*env_lst, *new_strs);
	if (*(new_strs + 1) == NULL)
	{
		if (*target != NULL)
			return (FAILURE);
		if (new_env_no_value(*new_strs, env_lst) == FAILURE)
		{
			free_all(*env_lst, top);
			exit(1);
		}
		free(new_strs);
		return (FAILURE);
	}
	free_null_term_strs(new_strs);
	return (SUCCESS);
}
