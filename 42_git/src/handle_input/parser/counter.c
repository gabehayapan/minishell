/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   counter.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 14:05:15 by hanakamu          #+#    #+#             */
/*   Updated: 2026/01/14 14:21:27 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

size_t	get_len_command(t_token *tokens)
{
	size_t	len_command;
	size_t	i;

	len_command = 0;
	while (tokens != NULL && tokens->tk_type != AND && tokens->tk_type != OR
		&& tokens->tk_type != SEMI && tokens->tk_type != PIPE)
	{
		i = 0;
		while ((tokens->word)[i] != '\0')
		{
			len_command = len_command + 1;
			i++;
		}
		len_command = len_command + 1;
		tokens = tokens->next;
	}
	return (len_command);
}

size_t	count_array_size(t_token *tokens, t_exec *node_exec)
{
	size_t	counter;

	counter = 3;
	while (tokens != NULL && tokens->tk_type != AND && tokens->tk_type != OR
		&& tokens->tk_type != SEMI)
	{
		if (tokens->tk_type == SGL_INRDT)
			node_exec->num_infile += 1;
		else if (tokens->tk_type == SGL_OUTRDT)
		{
			node_exec->num_outfile += 1;
			node_exec->is_append = 0;
		}
		else if (tokens->tk_type == DBL_INRDT)
			node_exec->num_heredoc += 1;
		else if (tokens->tk_type == DBL_OUTRDT)
		{
			node_exec->num_outfile += 1;
			node_exec->is_append = 1;
		}
		else if (tokens->tk_type == PIPE)
			counter = counter + 1;
		tokens = tokens->next;
	}
	node_exec->num_command = counter
		- node_exec->num_infile - node_exec->num_outfile;
	return (counter);
}
