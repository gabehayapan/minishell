/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 10:17:51 by hanakamu          #+#    #+#             */
/*   Updated: 2026/01/30 14:25:56 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_token	*get_head_dir_token(t_token *token)
{
	while (token->prev != NULL && (token->prev)->tk_type != SPACES)
		token = token->prev;
	return (token);
}

char	*is_slash(t_token *token_dir)
{
	char	*ret;

	if (token_dir == NULL)
		return (NULL);
	ret = ft_strrchr(token_dir->word, '/');
	return (ret);
}

void	clear_head_dir_token(t_token **head_dir)
{
	t_token	*next;

	next = (*head_dir)->next;
	clear_token(&(*head_dir)->prev, *head_dir, free);
	*head_dir = next;
}

char	*split_token_with_slash(t_token **head_dir, char *ptr_slash)
{
	char	*dirname;
	char	*stash;

	dirname = ft_substr((*head_dir)->word, 0,
			ptr_slash - (*head_dir)->word + 1);
	if (dirname == NULL)
		return (NULL);
	if (*(ptr_slash + 1) == '\0')
	{
		clear_head_dir_token(head_dir);
		return (dirname);
	}
	stash = ft_strdup(ptr_slash + 1);
	if (stash == NULL)
	{
		free(dirname);
		return (NULL);
	}
	free((*head_dir)->word);
	(*head_dir)->word = stash;
	return (dirname);
}

char	*get_open_dir_name(t_token **head_dir,
			char *ptr_slash, char **disname)
{
	char	*dirname;

	dirname = split_token_with_slash(head_dir, ptr_slash);
	if (dirname == NULL)
		return (NULL);
	*disname = ft_strdup(dirname);
	if (*disname == NULL)
	{
		free(dirname);
		return (NULL);
	}
	return (dirname);
}

char	*get_cwd_name(char **disname)
{
	char	*dirname;

	dirname = getcwd(NULL, 0);
	if (dirname == NULL)
		return (NULL);
	*disname = ft_strdup("");
	if (*disname == NULL)
	{
		free(dirname);
		return (NULL);
	}
	return (dirname);
}

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

t_token	*new_separated_tokens(t_token *curr_filter, char *str)
{
	t_token	*new_slash;
	t_token	*new_dir;
	t_token	*next;

	next = curr_filter->next;
	new_slash = new_token_str("/", curr_filter, WORD);
	if (new_slash == NULL)
	{
		free_token(next);
		return (NULL);
	}
	new_dir = new_token_str(str, new_slash, WORD);
	if (new_dir == NULL)
	{
		free_token(next);
		return (NULL);
	}
	new_slash->next = new_dir;
	new_dir->prev = new_slash;
	new_dir->next = next;
	if (next != NULL)
		next->prev = new_dir;
	return (new_dir);
}

int	separate_tokens(t_token *curr_filter, char **strs)
{
	free(curr_filter->word);
	curr_filter->word = ft_strdup(*strs);
	if (curr_filter->word == NULL)
		return (FAILURE);
	strs = strs + 1;
	while (*strs != NULL)
	{
		curr_filter = new_separated_tokens(curr_filter, *strs);
		strs++;
	}
	return (SUCCESS);
}

int	init_filter_tokens(t_token *filter)
{
	char	**strs;
	int		is_success;

	while (filter != NULL && filter->tk_type != SPACES)
	{
		strs = ft_split(filter->word, '/');
		if (strs == NULL)
			return (FAILURE);
		if (*(strs + 1) == NULL)
			free_null_term_strs(strs);
		else
		{
			is_success = separate_tokens(filter, strs);
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
	is_success = init_filter_tokens(*filter);
	if (is_success == FAILURE)
	{
		free(dnames->dirname);
		free(dnames->disname);
		return (FAILURE);
	}
	*token_dir = NULL;
	errno = 0;
	return (SUCCESS);
}
