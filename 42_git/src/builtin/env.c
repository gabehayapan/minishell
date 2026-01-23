/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 20:19:24 by hanakamu          #+#    #+#             */
/*   Updated: 2026/01/23 18:44:24 by keitotak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_var.h"
#include "ftprintf.h"

int	env(t_env *env_lst)
{
	while (env_lst != NULL)
	{
		if (env_lst->is_env == true)
			ft_printf("%s=%s\n", env_lst->key, env_lst->value);
		env_lst = env_lst->next;
	}
	return (EXIT_SUCCESS);
}
