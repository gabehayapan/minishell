/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitotak <keitotak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 23:11:26 by keitotak          #+#    #+#             */
/*   Updated: 2025/12/06 16:46:29 by keitotak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

#define PATH "PATH="

static char	**get_paths_from_envp(char **ev)
{
	char	**paths;

	while (*ev != NULL)
	{
		if (ft_strncmp(PATH, *ev, ft_strlen(PATH)) == 0)
		{
			paths = ft_split(*ev + ft_strlen(PATH), ':');
			return (paths);
		}
		ev++;
	}
	return (NULL);
}

static char	*create_pathname(char *onepath, char *name)
{
	char	*path;
	char	*pathname;

	path = ft_strjoin(onepath, "/");
	if (path == NULL)
		return (NULL);
	pathname = ft_strjoin(path, name);
	free(path);
	return (pathname);
}

char	*free_arrs_ret_s(char **arrs, char *s)
{
	char	**tmp;

	tmp = arrs;
	while (*arrs)
		free(*arrs++);
	free(tmp);
	return (s);
}

static char	*get_pathname(char *name, char **ev)
{
	char	*pathname;
	char	**pathset;
	char	**to_free;

	if (access(name, X_OK) == success)
		return (name);
	pathset = get_paths_from_envp(ev);
	if (pathset == NULL)
		return (NULL);
	to_free = pathset;
	while (*pathset != NULL)
	{
		pathname = create_pathname(*pathset, name);
		if (pathname == NULL)
			return (free_arrs_ret_s(to_free, NULL));
		if (access(pathname, X_OK) == success)
			return (free_arrs_ret_s(to_free, pathname));
		free(pathname);
		pathset++;
	}
	return (free_arrs_ret_s(to_free, name));
}

int	exec_command(char *cmd, char **ev)
{
	char	**cmdset;
	char	*pathname;

	cmdset = ft_split(cmd, ' ');
	if (cmdset == NULL)
		return (EXIT_FAILURE);
	if (**cmdset == '\0')
		return (handle_noexist_cmd(cmdset));
	pathname = get_pathname(cmdset[0], ev);
	if (pathname == NULL)
	{
		perror(cmdset[0]);
		free_arrs_ret_s(cmdset, NULL);
		return (EXIT_FAILURE);
	}
	if (execve(pathname, cmdset, ev) == -1)
	{
		if (errno == ENOENT)
			return (handle_noexist_cmd(cmdset));
		perror(cmdset[0]);
		free_arrs_ret_s(cmdset, NULL);
		return (EXIT_FAILURE);
	}
	return (EXIT_FAILURE);
}
