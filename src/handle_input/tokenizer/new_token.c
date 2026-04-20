/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 10:24:21 by hanakamu          #+#    #+#             */
/*   Updated: 2026/04/20 09:10:00 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	get_word(char **str, t_token *new_token, t_tk_type tk_type)
{
	int		len;
	char	*tmp;

	tmp = *str;
	if (tk_type == DBL_INRDT || tk_type == DBL_OUTRDT || tk_type == DBL_HIS
		|| tk_type == AND || tk_type == OR)
		len = 2;
	else if (tk_type == WORD || tk_type == SPACES)
	{
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
	if (current != NULL)
		current->next = new_token;
	return (new_token);
}

t_token	*new_token_str(const char *str, t_token *current, t_tk_type tk_type)
{
	t_token	*new_token;

	new_token = (t_token *)malloc(sizeof(t_token));
	if (new_token == NULL)
		return (NULL);
	new_token->word = ft_strdup(str);
	if (new_token->word == NULL)
	{
		free(new_token);
		return (NULL);
	}
	new_token->tk_type = tk_type;
	new_token->is_join = false;
	new_token->prev = current;
	new_token->next = NULL;
	if (current != NULL)
		current->next = new_token;
	return (new_token);
}

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
	return (new_token);
}
