/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_quote.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 12:45:43 by hanakamu          #+#    #+#             */
/*   Updated: 2026/01/22 19:03:25 by hanakamu         ###   ########.fr       */
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

	while (**str != '\'')
	{
		start = *str;
		while (get_token_type(*str) != SGL_QTE
			&& get_token_type(*str) != END)
			(*str)++;
		if (get_token_type(*str) == END)
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

	while (get_token_type(*str) != DBL_QTE)
	{
		tmp = *str;
		while (get_token_type(*str) != END && get_token_type(*str) != DOLLAR
			&& get_token_type(*str) != DBL_QTE)
			(*str)++;
		if (get_token_type(*str) == END)
			*str = syntax_error(input, tmp, DBL_QTE);
		else if (get_token_type(*str) == DBL_QTE)
		{
			current = new_token_quoted_str(tmp, *str, current);
			if (current == NULL)
				return (NULL);
			break ;
		}
		else
		{
			current = tokenize_dollar(input, tmp, str, current);
			if (current == NULL)
				return (NULL);
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
