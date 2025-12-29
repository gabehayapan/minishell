/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 14:23:21 by hanakamu          #+#    #+#             */
/*   Updated: 2025/12/29 14:27:34 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	init_parser(t_parser *parser)
{
	parser->num_infile = 0;
	parser->num_outfile = 0;
	parser->is_heredoc = 0;
	parser->num_command = 0;
	parser->exec_tree = NULL;
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

size_t	count_array_size(t_token *tokens, t_parser *parser)
{
	size_t	counter;

	counter = 3;
	while (tokens != NULL && tokens->tk_type != LOGICAL_OPERATOR
		&& tokens->tk_type != SEMICOLON)
	{
		if (tokens->tk_type == SINGLE_REDIRECTION && *(tokens->word) == '<')
			parser->num_infile += 1;
		if (tokens->tk_type == SINGLE_REDIRECTION && *(tokens->word) == '>')
			parser->num_outfile += 1;
		if (tokens->tk_type == PIPE)
			counter = counter + 1;
		tokens = tokens->next;
	}
	parser->num_command = counter - parser->num_infile - parser->num_outfile;
	return (counter);
}
