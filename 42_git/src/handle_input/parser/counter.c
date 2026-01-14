/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   counter.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 14:05:15 by hanakamu          #+#    #+#             */
/*   Updated: 2026/01/14 19:21:15 by hanakamu         ###   ########.fr       */
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

t_size_exec	count_size_exec(t_token *tokens)
{
	t_size_exec	size;

	size.inrdt = 0;
	size.outrdt = 0;
	while (tokens != NULL && tokens->tk_type != AND && tokens->tk_type != OR
		&& tokens->tk_type != SEMI && tokens->tk_type != PIPE)
	{
		if (tokens->tk_type == SGL_INRDT || tokens->tk_type == DBL_INRDT)
			size.inrdt = size.inrdt + 1;
		else if (tokens->tk_type == SGL_OUTRDT || tokens->tk_type == DBL_OUTRDT)
			size.outrdt = size.outrdt + 1;
		tokens = tokens->next;
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
		if (tokens->tk_type != HYPHEN)
			counter = counter + 1;
		tokens = tokens->next;
	}
	return (counter);
}
