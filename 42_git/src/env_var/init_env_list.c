/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 13:57:47 by hanakamu          #+#    #+#             */
/*   Updated: 2026/01/23 19:23:16 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_var.h"

t_env	*init_env_list(char **envp)
{
	t_init_env	init_vars;
	int			is_success;

	(init_vars.head).next = NULL;
	init_vars.last = NULL;
	while (*envp != NULL && *(envp + 1) != NULL)
	{
		init_vars.current = (t_env *)malloc(sizeof(t_env));
		if (init_vars.current == NULL)
			return (NULL);
		if ((init_vars.head).next == NULL)
			(init_vars.head).next = init_vars.current;
		is_success = new_env_var(init_vars.current, *envp);
		if (is_success == FAILURE)
		{
			free_env_lst((init_vars.head).next);
			return (NULL);
		}
		if (ft_strcmp(*envp, "_") != 0)
			(init_vars.current)->is_env = true;
		if (init_vars.last != NULL)
			(init_vars.last)->next = init_vars.current;
		init_vars.last = init_vars.current;
		envp++;
	}
	return ((init_vars.head).next);
}
