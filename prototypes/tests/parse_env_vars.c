/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env_vars.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 10:08:59 by hanakamu          #+#    #+#             */
/*   Updated: 2025/12/10 12:31:05 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/struct.h"

char	*convert_env_lst_to_str(t_env env_var)
{
	char	*env_str;
}

t_env	*parse_new_env_var(char *new_env)
{
	t_env	*new_env_var;
	char	**split_var;

	new_env_var = (t_env *)malloc(sizeof(t_env));
	if (new_env_var == NULL)
		return (NULL);
	split_var = ft_split(new_env, '=');
	if (split_var)
	{
		free(new_env_var);
		return (NULL);
	}
	new_env_var->key = split_var[0];
	new_env_var->value = split_var[1];
	free(split_var);
	return (new_env_var);
}

t_env	*init_env_vars(char **envp)
{
	t_env	*envs;
	int		size;

	size = 0;
	while (*envp != NULL)
	{
		size = size + 1;
		envp++;
	}
	envs = NULL;
}
