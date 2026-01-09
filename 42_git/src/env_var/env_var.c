/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 10:48:00 by hanakamu          #+#    #+#             */
/*   Updated: 2026/01/09 18:33:34 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_var.h"
#include "ftprintf.h"

char	*get_env_key(char **env)
{
	char	*start;
	char	*env_key;

	start = *env;
	while (**env != '=' && **env != '\0')
		(*env)++;
	if (**env == '\0')
		return (NULL);
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

int	new_env_var(t_env *current, char *env)
{
	current->key = get_env_key(&env);
	if (current->key == NULL)
		return (FAILURE);
	current->value = get_env_value(env + 1);
	if (current->value == NULL)
	{
		free(current->key);
		return (FAILURE);
	}
	current->next = NULL;
	return (SUCCESS);
}
