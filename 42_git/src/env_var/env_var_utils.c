/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 14:01:12 by hanakamu          #+#    #+#             */
/*   Updated: 2026/01/09 16:57:33 by hanakamu         ###   ########.fr       */
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

size_t	count_size_env_lst(t_env *env_lst)
{
	size_t	counter;

	counter = 0;
	while (env_lst != NULL)
	{
		counter = counter + 1;
		env_lst = env_lst->next;
	}
	return (counter);
}
