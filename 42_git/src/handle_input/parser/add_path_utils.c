/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_path_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 12:42:47 by hanakamu          #+#    #+#             */
/*   Updated: 2026/02/04 12:44:01 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <sys/stat.h>

#define DIRECTORY		0
#define REGULAR_FILE	1

static int	file_type(char *name)
{
	struct stat	sb;

	stat(name, &sb);
	if ((sb.st_mode & S_IFMT) == S_IFDIR)
		return (DIRECTORY);
	else
		return (REGULAR_FILE);
}

int	check_file_type(char *cmd)
{
	char		*ptr_slash;

	ptr_slash = ft_strchr(cmd, '/');
	if (ptr_slash == NULL)
		return (SUCCESS);
	if (file_type(cmd) == DIRECTORY)
	{
		ft_dprintf(2, "-minishell: %s: Is a directory\n", cmd);
		return (NO_COMMAND);
	}
	return (SUCCESS);
}

int	check_execute_permission(char *cmd)
{
	if (file_type(cmd) == DIRECTORY)
	{
		ft_dprintf(2, "-minishell: %s: command not found\n", cmd);
	}
	else
	{
		if (access(cmd, X_OK) == SUCCESS)
			return (SUCCESS);
		else
			ft_dprintf(2, "-minishell: %s: command not found\n", cmd);
	}
	return (NO_COMMAND);
}
