/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_substitution.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/31 18:10:49 by hanakamu          #+#    #+#             */
/*   Updated: 2026/02/02 09:45:13 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	substitute_sgl_his(t_token **tokens, t_token **current, t_his *his)
{
	if (*current != NULL && ((*current)->next == NULL
			|| ((*current)->next != NULL
				&& ((*current)->next)->tk_type == SPACES)))
		return (skip_his(tokens, current));
	else if (*current != NULL && (*current)->next != NULL
		&& ft_isalpha(*((*current)->next)->word) == 0)
		return (his_no_event(*current));
	else
		return (replace_his_token(tokens, current, his));
}

int	substitute_dbl_his(t_token **tokens, t_token **current, t_his *his)
{
	t_token	*next;
	t_token	*token_set;

	if (his == NULL)
	{
		next = (*current)->next;
		clear_token(tokens, *current, free);
	}
	else
	{
		token_set = tokenizer(&his->line);
		if (token_set == NULL)
			return (FAILURE);
		next = (*current)->next;
		insert_token(*current, token_set);
		clear_token(tokens, *current, free);
	}
	*current = next;
	return (SUCCESS);
}

int	check_history(t_token **tokens, t_his *his)
{
	t_token	*current;
	int		is_success;

	current = *tokens;
	is_success = SUCCESS;
	while (current != NULL)
	{
		if (current != NULL && current->tk_type == SGL_HIS)
			is_success = substitute_sgl_his(tokens, &current, his);
		else if (current != NULL && current->tk_type == DBL_HIS)
			is_success = substitute_dbl_his(tokens, &current, his);
		else
			current = current->next;
		if (is_success == FAILURE || is_success == NO_EVENT)
			return (is_success);
	}
	return (SUCCESS);
}
