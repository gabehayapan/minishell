/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 10:27:23 by hanakamu          #+#    #+#             */
/*   Updated: 2026/01/23 19:09:46 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "env_var.h"
#include "ft_dprintf.h"

int	cd(char **strs, t_env *env_lst)
{
	int		ret;
	char	*path;

	path = *(strs + 1);
	if (path == NULL)
	{
		path = env_value(env_lst, "HOME");
		if (path == NULL)
		{
			ft_dprintf(2, "minishell: cd: HOME not set");
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
	return (EXIT_SUCCESS);
}
