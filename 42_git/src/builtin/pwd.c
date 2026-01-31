/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitotak <keitotak@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 19:32:04 by keitotak          #+#    #+#             */
/*   Updated: 2026/02/01 08:13:59 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_var.h"
#include "ft_dprintf.h"
#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>

int	lstat(const char *pathname, struct stat *statbuf);

int	is_symbolic_link(const char *pathname)
{
	struct stat	sb;

	if (lstat(pathname, &sb) < 0)
	{
		perror("lstat");
		return (0);
	}
	if (S_ISLNK(sb.st_mode))
		return (1);
	return (0);
}

int	pwd(t_env **env_lst)
{
	t_env	*pwd;
	char	*cwd;

	pwd = env_find(*env_lst, "PWD");
	if (pwd != NULL)
	{
		if (is_symbolic_link(pwd->value))
			ft_dprintf(STDOUT_FILENO, "symbolic link.\n");
		ft_dprintf(STDOUT_FILENO, "%s\n", pwd->value);
	}
	else
	{
		cwd = getcwd(NULL, 0);
		if (cwd == NULL)
			return (EXIT_FAILURE);
		if (is_symbolic_link(cwd))
			ft_dprintf(STDOUT_FILENO, "symbolic link.\n");
		ft_dprintf(STDOUT_FILENO, "%s\n", cwd);
		free(cwd);
	}
	return (EXIT_SUCCESS);
}
