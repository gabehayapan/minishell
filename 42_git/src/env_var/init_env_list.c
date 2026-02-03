/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 13:57:47 by hanakamu          #+#    #+#             */
/*   Updated: 2026/02/03 09:24:07 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_var.h"

void	set_head_env_var(t_env *head, t_env *current)
{
	if (head != NULL && head->next == NULL)
		head->next = current;
}

void	set_last_env_var(t_env *last, t_env *current)
{
	if (last != NULL)
		last->next = current;
}

int	set_env_member(t_env *current, char *envp)
{
	int	is_success;

	is_success = new_env_var(current, envp);
	if (is_success == FAILURE)
		return (FAILURE);
	if (ft_strcmp(envp, "_") != 0)
		current->is_env = ENV_VAR;
	else
		current->is_env = SHELL_VAR;
	return (SUCCESS);
}

t_env	*init_env_list(char **envp)
{
	t_env	head;
	t_env	*current;
	t_env	*last;
	int			is_success;

	head.next = NULL;
	last = NULL;
	while (*envp != NULL)
	{
		current = (t_env *)malloc(sizeof(t_env));
		if (current == NULL)
			return (NULL);
		set_head_env_var(&head, current);
		is_success = set_env_member(current, *envp);
		if (is_success == FAILURE)
		{
			free_env_lst(head.next);
			return (NULL);
		}
		set_last_env_var(last, current);
		last = current;
		envp++;
	}
	return (head.next);
}
