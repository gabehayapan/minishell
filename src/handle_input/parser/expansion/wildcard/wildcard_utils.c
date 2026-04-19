/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 13:08:22 by hanakamu          #+#    #+#             */
/*   Updated: 2026/02/05 15:17:08 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	set_type_word(t_token *current)
{
	while (current != NULL && current->tk_type != SPACES)
	{
		if (current->tk_type == WILDCARD)
			current->tk_type = WORD;
		current = current->next;
	}
}

int	reset_wildcard_tokens(t_token **tokens, t_token *filter,
			t_token *token_dir, char *disname)
{
	t_token	*new_token;
	t_token	*next;

	set_type_word(filter);
	while (token_dir != NULL && token_dir != filter)
	{
		next = token_dir->next;
		clear_token(tokens, token_dir, free);
		token_dir = next;
	}
	if (disname != NULL && *disname == '\0')
	{
		free(disname);
		return (SUCCESS);
	}
	new_token = get_file_token(filter->prev, disname, "");
	free(disname);
	if (new_token == NULL)
		return (FAILURE);
	new_token->tk_type = WORD;
	if (*tokens == filter)
		*tokens = new_token;
	return (SUCCESS);
}

void	clear_filter_token(t_token **tokens, t_token *filter)
{
	t_token	*next;

	while (filter != NULL && filter->tk_type != SPACES)
	{
		next = filter->next;
		clear_token(tokens, filter, free);
		filter = next;
	}
}

t_token	*skip_one_filter_dir(t_token *filter)
{
	while (filter != NULL && filter->tk_type != SPACES && *filter->word != '/')
		filter = filter->next;
	if (filter == NULL || filter->tk_type == SPACES)
		return (NULL);
	return (filter);
}

int	set_dnames(t_token *dir, t_dir *dnames)
{
	dnames->dirname = dir->word;
	dnames->dirname = join_word_no_space(dnames->dirname, "/");
	if (dnames->dirname == NULL)
		return (FAILURE);
	dnames->disname = dnames->dirname;
	dnames->dir = NULL;
	dnames->tk_last = dir;
	return (SUCCESS);
}
