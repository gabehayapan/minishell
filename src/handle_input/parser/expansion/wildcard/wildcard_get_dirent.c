/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_get_dirent.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 13:11:23 by hanakamu          #+#    #+#             */
/*   Updated: 2026/02/05 14:57:20 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	get_dirent(struct dirent **ent, t_token *head, t_dir *dnames, char **name)
{
	errno = 0;
	*ent = readdir(dnames->dir);
	if (*ent == NULL && errno != 0)
	{
		perror("readdir");
		return (FAILURE);
	}
	else if (head == NULL)
	{
		*name = ft_strdup("");
		if (*name == NULL)
			return (FAILURE);
		return (NO_FILTER);
	}
	else if (*ent == NULL)
		return (END);
	return (SUCCESS);
}

int	filter_file(t_token *head, t_dir *dnames, char **name)
{
	struct dirent	*ent;
	int				ret;

	ret = get_dirent(&ent, head, dnames, name);
	if (ret != SUCCESS)
		return (ret);
	if (head->tk_type == WILDCARD && *(ent->d_name) == '.')
		return (NOT_FOUND);
	ret = check_file_name(head, ent);
	if (ret == FAILURE || ret == NOT_FOUND)
		return (ret);
	*name = ft_strdup(ent->d_name);
	if (*name == NULL)
		return (FAILURE);
	return (SUCCESS);
}

void	first_set_vars(t_token **tokens, t_token *head_filter,
			t_token *new_token, t_token **head_dir)
{
	if (*tokens == head_filter)
		*tokens = new_token;
	if (head_dir != NULL && *head_dir == NULL)
		*head_dir = new_token;
	new_token->next = head_filter;
	head_filter->prev = new_token;
}

int	get_matching_files(t_token **tokens, t_token *head_filter,
			t_token **head_dir, t_dir *dnames)
{
	char	*name;
	int		ret;

	ret = filter_file(head_filter, dnames, &name);
	if (ret == SUCCESS || ret == NO_FILTER)
	{
		if (*head_dir == NULL)
			dnames->tk_last = add_new_matched_file(head_filter->prev,
					dnames, name);
		else
			dnames->tk_last = add_new_matched_file(NULL, dnames, name);
		free(name);
		if (dnames->tk_last == NULL)
			return (FAILURE);
		if (*head_dir == NULL)
			first_set_vars(tokens, head_filter, dnames->tk_last, head_dir);
	}
	return (ret);
}

int	check_dirent(t_token **tokens, t_token *filter, t_token **token_dir,
			t_dir *dnames)
{
	int	ret;

	dnames->dir = opendir(dnames->dirname);
	if (dnames->dir == NULL)
		return (NO_DIR);
	ret = get_matching_files(tokens, filter, token_dir, dnames);
	while (ret != END)
	{
		if (ret == SUCCESS && dnames->is_found == 0)
			dnames->is_found = 1;
		else if (ret == NO_FILTER)
		{
			dnames->is_found = 1;
			break ;
		}
		else if (ret == FAILURE)
			break ;
		ret = get_matching_files(tokens, filter, token_dir, dnames);
	}
	closedir(dnames->dir);
	if (ret == FAILURE)
		return (FAILURE);
	else if (dnames->is_found == 0)
		return (NOT_FOUND);
	return (SUCCESS);
}
