/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_tokens_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 17:46:09 by hanakamu          #+#    #+#             */
/*   Updated: 2026/02/02 11:04:50 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	is_separator(t_token *token)
{
	if (token != NULL
		&& (token->tk_type == AND || token->tk_type == OR
			|| token->tk_type == SEMI || token->tk_type == PIPE))
		return (1);
	return (0);
}

static void	remove_tk_spaces(t_token **tokens)
{
	t_token	*current;
	t_token	*next;
	int		is_wildcard;

	is_wildcard = 0;
	current = *tokens;
	while (current != NULL)
	{
		next = current->next;
		if (current->tk_type == SPACES)
		{
			clear_token(tokens, current, free);
			is_wildcard = 0;
		}
		else if (current->tk_type == WILDCARD)
			is_wildcard = 1;
		else if (current->next != NULL
			&& (current->next)->tk_type != WILDCARD && is_wildcard == 0
			&& is_separator(current) == 0
			&& is_separator(current->next) == 0)
			(current->next)->is_join = true;
		current = next;
	}
}

static int	join_token_word(t_token **tokens)
{
	t_token	*current;
	t_token	*next;
	t_token	*tmp;

	current = *tokens;
	while (current != NULL)
	{
		next = current->next;
		while (next != NULL && (current->tk_type == WORD
				&& next->is_join == true && next->tk_type == WORD))
		{
			tmp = next->next;
			current->word = join_word_no_space(current->word, next->word);
			if (current->word == NULL)
				return (FAILURE);
			clear_token(tokens, next, free);
			next = tmp;
		}
		current = next;
	}
	return (SUCCESS);
}

int	rm_space_and_join_tokens(t_token **tokens)
{
	int	is_success;

	remove_tk_spaces(tokens);
	is_success = join_token_word(tokens);
	return (is_success);
}
