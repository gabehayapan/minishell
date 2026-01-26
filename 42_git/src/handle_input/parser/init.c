/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 14:23:21 by hanakamu          #+#    #+#             */
/*   Updated: 2026/01/26 12:13:05 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	init_node_exec(t_exec *node_exec)
{
	node_exec->tk_type = WORD;
	node_exec->left = NULL;
	node_exec->right = NULL;
	node_exec->command = NULL;
	node_exec->next = NULL;
}

void	init_command(t_command *command, int subshell)
{
	command->inrdt = NULL;
	command->outrdt = NULL;
	command->command = NULL;
	command->is_subshell = subshell;
	command->next = NULL;
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
			if (current->tk_type == O_PAREN)
				ft_dprintf(2, "minishell: syntax error near `('\n");
			else
				ft_dprintf(2, "minishell: syntax error near `)'\n");
			return (FAILURE);
		}
		current = current->next;
	}
	return (SUCCESS);
}

void	check_closing_parenthesis(t_token **tokens, int *subshell)
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
		}
		current = current->next;
	}
}

int	initialize_command(t_token **tokens, t_command *current, int *subshell)
{
	int	is_success;

	is_success = check_opening_parenthesis(tokens, subshell);
	if (is_success == FAILURE)
		return (FAILURE);
	init_command(current, *subshell);
	check_closing_parenthesis(tokens, subshell);
	return (SUCCESS);
}
