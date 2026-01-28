/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 09:57:15 by hanakamu          #+#    #+#             */
/*   Updated: 2026/01/28 11:27:11 by hanakamu         ###   ########.fr       */
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

void	remove_tk_spaces(t_token **tokens)
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

int	join_token_word(t_token **tokens)
{
	t_token	*current;
	t_token	*next;
	t_token	*tmp;

	current = *tokens;
	while (current != NULL)
	{
		next = current->next;
		while (next != NULL && (next->is_join == true && next->tk_type == WORD))
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

int	init_tokens(t_token **tokens, t_env **env_lst, unsigned char exit_status)
{
	int	is_success;

	is_success = check_assignment(tokens, env_lst);
	if (is_success == FAILURE)
		return (FAILURE);
	is_success = expand_specials(tokens, *env_lst, exit_status);
	if (is_success == FAILURE || is_success == SIGNALED)
		return (is_success);
	is_success = rm_space_and_join_tokens(tokens);
	if (is_success == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}
