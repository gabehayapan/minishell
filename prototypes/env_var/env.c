/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/31 11:11:07 by hanakamu          #+#    #+#             */
/*   Updated: 2025/12/31 11:13:48 by hanakamu         ###   ########.fr       */
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
