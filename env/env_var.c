/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 10:48:00 by hanakamu          #+#    #+#             */
/*   Updated: 2025/12/31 11:16:35 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_var.h"

void	free_env_lst(t_env *env_lst)
{
	t_env	*tmp;

	tmp = env_lst;
	while (tmp != NULL)
	{
		free(tmp->key);
		free(tmp->value);
		tmp = tmp->next;
	}
	free(env_lst);
}

char	*get_env_key(char **env)
{
	char	*start;
	char	*env_key;

	start = *env;
	while (**env != '=' && **env != '\0')
		(*env)++;
	env_key = ft_substr(start, 0, *env - start);
	if (env_key == NULL)
		return (NULL);
	return (env_key);
}

char	*get_env_value(char *env)
{
	char	*env_value;

	env_value = ft_strdup(env);
	if (env_value == NULL)
		return (NULL);
	return (env_value);
}

int	new_env_var(t_env *tmp, char *env)
{
	tmp->key = get_env_key(&env);
	if (tmp->key == NULL)
		return (FAILURE);
	tmp->value = get_env_value(env + 1);
	if (tmp->value == NULL)
	{
		free(tmp->key);
		return (FAILURE);
	}
	tmp->next = NULL;
	return (SUCCESS);
}

//#include <stdio.h>
//int	main(int argc, char **argv, char **envp)
//{
//	t_env	*env_lst;
//	t_env	*cp_env_lst;
////	char	**cp_envp;
//
//	(void)argc;
//	(void)argv;
////	cp_envp = envp;
////	printf("===env_vars===\n");
////	while (*cp_envp != NULL)
////	{
////		printf("%s\n", *cp_envp);
////		cp_envp++;
////	}
//	env_lst = init_env_list(envp);
//	cp_env_lst = env_lst;
//	printf("===env_lst===\n");
//	while (cp_env_lst != NULL)
//	{
//		printf("key:%s, value:%s\n", cp_env_lst->key, cp_env_lst->value);
//		cp_env_lst = cp_env_lst->next;
//	}
//	free_env_lst(env_lst);
//	return (0);
//}
