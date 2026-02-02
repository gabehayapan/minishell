/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_format_error.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 11:04:25 by hanakamu          #+#    #+#             */
/*   Updated: 2026/02/02 11:06:10 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	format_error(t_token *token)
{
	ft_dprintf(2, "-minishell: syntax error near unexpected token `%s'\n",
		token->word);
	return (FORMAT_ERROR);
}

int	check_format_error(t_token **tokens)
{
	t_token	*current;
	int		is_sep;

	if (is_separator(*tokens) == 1)
		return (format_error(*tokens));
	current = *tokens;
	is_sep = 0;
	while (current != NULL)
	{
		if (is_separator(current) == 1)
		{
			if (is_sep == 1)
				return (format_error(current));
			is_sep = 1;
		}
		else if (current->tk_type != SPACES)
			is_sep = 0;
		current = current->next;
	}
	return (SUCCESS);
}
