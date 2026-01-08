/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 14:23:21 by hanakamu          #+#    #+#             */
/*   Updated: 2026/01/08 18:52:26 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	init_node_exec(t_exec *node_exec)
{
	node_exec->num_infile = 0;
	node_exec->num_outfile = 0;
	node_exec->is_heredoc = 0;
	node_exec->num_command = 0;
	node_exec->exec = NULL;
}

void	free_exec(t_exec *node_exec)
{
	size_t	i;

	i = 0;
	while (i < node_exec->size_exec)
	{
		free((node_exec->exec)[i]);
		i++;
	}
	free(node_exec->exec);
}

void	free_node_exec(t_exec *node_exec)
{
	if (node_exec == NULL)
		return ;
	free_node_exec(node_exec->left);
	free_node_exec(node_exec->right);
	free_exec(node_exec);
	free(node_exec);
}

void	clear_token(t_token **tokens, t_token *target, void (*del)(void *))
{
	t_token	*tmp;

	if (tokens == NULL || *tokens == NULL || target == NULL)
		return ;
	tmp = *tokens;
	while (tmp->next != target && tmp != target && tmp != NULL)
		tmp = tmp->next;
	tmp->next = target->next;
	if (*tokens == target)
		*tokens = target->next;
	if (del != NULL)
		(*del)(target->word);
	free(target);
}

size_t	count_array_size(t_token *tokens, t_exec *node_exec)
{
	size_t	counter;

	counter = 3;
	while (tokens != NULL && tokens->tk_type != AND && tokens->tk_type != OR
		&& tokens->tk_type != SEMICOLON)
	{
		if (tokens->tk_type == SINGLE_REDIRECTION && *(tokens->word) == '<')
			node_exec->num_infile += 1;
		if (tokens->tk_type == SINGLE_REDIRECTION && *(tokens->word) == '>')
			node_exec->num_outfile += 1;
		if (tokens->tk_type == PIPE)
			counter = counter + 1;
		tokens = tokens->next;
	}
	node_exec->num_command = counter
		- node_exec->num_infile - node_exec->num_outfile;
	return (counter);
}
