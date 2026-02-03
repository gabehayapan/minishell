/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 10:17:51 by hanakamu          #+#    #+#             */
/*   Updated: 2026/01/31 10:19:27 by hanakamu         ###   ########.fr       */
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

int	replace_token_word(char **word, char *new_word)
{
	free(*word);
	*word = ft_strdup(new_word);
	if (*word == NULL)
		return (FAILURE);
	return (SUCCESS);
}

int	separate_tokens(t_token **curr_filter, char **strs, size_t len)
{
	int		is_last_slash;
	int		is_success;

	is_last_slash = 0;
	if ((((*curr_filter)->word)[len - 1] == '/') && len > 1
		&& ((*curr_filter)->word)[len - 2] != '/')
		is_last_slash = 1;
	if (*((*curr_filter)->word) == '/')
		is_success = add_head_slash(curr_filter, *strs);
	else
		is_success = replace_token_word(&(*curr_filter)->word, *strs);
	if (is_success == FAILURE)
		return (FAILURE);
	is_success = new_separated_tokens(curr_filter, strs + 1);
	if (is_success == FAILURE)
		return (FAILURE);
	if (is_last_slash == 1)
	{
		is_success = add_last_slash(curr_filter);
		if (is_success == FAILURE)
			return (FAILURE);
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
