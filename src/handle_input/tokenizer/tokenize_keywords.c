/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_keywords.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 12:53:06 by hanakamu          #+#    #+#             */
/*   Updated: 2026/02/03 09:15:42 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"
#include "ftprintf.h"

t_token	*tokenize_parenthesis(char **input, char **str, t_token *current)
{
	char	*tmp;

	current = create_new_token(str, current, O_PAREN);
	if (current == NULL)
		return (NULL);
	while (**str != ')')
	{
		tmp = *str;
		while (**str != '\0' && **str != ')')
			(*str)++;
		if (**str == '\0')
			*str = syntax_error(input, tmp, C_PAREN);
		else
		{
			current = new_token_quoted_str(tmp, *str, current);
			if (current == NULL)
				return (NULL);
		}
	}
	current = create_new_token(str, current, C_PAREN);
	if (current == NULL)
		return (NULL);
	return (current);
}

t_token	*tokenize_env_var(char **str, t_token *current)
{
	char	*tmp;

	tmp = *str;
	if (*str != NULL && **str == '?')
		*str = *str + 1;
	else
	{
		while (*str != NULL && (ft_isalnum(**str) == 1 || **str == '_'))
			(*str)++;
	}
	current = new_token_quoted_str(tmp, *str, current);
	if (current == NULL)
		return (NULL);
	return (current);
}

t_token	*tokenize_dollar(char **input, char *start, char **str,
			t_token *current)
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
		current = tokenize_parenthesis(input, str, current);
	else
		current = tokenize_env_var(str, current);
	if (current == NULL)
		return (NULL);
	return (current);
}
