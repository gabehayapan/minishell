/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_separate_token_slash.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/31 10:15:52 by hanakamu          #+#    #+#             */
/*   Updated: 2026/01/31 10:18:39 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

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

int	new_separated_tokens(t_token **curr_filter, char **strs)
{
	t_token	*new_slash;
	t_token	*new_dir;
	t_token	*next;

	while (*strs != NULL)
	{
		next = (*curr_filter)->next;
		new_slash = new_slash_token(*curr_filter);
		if (new_slash == NULL)
			return (FAILURE);
		new_dir = new_token_str(*strs, new_slash, WORD);
		if (new_dir == NULL)
			return (FAILURE);
		new_dir->next = next;
		if (next != NULL)
			next->prev = new_dir;
		*curr_filter = new_dir;
		strs++;
	}
	return (SUCCESS);
}

int	add_head_slash(t_token **curr_filter, char *str)
{
	t_token	*new_dir;
	int		is_success;

	is_success = replace_token_word(&(*curr_filter)->word, "/");
	if (is_success == FAILURE)
		return (FAILURE);
	if (*str != '\0')
	{
		new_dir = new_dir_token(*curr_filter, str);
		if (new_dir == NULL)
			return (FAILURE);
		*curr_filter = new_dir;
	}
	return (SUCCESS);
}

int	add_last_slash(t_token **curr_filter)
{
	t_token	*new_slash;

	new_slash = new_slash_token(*curr_filter);
	if (new_slash == NULL)
		return (FAILURE);
	*curr_filter = new_slash;
	return (SUCCESS);
}
