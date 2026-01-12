/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 14:25:58 by hanakamu          #+#    #+#             */
/*   Updated: 2026/01/12 12:54:09 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	add_space(char *exec, size_t *len_exec)
{
	ft_strlcat(exec + *len_exec, " ", 2);
	*len_exec = *len_exec + 1;
}

void	get_quoted_command(char *exec, t_token **token, size_t *len_exec,
			int is_space)
{
	size_t	len_word;

	if (is_space == 1)
		add_space(exec, len_exec);
	*token = (*token)->next;
	if ((*token)->tk_type == SGL_QTE || (*token)->tk_type == DBL_QTE)
		return ;
	while ((*token)->tk_type != SGL_QTE
		&& (*token)->tk_type != DBL_QTE)
	{
		len_word = ft_strlen((*token)->word);
		ft_strlcat(exec + *len_exec, (*token)->word, len_word + 1);
		*len_exec = *len_exec + len_word;
		if ((*token)->tk_type != DOLLAR
			&& ((*token)->next)->tk_type != DBL_QTE)
			add_space(exec, len_exec);
		*token = (*token)->next;
	}
	*token = (*token)->next;
}

void	get_command(char *exec, t_token *tokens)
{
	size_t	len_exec;
	size_t	len_word;
	int		is_space;

	len_exec = 0;
	len_word = 0;
	is_space = 0;
	while (tokens != NULL && tokens->tk_type != AND && tokens->tk_type != OR
		&& tokens->tk_type != SEMI && tokens->tk_type != PIPE)
	{
		if (tokens->tk_type == SGL_QTE || tokens->tk_type == DBL_QTE)
		{
			get_quoted_command(exec, &tokens, &len_exec, is_space);
			is_space = 1;
			continue ;
		}
		len_word = ft_strlen(tokens->word);
		ft_strlcat(exec + len_exec, tokens->word, len_word + 1);
		len_exec = len_exec + len_word;
		if (tokens->tk_type != HYPHEN && tokens->tk_type != TILDE
			&& tokens->next != NULL && (tokens->next)->tk_type != PIPE
			&& (tokens->next)->tk_type != AND && (tokens->next)->tk_type != OR)
			add_space(exec, &len_exec);
		tokens = tokens->next;
	}
}
