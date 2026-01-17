/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   counter.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 14:05:15 by hanakamu          #+#    #+#             */
/*   Updated: 2026/01/16 16:46:25 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <stdbool.h>

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

t_size_exec	count_size_exec(t_token **tokens)
{
	t_size_exec	size;
	t_token		*current;

	size.inrdt = 0;
	size.outrdt = 0;
	current = *tokens;
	while (current != NULL && current->tk_type != AND && current->tk_type != OR
		&& current->tk_type != SEMI && current->tk_type != PIPE)
	{
		if (current->tk_type == SGL_INRDT || current->tk_type == DBL_INRDT)
			size.inrdt = size.inrdt + 1;
		else if (current->tk_type == SGL_OUTRDT
			|| current->tk_type == DBL_OUTRDT)
			size.outrdt = size.outrdt + 1;
		current = current->next;
	}
	return (size);
}

size_t	get_size_command(t_token *tokens)
{
	size_t	counter;

	counter = 0;
	while (tokens != NULL && tokens->tk_type != AND && tokens->tk_type != OR
		&& tokens->tk_type != SEMI && tokens->tk_type != PIPE)
	{
		if (tokens->is_join == false)
			counter = counter + 1;
		tokens = tokens->next;
	}
	return (counter);
}
