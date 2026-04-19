/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 14:23:21 by hanakamu          #+#    #+#             */
/*   Updated: 2026/02/04 12:50:03 by hanakamu         ###   ########.fr       */
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

int	initialize_command(t_token **tokens, t_command **current, int *subshell)
{
	int	is_success;

	*current = (t_command *)malloc(sizeof(t_command));
	if (*current == NULL)
		return (FAILURE);
	is_success = check_opening_parenthesis(tokens, subshell);
	if (is_success == FAILURE)
	{
		free(*current);
		return (FORMAT_ERROR);
	}
	init_command(*current, *subshell);
	is_success = check_closing_parenthesis(tokens, subshell);
	if (is_success == FAILURE)
	{
		free(*current);
		return (FORMAT_ERROR);
	}
	return (SUCCESS);
}
