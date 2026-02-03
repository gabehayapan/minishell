/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_file_token.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 12:58:15 by hanakamu          #+#    #+#             */
/*   Updated: 2026/01/30 14:31:12 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_token	*new_file_token(t_token *last, char *name)
{
	t_token	*new_token;

	new_token = (t_token *)malloc(sizeof(t_token));
	if (new_token == NULL)
		return (NULL);
	new_token->tk_type = WILDCARD;
	new_token->word = name;
	new_token->is_join = false;
	new_token->prev = last;
	new_token->next = NULL;
	if (last != NULL)
		last->next = new_token;
	return (new_token);
}

t_token	*get_file_token(t_token *last, char *disname, char *name)
{
	char	*new_name;
	t_token	*new_token;
	t_token	*next;

	new_name = ft_strjoin(disname, name);
	if (new_name == NULL)
		return (NULL);
	next = NULL;
	if (last != NULL)
		next = last->next;
	new_token = new_file_token(last, new_name);
	if (new_token == NULL)
	{
		free(new_name);
		return (NULL);
	}
	new_token->next = next;
	if (next != NULL)
		next->prev = new_token;
	return (new_token);
}

t_token	*add_new_matched_file(t_token *last_dir, t_dir *dnames, char *name)
{
	t_token	*new_token;

	if (last_dir != NULL)
		new_token = get_file_token(last_dir, dnames->disname, name);
	else
		new_token = get_file_token(dnames->tk_last, dnames->disname, name);
	if (new_token == NULL)
		return (NULL);
	return (new_token);
}
