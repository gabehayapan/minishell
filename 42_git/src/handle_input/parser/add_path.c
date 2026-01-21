/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 08:44:14 by hanakamu          #+#    #+#             */
/*   Updated: 2026/01/21 13:26:40 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "builtin.h"

t_builtin	is_builtin(char *cmd)
{
	if (ft_strcmp("echo", cmd) == 0)
		return (ECHO);
	if (ft_strcmp("cd", cmd) == 0)
		return (CD);
	if (ft_strcmp("pwd", cmd) == 0)
		return (PWD);
	if (ft_strcmp("export", cmd) == 0)
		return (EXPORT);
	if (ft_strcmp("unset", cmd) == 0)
		return (UNSET);
	if (ft_strcmp("env", cmd) == 0)
		return (ENV);
	if (ft_strcmp("exit", cmd) == 0)
		return (EXIT);
	else
		return (ELSE);
}

int	get_pathset(t_env *env_lst, char ***pathset)
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

char	*add_pathset(char *path, char *command)
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

int	search_path_command(t_token *tokens, char *pathset)
{
	char	*path_command;

	path_command = add_pathset(pathset, tokens->word);
	if (path_command == NULL)
		return (FAILURE);
	if (access(path_command, X_OK) == SUCCESS)
	{
		free(tokens->word);
		tokens->word = path_command;
		return (SUCCESS);
	}
	free(path_command);
	return (NOT_FOUND);
}

int	add_path_to_command(t_token *tokens, t_env *env_lst)
{
	char	**pathset;
	char	**ptr_pathset;
	int		status;

	if (tokens == NULL || is_builtin(tokens->word) != ELSE
		|| access(tokens->word, X_OK) == SUCCESS)
		return (SUCCESS);
	pathset = NULL;
	if (get_pathset(env_lst, &pathset) == FAILURE)
		return (FAILURE);
	ptr_pathset = pathset;
	while (pathset != NULL && *pathset != NULL)
	{
		status = search_path_command(tokens, *pathset);
		if (status == FAILURE || status == SUCCESS)
		{
			free_null_term_strs(ptr_pathset);
			return (status);
		}
		pathset++;
	}
	free_null_term_strs(ptr_pathset);
	return (SUCCESS);
}
