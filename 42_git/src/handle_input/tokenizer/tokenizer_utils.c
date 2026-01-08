/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 12:57:43 by hanakamu          #+#    #+#             */
/*   Updated: 2026/01/08 16:57:45 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

void	*free_token(t_token *token)
{
	t_token	*tmp;

	while (token != NULL)
	{
		tmp = token->next;
		free(token->word);
		free(token);
		token = tmp;
	}
	return (NULL);
}

t_tk_type	get_token_type_util(char *str)
{
	if (*str == '\'')
		return (SINGLE_QUOTE);
	if (*str == '"')
		return (DOUBLE_QUOTE);
	if (*str == '$' && ft_isalnum(*(str + 1)) == 1)
		return (DOLLAR);
	if (*str == '-' && ft_isalnum(*(str + 1)) == 1)
		return (OPTION);
	if (*str == '(' || *str == ')')
		return (PARENTHESIS);
	if (*str == '*')
		return (WILDCARD);
	if (*str == '~'
		&& (*(str + 1) == '/' || *(str + 1) == ' ' || *(str + 1) == '\0'))
		return (TILDE);
	if (*str == ';')
		return (SEMICOLON);
	if (ft_isspace(*str))
		return (SPACES);
	return (WORD);
}

t_tk_type	get_token_type(char *str)
{
	if (*str == '\0')
		return (END);
	if (ft_strncmp(str, "<<", 2) == 0 || ft_strncmp(str, ">>", 2) == 0)
		return (DOUBLE_REDIRECTION);
	if (*str == '<' || *str == '>')
		return (SINGLE_REDIRECTION);
	if (ft_strncmp(str, "!!", 2) == 0)
		return (DOUBLE_HISTORY);
	if (*str == '!' && ft_isspace(*(str + 1)) == 0)
		return (SINGLE_HISTORY);
	if (ft_strncmp(str, "&&", 2) == 0)
		return (AND);
	if (ft_strncmp(str, "||", 2) == 0)
		return (OR);
	if (*str == '|')
		return (PIPE);
	return (get_token_type_util(str));
}

t_token	*new_token_quoted_str(char *start, char *end, t_token *current)
{
	t_token	*new_token;

	new_token = (t_token *)malloc(sizeof(t_token));
	if (new_token == NULL)
		return (NULL);
	new_token->tk_type = WORD;
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
