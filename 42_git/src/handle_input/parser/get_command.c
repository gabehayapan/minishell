/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 14:25:58 by hanakamu          #+#    #+#             */
/*   Updated: 2026/01/08 20:34:04 by hanakamu         ###   ########.fr       */
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
	if ((*token)->tk_type == SINGLE_QUOTE || (*token)->tk_type == DOUBLE_QUOTE)
		return ;
	while ((*token)->tk_type != SINGLE_QUOTE
		&& (*token)->tk_type != DOUBLE_QUOTE)
	{
		len_word = ft_strlen((*token)->word);
		ft_strlcat(exec + *len_exec, (*token)->word, len_word + 1);
		*len_exec = *len_exec + len_word;
		if ((*token)->tk_type != DOLLAR
			&& ((*token)->next)->tk_type != DOUBLE_QUOTE)
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
		&& tokens->tk_type != SEMICOLON && tokens->tk_type != PIPE)
	{
		if (tokens->tk_type == SINGLE_QUOTE || tokens->tk_type == DOUBLE_QUOTE)
		{
			get_quoted_command(exec, &tokens, &len_exec, is_space);
			is_space = 1;
			continue ;
		}
		len_word = ft_strlen(tokens->word);
		ft_strlcat(exec + len_exec, tokens->word, len_word + 1);
		len_exec = len_exec + len_word;
		if (tokens->tk_type != OPTION && tokens->tk_type != TILDE
			&& tokens->next != NULL && (tokens->next)->tk_type != PIPE
			&& (tokens->next)->tk_type != AND && (tokens->next)->tk_type != OR)
			add_space(exec, &len_exec);
		tokens = tokens->next;
	}
}
