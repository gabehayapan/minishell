/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */ /*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 10:27:23 by hanakamu          #+#    #+#             */
/*   Updated: 2026/01/24 11:57:46 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "env_var.h"
#include "parser.h"
#include "ft_dprintf.h"
#include "builtin.h"

int	change_cwd_to_home(char **path, t_env *env_lst)
{
	*path = env_value(env_lst, "HOME");
	if (*path == NULL)
	{
		ft_dprintf(2, "minishell: cd: HOME not set\n");
		return (FAILURE);
	}
	return (SUCCESS);
}

int	change_cwd_to_oldpwd(char **path, t_env *env_lst)
{
	t_env	*oldpwd;

	oldpwd = env_find(env_lst, "OLDPWD");
	if (oldpwd != NULL && *(oldpwd->value) != '\0')
	{
		*path = oldpwd->value;
		ft_printf("%s\n", *path);
	}
	else
	{
		ft_dprintf(2, "minishell: cd: OLDPWD not set\n");
		return (FAILURE);
	}
	return (SUCCESS);
}

int	change_cwd_to_path(char *path)
{
	int	ret;

	ret = chdir(path);
	if (ret == -1)
	{
		perror("chdir");
		return (FAILURE);
	}
	return (SUCCESS);
}

void	update_env_pwd(t_env **env_lst, t_exec *top)
{
	t_env	*pwd;
	t_env	*oldpwd;
	int		is_success;

	pwd = env_find(*env_lst, "PWD");
	oldpwd = env_find(*env_lst, "OLDPWD");
	if (pwd == NULL)
		is_success = update_to_new_pwd(oldpwd, env_lst);
	else
		is_success = update_to_new_oldpwd(pwd, oldpwd, env_lst);
	if (is_success == FAILURE)
	{
		free_env_lst(*env_lst);
		free_node_exec(top);
		exit(1);
	}
}

int	cd(char **strs, t_env **env_lst, t_exec *top)
{
	int		ret;
	char	*path;

	ret = validate_args(strs);
	if (ret == FAILURE)
		return (FAILURE);
	path = *(strs + 1);
	if (path == NULL)
	{
		ret = change_cwd_to_home(&path, *env_lst);
		if (ret == FAILURE)
			return (FAILURE);
	}
	else if (ft_strcmp(path, "-") == 0)
	{
		ret = change_cwd_to_oldpwd(&path, *env_lst);
		if (ret == FAILURE)
			return (FAILURE);
	}
	ret = change_cwd_to_path(path);
	if (ret == -1)
		return (FAILURE);
	update_env_pwd(env_lst, top);
	return (SUCCESS);
}
