/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wildcard.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 14:57:46 by hanakamu          #+#    #+#             */
/*   Updated: 2026/01/19 17:36:06 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <dirent.h>
#include <errno.h>

char	*get_target_dir(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
	{
		perror("getcwd");
		return (NULL);
	}
	return (cwd);
}

int	get_dir_ent(t_token *current, char *cwd)
{
	DIR				*dir;
	struct dirent	*ent;
	t_token			*next;

	dir = opendir(cwd);
	if (dir == NULL)
	{
		perror("opendir");
		return (SUCCESS);
	}
	errno = 0;
	ent = readdir(dir);
	if (ent == NULL)
		return (SUCCESS);
	while (ent != NULL && *(ent->d_name) == '.')
	{
		ent = readdir(dir);
		if (ent == NULL)
			return (SUCCESS);
	}
	free(current->word);
	current->word = ft_strdup(ent->d_name);
	if (current->word == NULL)
		return (FAILURE);
	ent = readdir(dir);
	if (ent == NULL)
		return (SUCCESS);
	next = current->next;
	while (ent != NULL && errno == 0)
	{
		if (*(ent->d_name) == '.')
		{
			ent = readdir(dir);
			if (ent == NULL && errno != 0)
				return (SUCCESS);
			continue ;
		}
		current = new_token_str(ent->d_name, current, WORD);
		if (current == NULL)
		{
			free_token(next);
			closedir(dir);
			return (FAILURE);
		}
		current->next = next;
		if (next != NULL)
			next->prev = current;
		ent = readdir(dir);
	}
	closedir(dir);
	return (SUCCESS);
}
