/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_expansion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/31 17:50:11 by hanakamu          #+#    #+#             */
/*   Updated: 2026/01/31 17:52:17 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	expand_wildcard(t_token **tokens, t_token *filter)
{
	t_token	*token_dir;
	t_dir	dnames;
	int		is_success;

	is_success = init_wildcard(&filter, &token_dir, &dnames);
	if (is_success == FAILURE)
		return (FAILURE);
	is_success = check_initial_dir(tokens, filter, &token_dir, &dnames);
	if (is_success == FAILURE)
		return (FAILURE);
	else if (is_success == NOT_FOUND || is_success == NO_DIR)
		return (reset_wildcard_tokens(tokens, filter, token_dir,
				dnames.disname));
	is_success = check_deeper_dir(tokens, filter, &token_dir, dnames.disname);
	if (is_success == SUCCESS)
		clear_filter_token(tokens, filter);
	else if (is_success == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

int	wildcard_expansion(t_token **tokens)
{
	t_token	*current;
	int		is_success;

	current = *tokens;
	while (current != NULL)
	{
		is_success = expand_wildcard(tokens, current);
		if (is_success == FAILURE)
			return (FAILURE);
		current = current->next;
	}
	return (SUCCESS);
}
