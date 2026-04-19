/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_deeper_dir.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 10:49:08 by hanakamu          #+#    #+#             */
/*   Updated: 2026/02/05 14:52:48 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	check_first_dirent(t_token **tokens, t_token **filter, t_token **head_dir,
			t_dir *dnames)
{
	t_token	*next;
	int		ret;

	*filter = (*filter)->next;
	dnames->is_found = 0;
	ret = check_dirent(tokens, *filter, head_dir, dnames);
	free(dnames->dirname);
	next = (*head_dir)->next;
	clear_token(tokens, *head_dir, NULL);
	if (ret == SUCCESS)
		dnames->is_found = 1;
	else if (ret == FAILURE)
		return (FAILURE);
	*head_dir = next;
	return (ret);
}

int	check_remaining_dirent(t_token **tokens, t_token *filter,
			t_token *curr_dir, t_dir *dnames)
{
	int	ret;
	int	prev_found;

	if (set_dnames(curr_dir, dnames) == FAILURE)
		return (FAILURE);
	prev_found = dnames->is_found;
	ret = check_dirent(tokens, filter, &curr_dir, dnames);
	free(dnames->dirname);
	if (ret == FAILURE)
		return (FAILURE);
	else if (prev_found == 0 && ret == SUCCESS)
		return (NEW_MATCH);
	return (ret);
}

int	get_matching_files_multidir(t_token **tokens, t_token **filter,
			t_token *head_filter, t_token **head_dir)
{
	t_token	*curr_dir;
	t_token	*next;
	t_dir	dnames;
	int		ret;

	next = (*head_dir)->next;
	if (set_dnames(*head_dir, &dnames) == FAILURE)
		return (FAILURE);
	ret = check_first_dirent(tokens, filter, head_dir, &dnames);
	if (ret == FAILURE)
		return (FAILURE);
	curr_dir = next;
	while (curr_dir != NULL && curr_dir != head_filter)
	{
		next = curr_dir->next;
		ret = check_remaining_dirent(tokens, *filter, curr_dir, &dnames);
		if (ret == FAILURE)
			return (FAILURE);
		set_head_dir(head_dir, curr_dir, &dnames, ret);
		clear_token(tokens, curr_dir, NULL);
		curr_dir = next;
	}
	if (dnames.is_found == 0)
		return (NOT_FOUND);
	return (SUCCESS);
}

int	check_deeper_dir(t_token **tokens, t_token *head_filter, t_token **head_dir,
			char *disname)
{
	t_token	*curr_filter;
	int		is_success;

	curr_filter = skip_one_filter_dir(head_filter);
	if (curr_filter == NULL)
	{
		free(disname);
		return (SUCCESS);
	}
	while (curr_filter != NULL && curr_filter->tk_type != SPACES)
	{
		is_success = get_matching_files_multidir(tokens, &curr_filter,
				head_filter, head_dir);
		if (is_success == FAILURE)
		{
			free(disname);
			return (FAILURE);
		}
		else if (is_success == NOT_FOUND)
			return (handle_not_found(tokens, head_filter, disname));
		curr_filter = skip_one_filter_dir(curr_filter);
	}
	free(disname);
	return (SUCCESS);
}
