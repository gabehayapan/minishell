/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_quote.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 12:45:43 by hanakamu          #+#    #+#             */
/*   Updated: 2026/01/31 15:35:52 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"
#include <stdbool.h>

t_token	*new_token_quoted_str(char *start, char *end, t_token *current)
{
	t_token	*new_token;

	new_token = (t_token *)malloc(sizeof(t_token));
	if (new_token == NULL)
		return (NULL);
	new_token->tk_type = WORD;
	new_token->is_join = false;
	new_token->prev = current;
	new_token->next = NULL;
	new_token->word = ft_substr(start, 0, end - start);
	if (new_token->word == NULL)
	{
		free(new_token);
		return (NULL);
	}
	current->next = new_token;
	current = new_token;
	return (new_token);
}

t_token	*tokenize_single_quote(char **input, char **str, t_token *current)
{
	char	*start;

	current = create_new_token(str, current, SGL_QTE);
	if (current == NULL)
		return (NULL);
	while (**str != '\'')
	{
		start = *str;
		while (**str != '\0' && **str != '\'')
			(*str)++;
		if (**str == '\0')
			*str = syntax_error(input, start, SGL_QTE);
		else
		{
			current = new_token_quoted_str(start, *str, current);
			if (current == NULL)
				return (NULL);
		}
	}
	return (create_new_token(str, current, SGL_QTE));
}

t_token	*tokenize_double_quote(char **input, char **str, t_token *current)
{
	char	*tmp;

	current = create_new_token(str, current, DBL_QTE);
	if (current == NULL)
		return (NULL);
	while (**str != '\"')
	{
		tmp = *str;
		while (**str != '\0' && **str != '$' && **str != '\"')
			(*str)++;
		if (**str == '\0')
			*str = syntax_error(input, tmp, DBL_QTE);
		else
		{
			if (**str == '"')
				current = new_token_quoted_str(tmp, *str, current);
			else
				current = tokenize_dollar(input, tmp, str, current);
			if (current == NULL)
				return (NULL);
			if (**str == '"')
				break ;
		}
	}
	return (create_new_token(str, current, DBL_QTE));
}

t_token	*tokenize_quote(char **input, char **str,
			t_token *current, t_tk_type tk_type)
{
	if (tk_type == SGL_QTE)
		return (tokenize_single_quote(input, str, current));
	else
		return (tokenize_double_quote(input, str, current));
}
