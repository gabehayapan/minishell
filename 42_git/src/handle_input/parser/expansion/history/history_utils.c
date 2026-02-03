/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 07:56:34 by hanakamu          #+#    #+#             */
/*   Updated: 2026/02/01 07:58:03 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_token	*last_token(t_token *token)
{
	t_token	*last;

	last = token;
	while (last != NULL && last->next != NULL)
		last = last->next;
	return (last);
}

void	insert_token(t_token *head, t_token *new)
{
	t_token	*next;
	t_token	*last_new;

	next = head->next;
	head->next = new;
	last_new = last_token(new);
	last_new->next = next;
	if (next != NULL)
		next->prev = last_new;
}
