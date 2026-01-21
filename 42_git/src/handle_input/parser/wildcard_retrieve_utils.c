/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_retrieve_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 10:20:30 by hanakamu          #+#    #+#             */
/*   Updated: 2026/01/21 10:27:25 by hanakamu         ###   ########.fr       */
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

void	clear_filter_token(t_token **tokens, t_token *head)
{
	t_token	*next;

	while (head != NULL && head->tk_type != SPACES)
	{
		next = head->next;
		clear_token(tokens, head, free);
		head = next;
	}
}

t_token	*get_token_dir(t_token *head)
{
	if (head->prev == NULL)
		return (NULL);
	else if ((head->prev)->tk_type != WORD)
		return (NULL);
	else
		return (head->prev);
}
