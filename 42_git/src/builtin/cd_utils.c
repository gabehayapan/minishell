/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 11:49:28 by hanakamu          #+#    #+#             */
/*   Updated: 2026/01/26 09:56:48 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "env_var.h"
#include "parser.h"
#include "ft_dprintf.h"

int	validate_args(char **strs)
{
	size_t	num_args;

	num_args = 0;
	while (*strs != NULL && num_args < 3)
	{
		num_args = num_args + 1;
		strs++;
	}
	if (num_args > 2)
	{
		ft_dprintf(2, "minishell: cd: too many arguments\n");
		return (FAILURE);
	}
	return (SUCCESS);
}

int	set_oldpwd(t_env *pwd, t_env **env_lst)
{
	char	*new_oldpwd;
	int		is_success;

	if (pwd == NULL)
		return (SUCCESS);
	new_oldpwd = ft_strjoin("OLDPWD=", pwd->value);
	if (new_oldpwd == NULL)
		return (FAILURE);
	is_success = add_shell_var(new_oldpwd, env_lst);
	free(new_oldpwd);
	return (is_success);
}

int	set_pwd(t_env **env_lst)
{
	char	*cwd;
	char	*new_pwd;
	int		is_success;

	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
		return (FAILURE);
	new_pwd = ft_strjoin("PWD=", cwd);
	if (new_pwd == NULL)
	{
		free(cwd);
		return (FAILURE);
	}
	is_success = add_shell_var(new_pwd, env_lst);
	free(new_pwd);
	return (is_success);
}

int	update_to_new_pwd(t_env *oldpwd, t_env **env_lst)
{
	if (oldpwd != NULL)
	{
		free(oldpwd->value);
		oldpwd->value = ft_strdup("");
		if (oldpwd->value == NULL)
			return (FAILURE);
		if (set_pwd(env_lst) == FAILURE)
			return (FAILURE);
	}
	else
	{
		if (set_pwd(env_lst) == FAILURE)
			return (FAILURE);
	}
	return (SUCCESS);
}

int	update_to_new_oldpwd(t_env *pwd, t_env *oldpwd, t_env **env_lst)
{
	if (oldpwd != NULL)
	{
		free(oldpwd->value);
		oldpwd->value = pwd->value;
		pwd->value = getcwd(NULL, 0);
		if (pwd->value == NULL)
			return (FAILURE);
	}
	else
	{
		if (set_oldpwd(pwd, env_lst) == FAILURE)
			return (FAILURE);
		free(pwd->value);
		pwd->value = getcwd(NULL, 0);
		if (pwd->value == NULL)
			return (FAILURE);
	}
	return (SUCCESS);
}
