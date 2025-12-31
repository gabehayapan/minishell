/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/31 11:11:07 by hanakamu          #+#    #+#             */
/*   Updated: 2025/12/31 11:24:17 by hanakamu         ###   ########.fr       */
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

int	main(int argc, char **argv, char **envp)
{
	t_env	*env_lst;

	(void)argc;
	(void)argv;
	env_lst = init_env_list(envp);
	env(env_lst);
	free_env_lst(env_lst);
	return (0);
}
