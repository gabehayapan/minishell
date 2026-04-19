/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_path_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 12:42:47 by hanakamu          #+#    #+#             */
/*   Updated: 2026/02/05 16:11:37 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <sys/stat.h>

#define DIRECTORY		0
#define REGULAR_FILE	1
#define NO_FILE_DIR		2

static int	file_type(char *name)
{
	struct stat	sb;
	int			is_success;

	is_success = stat(name, &sb);
	if (is_success == -1)
		return (NO_FILE_DIR);
	else if (S_ISDIR(sb.st_mode))
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
		return (IS_DIR);
	}
	else if (access(cmd, X_OK) == SUCCESS)
		return (EXECUTABLE);
	return (SUCCESS);
}

int	check_execute_permission(char *cmd)
{
	int	ret;

	ret = file_type(cmd);
	if (ret == NO_FILE_DIR)
	{
		ft_dprintf(2, "-minishell: %s: No such file or directory\n", cmd);
		return (NO_COMMAND);
	}
	else if (ret == DIRECTORY)
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
