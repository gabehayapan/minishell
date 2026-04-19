/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 13:34:52 by hanakamu          #+#    #+#             */
/*   Updated: 2026/01/29 07:49:13 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	print_syntax_error_paren(t_token *token)
{
	if (token->tk_type == O_PAREN)
	{
		if (token->next != NULL)
			ft_dprintf(2, "-minishell: syntax error near unexpected token "
				"`%s'\n", (token->next)->word);
		else
			ft_dprintf(2, "-minishell: syntax error near `('\n");
	}
	else
		ft_dprintf(2, "-minishell: syntax error near `)'\n");
}

int	check_opening_parenthesis(t_token **tokens, int *subshell)
{
	t_token	*current;

	while (*tokens != NULL && (*tokens)->tk_type == O_PAREN)
	{
		*subshell = *subshell + 1;
		clear_token (tokens, *tokens, free);
	}
	current = *tokens;
	while (current != NULL && current->tk_type != AND && current->tk_type != OR
		&& current->tk_type != SEMI && current->tk_type != PIPE)
	{
		if (current->tk_type == O_PAREN
			|| (current->tk_type == C_PAREN && *subshell == 0))
		{
			print_syntax_error_paren(current);
			return (FAILURE);
		}
		current = current->next;
	}
	return (SUCCESS);
}

int	check_closing_parenthesis(t_token **tokens, int *subshell)
{
	t_token	*current;

	current = *tokens;
	while (current != NULL && current->tk_type != AND && current->tk_type != OR
		&& current->tk_type != SEMI && current->tk_type != PIPE)
	{
		if (current->tk_type == C_PAREN)
		{
			*subshell = *subshell - 1;
			clear_token(tokens, current, free);
			if (current->next != NULL && (current->next)->tk_type == WORD)
			{
				ft_dprintf(2, "-minishell: syntax error near unexpected token "
					"%s\n", (current->next)->word);
				return (FAILURE);
			}
		}
		current = current->next;
	}
	return (SUCCESS);
}
