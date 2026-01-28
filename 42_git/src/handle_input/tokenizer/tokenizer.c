/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 11:54:45 by hanakamu          #+#    #+#             */
/*   Updated: 2026/01/28 13:18:11 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"
#include <stdbool.h>

int	get_word(char **str, t_token *new_token, t_tk_type tk_type)
{
	int		len;
	char	*tmp;

	tmp = *str;
	if (tk_type == DBL_INRDT || tk_type == DBL_OUTRDT || tk_type == DBL_HIS
		|| tk_type == AND || tk_type == OR)
		len = 2;
	else if (tk_type == WORD || tk_type == SPACES)
	{
		len = 0;
		while (get_token_type(tmp) == tk_type)
			tmp++;
		len = tmp - *str;
	}
	else
		len = 1;
	if (tk_type == BACKSLASH)
		*str = *str + 1;
	new_token->word = ft_substr(*str, 0, len);
	if (new_token->word == NULL)
		return (FAILURE);
	*str = *str + len;
	return (SUCCESS);
}

t_token	*create_new_token(char **str, t_token *current, t_tk_type tk_type)
{
	t_token	*new_token;

	new_token = (t_token *)malloc(sizeof(t_token));
	if (new_token == NULL)
		return (NULL);
	if (get_word(str, new_token, tk_type) == FAILURE)
	{
		free(new_token);
		return (NULL);
	}
	new_token->tk_type = tk_type;
	new_token->is_join = false;
	new_token->prev = current;
	new_token->next = NULL;
	current->next = new_token;
	return (new_token);
}

t_token	*new_token(char **input, char **str,
			t_token *current, t_tk_type tk_type)
{
	if (tk_type == DOLLAR)
		return (tokenize_dollar(input, *str, str, current));
	else
		return (create_new_token(str, current, tk_type));
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
		current = new_token(input, &str, current, tk_type);
		if (current == NULL)
			return (free_token(head.next));
		if (tk_type == SGL_QTE || tk_type == DBL_QTE)
		{
			current = tokenize_quote(input, &str, current, tk_type);
			if (current == NULL)
				return (free_token(head.next));
		}
	}
	free(cp_str);
	return (head.next);
}
