/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wildcard.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 14:57:46 by hanakamu          #+#    #+#             */
/*   Updated: 2026/01/19 19:21:26 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <dirent.h>
#include <errno.h>

int	new_echo_token(t_token **tokens)
{
	t_token	*token_echo;

	token_echo = new_token_str("echo", NULL, WORD);
	if (token_echo == NULL)
		return (FAILURE);
	token_echo->next = *tokens;
	(*tokens)->prev = token_echo;
	*tokens = token_echo;
	return (SUCCESS);
}

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

int	get_first_file(t_token *current, DIR *dir)
{
	struct dirent	*ent;

	ent = readdir(dir);
	if (ent == NULL && errno != 0)
		return (FAILURE);
	while (ent != NULL && *(ent->d_name) == '.')
	{
		ent = readdir(dir);
		if (ent == NULL && errno != 0)
			return (FAILURE);
	}
	free(current->word);
	current->word = ft_strdup(ent->d_name);
	if (current->word == NULL)
		return (FAILURE);
	return (SUCCESS);
}

int	get_new_files(t_token **current, t_token *next,
			DIR *dir, struct dirent *ent)
{
	while (ent != NULL && errno == 0)
	{
		if (*(ent->d_name) != '.')
		{
			*current = new_token_str(ent->d_name, *current, WORD);
			if (*current == NULL)
				return (FAILURE);
		}
		ent = readdir(dir);
	}
	if (errno != 0)
	{
		perror("readdir");
		return (FAILURE);
	}
	(*current)->next = next;
	if (next != NULL)
		next->prev = *current;
	return (SUCCESS);
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
	next = current->next;
	if (get_first_file(current, dir) == FAILURE)
		return (FAILURE);
	ent = readdir(dir);
	if (ent == NULL)
		return (SUCCESS);
	if (get_new_files(&current, next, dir, ent) == FAILURE)
	{
		free_token(next);
		closedir(dir);
		return (FAILURE);
	}
	closedir(dir);
	return (SUCCESS);
}
