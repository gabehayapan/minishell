/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 11:54:45 by hanakamu          #+#    #+#             */
/*   Updated: 2026/02/02 10:25:06 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"
#include <stdbool.h>

static t_token	*new_token(char **input, char **str,
			t_token **current, t_tk_type tk_type)
{
	if (tk_type == DOLLAR)
		*current = tokenize_dollar(input, *str, str, *current);
	else if (tk_type == SGL_QTE || tk_type == DBL_QTE)
		*current = tokenize_quote(input, str, *current, tk_type);
	else
		*current = create_new_token(str, *current, tk_type);
	if (*current == NULL)
		return (NULL);
	return (*current);
}

t_token	*tokenizer(char **input)
{
	t_token		head;
	t_token		*current;
	t_tk_type	tk_type;
	char		*str;
	char		*cp_str;

	if (init_token_vars(&head, &current, input, &str) == FAILURE)
		return (NULL);
	cp_str = str;
	while (*str != '\0')
	{
		tk_type = get_token_type(str);
		current = new_token(input, &str, &current, tk_type);
		if (current == NULL)
		{
			free(cp_str);
			return (free_token(head.next));
		}
	}
	free(cp_str);
	if (head.next != NULL)
		(head.next)->prev = NULL;
	return (head.next);
}
