/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 10:27:23 by hanakamu          #+#    #+#             */
/*   Updated: 2026/01/23 20:04:39 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "env_var.h"
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

int	update_pwd(t_env *env_lst)
{
	t_env	*oldpwd;
	t_env	*pwd;

	(void)env_lst;
	(void)oldpwd;
	(void)pwd;
	return (1);
}

int	cd(char **strs, t_env *env_lst)
{
	size_t	num_args;
	int		ret;
	char	*path;

	num_args = count_num_args(strs);
	if (num_args > 2)
	{
		ft_dprintf(2, "minishell: cd: too many arguments\n");
		return (EXIT_FAILURE);
	}
	path = *(strs + 1);
	if (path == NULL)
	{
		path = env_value(env_lst, "HOME");
		if (path == NULL)
		{
			ft_dprintf(2, "minishell: cd: HOME not set\n");
			return (EXIT_FAILURE);
		}
	}
	ret = chdir(path);
	if (ret == -1)
	{
		ft_dprintf(2, "minishell: cd: ");
		perror(*(strs + 1));
		return (EXIT_FAILURE);
	}
	update_pwd(env_lst);
	return (EXIT_SUCCESS);
}
