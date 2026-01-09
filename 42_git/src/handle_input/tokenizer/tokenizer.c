/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 11:54:45 by hanakamu          #+#    #+#             */
/*   Updated: 2026/01/09 18:41:50 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

int	get_word(char **str, t_token *new_token, t_tk_type tk_type)
{
	int		len;
	char	*tmp;

	tmp = *str;
	if (tk_type == DOUBLE_REDIRECTION || tk_type == DOUBLE_HISTORY
		|| tk_type == AND || tk_type == OR)
		len = 2;
	else if (tk_type == WORD)
	{
		len = 0;
		while (get_token_type(tmp) == WORD)
			tmp++;
		len = tmp - *str;
	}
	else
		len = 1;
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
	new_token->next = NULL;
	current->next = new_token;
	return (new_token);
}

t_token	*tokenizer(char *str)
{
	t_token		head;
	t_token		*current;
	t_tk_type	tk_type;

	head.next = NULL;
	current = &head;
	while (*str != '\0')
	{
		while (ft_isspace(*str))
			str++;
		tk_type = get_token_type(str);
		current = create_new_token(&str, current, tk_type);
		if (current == NULL)
			return (free_token(head.next));
		if (tk_type == SINGLE_QUOTE || tk_type == DOUBLE_QUOTE)
		{
			current = handle_quote(&str, current, tk_type);
			if (current == NULL)
				return (free_token(head.next));
		}
	}
	return (head.next);
}
