/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 19:22:07 by hanakamu          #+#    #+#             */
/*   Updated: 2026/01/19 13:56:05 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <stdbool.h>

void	get_remaining_tokens(t_token **tokens)
{
	while (*tokens != NULL
		&& (*tokens)->tk_type != AND && (*tokens)->tk_type != OR
		&& (*tokens)->tk_type != SEMI && (*tokens)->tk_type != PIPE)
		clear_token(tokens, *tokens, free);
	if (*tokens != NULL && (*tokens)->tk_type == PIPE)
		clear_token(tokens, *tokens, free);
}

void	add_new_command(t_command **head, t_command *new_command,
			t_command **last)
{
	if (*head == NULL)
		*head = new_command;
	else
		(*last)->next = new_command;
	*last = new_command;
}

void	remove_tk_spaces(t_token **tokens)
{
	t_token	*current;

	current = *tokens;
	while (current != NULL)
	{
		if (current->tk_type == SPACES)
			clear_token(tokens, current, free);
		else if (current->next != NULL)
			(current->next)->is_join = true;
		current = current->next;
	}
}

int	join_command(t_token **tokens, t_token *current, char **command,
			t_token **next)
{
	t_token	*tmp;

	*next = current->next;
	*command = current->word;
	clear_token(tokens, current, NULL);
	while (*next != NULL && (*next)->is_join == true)
	{
		tmp = *next;
		*next = (*next)->next;
		*command = join_word_no_space(*command, tmp->word);
		if (*command == NULL)
			return (FAILURE);
		clear_token(tokens, tmp, free);
	}
	return (SUCCESS);
}
