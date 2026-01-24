/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 10:27:23 by hanakamu          #+#    #+#             */
/*   Updated: 2026/01/24 11:38:03 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "env_var.h"
#include "parser.h"
#include "ft_dprintf.h"

size_t	count_num_args(char **strs)
{
	size_t	counter;

	counter = 0;
	while (*strs != NULL && counter < 3)
	{
		counter = counter + 1;
		strs++;
	}
	return (counter);
}

int	validate_args(char **strs)
{
	size_t	num_args;

	num_args = count_num_args(strs);
	if (num_args > 2)
	{
		ft_dprintf(2, "minishell: cd: too many arguments\n");
		return (FAILURE);
	}
	return (SUCCESS);
}

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
		*path = oldpwd->value;
	else
	{
		ft_dprintf(2, "minishell: cd: OLDPWD not set\n");
		return (FAILURE);
	}
	return (SUCCESS);
}

int	set_oldpwd(t_env *pwd, t_env *env_lst)
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

int	set_pwd(t_env *env_lst)
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

int	update_to_new_pwd(t_env *pwd, t_env *oldpwd, t_env *env_lst)
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

int	update_to_new_oldpwd(t_env *pwd, t_env *oldpwd, t_env *env_lst)
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

int	update_env_pwd(t_env *env_lst)
{
	t_env	*pwd;
	t_env	*oldpwd;
	int		is_success;

	pwd = env_find(env_lst, "PWD");
	oldpwd = env_find(env_lst, "OLDPWD");
	if (pwd == NULL)
		is_success = update_to_new_pwd(pwd, oldpwd, env_lst);
	else
		is_success = update_to_new_oldpwd();
	return (is_success);
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

int	cd(char **strs, t_env *env_lst)
{
	int		ret;
	char	*path;

	ret = validate_args(strs);
	if (ret == FAILURE)
		return (FAILURE);
	path = *(strs + 1);
	if (path == NULL)
	{
		ret = change_cwd_to_home(&path, env_lst);
		if (ret == FAILURE)
			return (FAILURE);
	}
	else if (ft_strcmp(path, "-") == 0)
	{
		ret = change_cwd_to_oldpwd(&path, env_lst);
		if (ret == FAILURE)
			return (FAILURE);
	}
	ret = change_cwd_to_path(path);
	if (ret == -1)
		return (FAILURE);
	update_env_pwd(env_lst);
	return (SUCCESS);
}
