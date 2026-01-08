/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 13:57:47 by hanakamu          #+#    #+#             */
/*   Updated: 2026/01/08 18:58:11 by hanakamu         ###   ########.fr       */
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
	t_env	head;
	t_env	*current;
	t_env	*prev;
	int		is_success;

	head.next = NULL;
	prev = NULL;
	while (*envp != NULL)
	{
		current = (t_env *)malloc(sizeof(t_env));
		if (current == NULL)
			return (NULL);
		if (head.next == NULL)
			head.next = current;
		is_success = new_env_var(current, *envp);
		if (is_success == FAILURE)
		{
			free_env_lst(head.next);
			return (NULL);
		}
		if (prev != NULL)
			prev->next = current;
		prev = current;
		envp++;
	}
	return (head.next);
}
