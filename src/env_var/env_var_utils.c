/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 14:01:12 by hanakamu          #+#    #+#             */
/*   Updated: 2026/01/28 09:30:54 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_var.h"

void	free_env_lst(t_env *env_lst)
{
	t_env	*current;
	t_env	*next;

	current = env_lst;
	while (current != NULL)
	{
		next = current->next;
		free(current->key);
		free(current->value);
		free(current);
		current = next;
	}
}

t_env	*get_last_env(t_env *env_lst)
{
	if (env_lst == NULL)
		return (NULL);
	while (env_lst->next != NULL)
		env_lst = env_lst->next;
	return (env_lst);
}

size_t	count_size_env_lst(t_env *env_lst)
{
	size_t	counter;

	counter = 0;
	while (env_lst != NULL)
	{
		if (env_lst->is_env == ENV_VAR)
			counter = counter + 1;
		env_lst = env_lst->next;
	}
	return (counter);
}
