/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_quote.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 12:45:43 by hanakamu          #+#    #+#             */
/*   Updated: 2025/12/21 12:49:22 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

t_token	*handle_single_quote(char **str, t_token *current)
{
	char	*start;

	while (**str != '\'')
	{
		start = *str;
		while (get_token_type(*str) != SINGLE_QUOTE
			&& get_token_type(*str) != END)
			(*str)++;
		if (get_token_type(*str) == END)
			*str = syntax_error(start, SINGLE_QUOTE);
		else
		{
			current = new_token_quoted_str(start, *str, current);
			if (current == NULL)
				return (NULL);
		}
	}
	return (create_new_token(str, current, SINGLE_QUOTE));
}

t_token	*handle_double_quote(char **str, t_token *current)
{
	char	*tmp;

	while (get_token_type(*str) != DOUBLE_QUOTE)
	{
		tmp = *str;
		while (get_token_type(*str) != END && get_token_type(*str) != DOLLAR
			&& get_token_type(*str) != DOUBLE_QUOTE)
			(*str)++;
		if (get_token_type(*str) == END)
			*str = syntax_error(tmp, DOUBLE_QUOTE);
		else if (get_token_type(*str) == DOUBLE_QUOTE)
		{
			current = new_token_quoted_str(tmp, *str, current);
			if (current == NULL)
				return (NULL);
			break ;
		}
		else
		{
			current = tokenize_dollar(tmp, str, current);
			if (current == NULL)
				return (NULL);
		}
	}
	return (create_new_token(str, current, DOUBLE_QUOTE));
}

t_token	*handle_quote(char **str, t_token *current, t_tk_type tk_type)
{
	if (tk_type == SINGLE_QUOTE)
		return (handle_single_quote(str, current));
	else
		return (handle_double_quote(str, current));
}
