/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitotak <keitotak@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 19:32:04 by keitotak          #+#    #+#             */
/*   Updated: 2026/02/02 12:42:07 by keitotak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_var.h"
#include "ft_dprintf.h"
#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>

/*
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
*/

int	pwd(t_env **env_lst)
{
	t_env	*pwd;
	char	*cwd;

	pwd = env_find(*env_lst, "PWD");
	if (pwd != NULL)
		ft_dprintf(STDOUT_FILENO, "%s\n", pwd->value);
	else
	{
		cwd = getcwd(NULL, 0);
		if (cwd == NULL)
			return (EXIT_FAILURE);
		ft_dprintf(STDOUT_FILENO, "%s\n", cwd);
		free(cwd);
	}
	return (EXIT_SUCCESS);
}
