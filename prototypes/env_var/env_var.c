/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 10:48:00 by hanakamu          #+#    #+#             */
/*   Updated: 2026/01/07 10:49:19 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_var.h"

void	free_env_lst(t_env *env_lst)
{
	t_env	*current;
	t_env	*next;

	current = env_lst;
	while (current != NULL)
	{
		next = current->next;
		free(current->key);
		free(current->value);
		free(current);
		current = next;
	}
}

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

//t_env	*init_env_list(char **envp)
//{
//	size_t	size;
//	t_env	*env_lst;
//	t_env	*last_node;
//	int		is_success;
//
//	size = get_array_size(envp);
//	env_lst = (t_env *)malloc(sizeof(t_env) * size);
//	if (env_lst == NULL)
//		return (NULL);
//	last_node = env_lst;
//	while (*envp != NULL)
//	{
//		is_success = new_env_var(last_node, *envp);
//		if (is_success == FAILURE)
//		{
//			free(env_lst);
//			return (NULL);
//		}
//		last_node->next = last_node + 1;
//		last_node++;
//		envp++;
//	}
//	last_node = env_lst + size - 1;
//	last_node->next = NULL;
//	return (env_lst);
//}
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
