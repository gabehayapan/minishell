/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 08:44:14 by hanakamu          #+#    #+#             */
/*   Updated: 2026/02/10 09:11:13 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "builtin.h"

static int	get_pathset(t_env *env_lst, char ***pathset)
{
	char	*val_path;

	val_path = env_value(env_lst, "PATH");
	if (val_path == NULL)
	{
		*pathset = NULL;
		return (SUCCESS);
	}
	*pathset = ft_split(val_path, ':');
	if (*pathset == NULL)
		return (FAILURE);
	return (SUCCESS);
}

static char	*add_pathset(char *path, char *command)
{
	char	*new_path;
	char	*path_command;

	new_path = ft_strjoin(path, "/");
	if (new_path == NULL)
		return (NULL);
	path_command = ft_strjoin(new_path, command);
	free(new_path);
	return (path_command);
}

static int	search_path_command(char *cmd, char *pathset, char **pathname)
{
	char	*path_command;

	path_command = add_pathset(pathset, cmd);
	if (path_command == NULL)
		return (FAILURE);
	if (access(path_command, X_OK) == SUCCESS)
	{
		*pathname = path_command;
		return (SUCCESS);
	}
	free(path_command);
	return (NOT_FOUND);
}

char	*add_path_to_command(char **cmdset, t_env *env_lst, t_to_free *to_free)
{
	char	**pathset;
	char	**ptr_pathset;
	int		ret;
	char	*pathname;

	(void)to_free;
	ret = check_file_type(*cmdset);
	if (ret == IS_DIR || ret == EXECUTABLE)
		return (NULL);
	pathset = NULL;
	if (get_pathset(env_lst, &pathset) == FAILURE)
		return (NULL);
	ptr_pathset = pathset;
	while (pathset != NULL && *pathset != NULL)
	{
		ret = search_path_command(*cmdset, *pathset, &pathname);
		if (ret == FAILURE || ret == SUCCESS)
		{
			free_null_term_strs(ptr_pathset);
			return (pathname);
		}
		pathset++;
	}
	free_null_term_strs(ptr_pathset);
	return (check_execute_permission(*cmdset));
}
