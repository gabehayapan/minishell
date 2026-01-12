/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_redirect_file.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 14:19:41 by hanakamu          #+#    #+#             */
/*   Updated: 2026/01/12 12:55:33 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_token	*get_token_infile(t_token *tokens)
{
	while (tokens != NULL && tokens->tk_type != AND && tokens->tk_type != OR
		&& tokens->tk_type != SEMI)
	{
		if (tokens->tk_type == SGL_INRDT)
			return (tokens);
		tokens = tokens->next;
	}
	return (NULL);
}

int	get_infile(t_token *tokens, char **exec)
{
	t_token	*token_infile;

	token_infile = get_token_infile(tokens);
	if (token_infile != NULL && token_infile->next == NULL)
	{
		syntax_error_redirection();
		return (FAILURE);
	}
	else if (token_infile != NULL && token_infile != NULL)
		*exec = (token_infile->next)->word;
	else
		*exec = NULL;
	return (SUCCESS);
}

t_token	*get_token_outfile(t_token *tokens)
{
	while (tokens != NULL && tokens->tk_type != AND && tokens->tk_type != OR
		&& tokens->tk_type != SEMI)
	{
		if (tokens->tk_type == SGL_OUTRDT)
			return (tokens);
		tokens = tokens->next;
	}
	return (NULL);
}

int	get_outfile(t_token *tokens, char **exec)
{
	t_token	*token_outfile;

	token_outfile = get_token_outfile(tokens);
	if (token_outfile != NULL && token_outfile->next == NULL)
	{
		syntax_error_redirection();
		return (FAILURE);
	}
	else if (token_outfile != NULL && token_outfile != NULL)
		*exec = (token_outfile->next)->word;
	else
		*exec = NULL;
	return (SUCCESS);
}

int	get_redirect_file(t_token **tokens, char **exec, size_t size)
{
	int		is_success;
	t_token	*tmp_token;

	is_success = get_infile(*tokens, exec);
	if (is_success == FAILURE)
		return (FAILURE);
	tmp_token = get_token_infile(*tokens);
	if (tmp_token != NULL)
	{
		clear_token(tokens, tmp_token->next, NULL);
		clear_token(tokens, tmp_token, free);
	}
	is_success = get_outfile(*tokens, exec + size - 1);
	if (is_success == FAILURE)
		return (FAILURE);
	tmp_token = get_token_outfile(*tokens);
	if (tmp_token != NULL)
	{
		clear_token(tokens, tmp_token->next, NULL);
		clear_token(tokens, tmp_token, free);
	}
	return (SUCCESS);
}
