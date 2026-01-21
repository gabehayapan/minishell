/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_retrieve.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 11:01:34 by hanakamu          #+#    #+#             */
/*   Updated: 2026/01/21 13:39:46 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	filter_file(t_token *head, DIR *dir, char **name)
{
	struct dirent	*ent;
	int				ret;

	errno = 0;
	ent = readdir(dir);
	if (ent == NULL && errno != 0)
	{
		perror("readdir");
		return (FAILURE);
	}
	else if (ent == NULL)
		return (END);
	if (head->tk_type == WILDCARD && *(ent->d_name) == '.')
		return (NOT_FOUND);
	ret = check_file_name(head, ent);
	if (ret == NOT_FOUND)
		return (NOT_FOUND);
	*name = ft_strdup(ent->d_name);
	if (*name == NULL)
		return (FAILURE);
	return (SUCCESS);
}

t_token	*get_file_token(t_token *head, char *disname, char *name)
{
	char	*new_name;
	t_token	*new_token;

	new_name = ft_strjoin(disname, name);
	if (new_name == NULL)
		return (NULL);
	new_token = new_file_token(head, new_name);
	if (new_token == NULL)
	{
		free(new_name);
		return (NULL);
	}
	return (new_token);
}

int	get_first_file(t_token **tokens, t_token *head, char *disname, DIR *dir)
{
	char	*name;
	t_token	*new_token;
	int		ret;

	ret = filter_file(head, dir, &name);
	while (ret != END)
	{
		if (ret == SUCCESS)
		{
			new_token = get_file_token(head, disname, name);
			free(name);
			if (new_token == NULL)
				return (FAILURE);
			if (*tokens == head)
				*tokens = new_token;
			new_token->tk_type = WILDCARD;
			return (SUCCESS);
		}
		else if (ret == FAILURE)
			return (FAILURE);
		ret = filter_file(head, dir, &name);
	}
	return (NOT_FOUND);
}

int	get_remaining_files(t_token *head, char *disname, DIR *dir)
{
	char	*name;
	t_token	*new_token;
	int		ret;

	ret = filter_file(head, dir, &name);
	while (ret != END)
	{
		if (ret == SUCCESS)
		{
			new_token = get_file_token(head, disname, name);
			free(name);
			if (new_token == NULL)
				return (FAILURE);
		}
		else if (ret == FAILURE)
			return (FAILURE);
		ret = filter_file(head, dir, &name);
	}
	return (SUCCESS);
}

int	get_matching_files(t_token **tokens, t_token *head,
			char *dirname, char *disname)
{
	DIR		*dir;
	int		ret;

	dir = opendir(dirname);
	if (dir == NULL)
	{
		set_type_word(head);
		return (SUCCESS);
	}
	ret = get_first_file(tokens, head, disname, dir);
	if (ret != SUCCESS)
		return (handle_return_value(head, dir, ret));
	if (get_remaining_files(head, disname, dir) == FAILURE)
	{
		closedir(dir);
		return (FAILURE);
	}
	clear_filter_token(tokens, head);
	closedir(dir);
	return (SUCCESS);
}
