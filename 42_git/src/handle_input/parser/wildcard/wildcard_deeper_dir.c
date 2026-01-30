/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_deeper_dir.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 10:49:08 by hanakamu          #+#    #+#             */
/*   Updated: 2026/01/30 13:34:23 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	get_matching_files_multidir(t_token **tokens, t_token **filter,
			t_token *head_filter, t_token **head_dir)
{
	t_token	*curr_dir;
	t_token	*next;
	t_dir	dnames;
	int		is_found;
	int		ret;

	curr_dir = *head_dir;
	next = curr_dir->next;
	if (set_dnames(curr_dir, &dnames) == FAILURE)
		return (FAILURE);
	is_found = 0;
	*filter = (*filter)->next;
	ret = check_dirent(tokens, *filter, &curr_dir, &dnames);
	free(dnames.dirname);
	if (ret == SUCCESS)
		is_found = 1;
	else if (ret == FAILURE)
		return (FAILURE);
	*head_dir = (*head_dir)->next;
	clear_token(tokens, curr_dir, NULL);
	curr_dir = next;
	while (curr_dir != NULL && curr_dir != head_filter)
	{
		next = curr_dir->next;
		if (set_dnames(curr_dir, &dnames) == FAILURE)
			return (FAILURE);
		ret = check_dirent(tokens, *filter, &curr_dir, &dnames);
		if (ret == SUCCESS && is_found == 0)
			is_found = 1;
		else if (ret == FAILURE)
			return (FAILURE);
		free(dnames.dirname);
		clear_token(tokens, curr_dir, NULL);
		curr_dir = next;
	}
	if (is_found == 0)
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
		return (SUCCESS);
	while (curr_filter != NULL && curr_filter->tk_type != SPACES)
	{
		is_success = get_matching_files_multidir(tokens, &curr_filter,
			head_filter, head_dir);
		if (is_success == FAILURE)
			return (FAILURE);
		else if (is_success == NOT_FOUND)
		{
			is_success = reset_wildcard_tokens(tokens, head_filter, *head_dir,
				disname);
			if (is_success == FAILURE)
				return (FAILURE);
			return (NOT_FOUND);
		}
		curr_filter = skip_one_filter_dir(curr_filter);
	}
	return (SUCCESS);
}
