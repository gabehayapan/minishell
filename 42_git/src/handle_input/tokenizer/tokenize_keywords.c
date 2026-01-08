/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_keywords.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 12:53:06 by hanakamu          #+#    #+#             */
/*   Updated: 2025/12/21 14:01:29 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

t_token	*tokenize_parenthesis(char **str, t_token *current)
{
	char	*tmp;

	current = create_new_token(str, current, PARENTHESIS);
	if (current == NULL)
		return (NULL);
	while (**str != ')')
	{
		tmp = *str;
		while (get_token_type(*str) != PARENTHESIS
			&& get_token_type(*str) != END)
			(*str)++;
		if (get_token_type(*str) == END)
			*str = syntax_error(tmp, PARENTHESIS);
		else
		{
			current = new_token_quoted_str(tmp, *str, current);
			if (current == NULL)
				return (NULL);
		}
	}
	current = create_new_token(str, current, PARENTHESIS);
	if (current == NULL)
		return (NULL);
	return (current);
}

t_token	*tokenize_env_var(char **str, t_token *current)
{
	char	*tmp;

	tmp = *str;
	while (get_token_type(*str) != SPACES && get_token_type(*str) != END
		&& get_token_type(*str) != DOUBLE_QUOTE)
		(*str)++;
	current = new_token_quoted_str(tmp, *str, current);
	if (current == NULL)
		return (NULL);
	return (current);
}

t_token	*tokenize_dollar(char *start, char **str, t_token *current)
{
	if (start != *str)
	{
		current = new_token_quoted_str(start, *str, current);
		if (current == NULL)
			return (NULL);
	}
	current = create_new_token(str, current, DOLLAR);
	if (current == NULL)
		return (NULL);
	if (**str == '(')
	{
		current = tokenize_parenthesis(str, current);
		if (current == NULL)
			return (NULL);
	}
	else
	{
		current = tokenize_env_var(str, current);
		if (current == NULL)
			return (NULL);
	}
	return (current);
}
