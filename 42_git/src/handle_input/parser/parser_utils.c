/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 19:22:07 by hanakamu          #+#    #+#             */
/*   Updated: 2026/01/14 19:39:29 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

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
