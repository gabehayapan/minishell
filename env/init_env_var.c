/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env_var.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/31 11:15:22 by hanakamu          #+#    #+#             */
/*   Updated: 2025/12/31 11:16:13 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_var.h"

size_t	get_array_size(char **strs)
{
	size_t	count;

	count = 0;
	while (*strs != NULL)
	{
		count = count + 1;
		strs++;
	}
	return (count);
}

t_env	*init_env_list(char **envp)
{
	size_t	size;
	t_env	*env_lst;
	t_env	*last_node;
	int		is_success;

	size = get_array_size(envp);
	env_lst = (t_env *)malloc(sizeof(t_env) * size);
	if (env_lst == NULL)
		return (NULL);
	last_node = env_lst;
	while (*envp != NULL)
	{
		is_success = new_env_var(last_node, *envp);
		if (is_success == FAILURE)
		{
			free(env_lst);
			return (NULL);
		}
		last_node->next = last_node + 1;
		last_node++;
		envp++;
	}
	last_node = env_lst + size - 1;
	last_node->next = NULL;
	return (env_lst);
}
