/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 10:17:51 by hanakamu          #+#    #+#             */
/*   Updated: 2026/01/30 19:26:08 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char	*init_dnames(t_token **current, char **disname)
{
	char	*dirname;
	t_token	*head_dir;
	char	*ptr_slash;

	head_dir = get_head_dir_token(*current);
	ptr_slash = is_slash(head_dir);
	if (ptr_slash != NULL)
		dirname = get_open_dir_name(&head_dir, ptr_slash, disname);
	else
		dirname = get_cwd_name(disname);
	if (dirname == NULL)
		return (NULL);
	*current = head_dir;
	return (dirname);
}

t_token	*new_slash_token(t_token *curr_filter)
{
	t_token	*new_slash;
	t_token	*next;

	next = curr_filter->next;
	new_slash = new_token_str("/", curr_filter, WORD);
	if (new_slash == NULL)
		return (NULL);
	new_slash->next = next;
	if (next != NULL)
		next->prev = new_slash;
	return (new_slash);
}

t_token	*new_dir_token(t_token *curr_filter, char *str)
{
	t_token	*new_dir;
	t_token	*next;

	next = curr_filter->next;
	new_dir = new_token_str(str, curr_filter, WORD);
	if (new_dir == NULL)
		return (NULL);
	new_dir->next = next;
	if (next != NULL)
		next->prev = new_dir;
	return (new_dir);
}

t_token	*new_separated_tokens(t_token *curr_filter, char *str)
{
	t_token	*new_slash;
	t_token	*new_dir;
	t_token	*next;

	next = curr_filter->next;
	new_slash = new_token_str("/", curr_filter, WORD);
	if (new_slash == NULL)
		return (NULL);
	new_dir = new_token_str(str, new_slash, WORD);
	if (new_dir == NULL)
		return (NULL);
	new_slash->next = new_dir;
	new_dir->prev = new_slash;
	new_dir->next = next;
	if (next != NULL)
		next->prev = new_dir;
	return (new_dir);
}

int	separate_tokens(t_token **curr_filter, char **strs, size_t len)
{
	t_token	*new_dir;
	t_token	*fil;

	(void)len;
	if (*((*curr_filter)->word) == '/')
	{
		free((*curr_filter)->word);
		(*curr_filter)->word = ft_strdup("/");
		if ((*curr_filter)->word == NULL)
			return (FAILURE);
		new_dir = new_dir_token(*curr_filter, *strs);
		if (new_dir == NULL)
			return (FAILURE);
	}
	else
	{
		free((*curr_filter)->word);
		(*curr_filter)->word = ft_strdup(*strs);
		if ((*curr_filter)->word == NULL)
			return (FAILURE);
	}
	strs = strs + 1;
	fil = *curr_filter;
	while (*strs != NULL)
	{
		*curr_filter = new_separated_tokens(*curr_filter, *strs);
		strs++;
	}
	return (SUCCESS);
}

int	init_filter_tokens(t_token *filter)
{
	char	**strs;
	size_t	len;
	int		is_success;

	while (filter != NULL && filter->tk_type != SPACES)
	{
		len = ft_strlen(filter->word);
		strs = ft_split(filter->word, '/');
		if (strs == NULL)
			return (FAILURE);
		if (*(strs + 1) == NULL
			&& *(filter->word) != '/' && (filter->word)[len - 1] != '/')
			free_null_term_strs(strs);
		else
		{
			is_success = separate_tokens(&filter, strs, len);
			free_null_term_strs(strs);
			if (is_success == FAILURE)
				return (FAILURE);
		}
		filter = filter->next;
	}
	return (SUCCESS);
}

int	init_wildcard(t_token **filter, t_token **token_dir,
			t_dir *dnames)
{
	int	is_success;

	dnames->dir = NULL;
	dnames->dirname = init_dnames(filter, &dnames->disname);
	if (dnames->dirname == NULL)
		return (FAILURE);
	dnames->tk_last = NULL;
	dnames->is_found = 0;
	is_success = init_filter_tokens(*filter);
	if (is_success == FAILURE)
	{
		free(dnames->dirname);
		free(dnames->disname);
		return (FAILURE);
	}
	*token_dir = NULL;
	return (SUCCESS);
}
