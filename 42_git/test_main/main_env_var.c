/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_env_var.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 14:03:04 by hanakamu          #+#    #+#             */
/*   Updated: 2025/12/30 14:03:39 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_var.h"

#include <stdio.h>
int	main(int argc, char **argv, char **envp)
{
	t_env	*env_lst;
	t_env	*cp_env_lst;
//	char	**cp_envp;

	(void)argc;
	(void)argv;
//	cp_envp = envp;
//	printf("===env_vars===\n");
//	while (*cp_envp != NULL)
//	{
//		printf("%s\n", *cp_envp);
//		cp_envp++;
//	}
	env_lst = init_env_list(envp);
	cp_env_lst = env_lst;
	printf("===env_lst===\n");
	while (cp_env_lst != NULL)
	{
		printf("key:%s, value:%s\n", cp_env_lst->key, cp_env_lst->value);
		cp_env_lst = cp_env_lst->next;
	}
	free_env_lst(env_lst);
	return (0);
}
