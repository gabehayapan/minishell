/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 20:19:24 by hanakamu          #+#    #+#             */
/*   Updated: 2026/01/15 20:20:14 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_var.h"

void	env(t_env *env_lst)
{
	while (env_lst != NULL)
	{
		ft_printf("%s=%s\n", env_lst->key, env_lst->value);
		env_lst = env_lst->next;
	}
}
