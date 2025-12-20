/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 18:12:44 by hanakamu          #+#    #+#             */
/*   Updated: 2025/12/19 11:08:22 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenize.h"

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

t_tk_type	get_token_type_util()
{
}

t_tk_type	get_token_type(char *str)
{
	if (*str == '\0')
		return (END);
	if (ft_strncmp(str, "<<", 2) || ft_strncmp(str, ">>", 2))
		return (DOUBLE_REDIRECTION);
	if (*str == '<' || *str == '>')
		return (SINGLE_REDIRECTION);
	if (ft_strncmp(str, "!!", 2))
		return (DOUBLE_HISTORY);
	if (*str == '!' && ft_isspace(*(str + 1)) == 0)
		return (SINGLE_HISTORY);
	if (ft_strncmp(str, "&&", 2) || ft_strncmp(str, "||", 2))
		return (LOGICAL_OPERATOR);
	if (*str == '|')
		return (PIPE);
	if (*str == ''')
		return (SINGLE_QUOTE);
	if (*str == '"')
		return (DOUBLE_QUOTE);
	if (*str == '$' && ft_isspace(*(str + 1)) == 0)
		return (DOLLAR);
	if (*str == '-' && ft_isspace(*(str + 1)) == 0)
		return (OPTION);
	if (*str == '(' || *str == ')')
		return (PRIORITY);
	if (*str == '*')
		return (WILDCARD);
	if (ft_isspace(*str))
		return (SPACE);
	return (WORD);
}

int	get_word(char **str, t_token *new_token, t_tk_type tk_type)
{
	char	*tmp;

	if (tk_type == DOUBLE_REDIRECTION || tk_type == DOUBLE_HISTORY
		|| tk_type == LOGICAL_OPERATOR)
	{
		new_token->word = ft_substr(str, 0, 2);
		if (new_token->word == NULL)
			return (1);
		*str = *str + 2;
	}
	else if (tk_type == WORD)
	{
		tmp = *str;
		while (get_token_type(*str) == WORD)
			(*str)++;
		new_token->word == ft_substr(tmp, 0, *str - tmp);
		if (new_token->word == NULL)
			return (1);
	}
	else
	{
		new_token->word = ft_substr(str, 0, 1);
		if (new_token->word == NULL)
			return (1);
		*str = *str + 1;
	}
	return(0);
}

t_token	*new_token(char **str, t_token *current, t_tk_type tk_type)
{
	t_token	*new_token;

	new_token = (t_token *)malloc(sizeof(t_token));
	if (new_token == NULL)
		return (NULL);
	get_word(str, new_token, tk_type);
	new_token->tk_type = tk_type;
	new_token->next = NULL;
	current->next = new_token;
	return (new_token);
}

t_token	*handle_quote(char **str, t_token *current, t_tk_type tk_type)
{
	t_token	*new_token;
	char	*tmp;

	new_token = (t_token *)malloc(sizeof(t_token));
	if (new_token == NULL)
		return (NULL);
	new_token->tk_type = WORD;
	new_token->next = NULL;
	current->next = new_token;
	if (tk_type == SINGLE_QUOTE)
	{
		tmp = *str;
		while (get_token_type(*str) != SINGLE_QUOTE && get_token_type(*str) != END)
			(*str)++;
		if (get_token_type(*str) == END)
			syntax_error();
		new_token->word = ft_substr(tmp, 0, str - tmp);
		if (new_token->word == NULL)
			return (NULL);
	}
	else
	{
		while (get_token_type(*str) != DOUBLE_QUOTE)
		{
			tmp = *str;
			while (get_token_type(*str) != DOUBLE_QUOTE && get_token_type(*str) != END
				&& get_token_type(*str) != DOLLAR)
				(*str)++;
			if (get_token_type(*str) == END)
				syntax_error(tmp, DOUBLE_QUOTE);
			else
			{
				new_token->word = ft_substr(tmp, 0, *str - tmp);
				if (new_token->word == NULL)
					return (NULL);
				new_token->tk_type = DOLLAR;
				new_token->next = NULL;
				if (get_token_type(*str) == DOLLAR)
			}
		}
	}
	return (new_token);
}

t_token	*tokenize(char *str)
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
		current = new_token(&str, current, tk_type);
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

int	main(int argc, char **argv)
{
	if (argc != 2)
	{
		write(2, "arg error\n", 10);
		return (1);
	}
	if (tokenize(argv[1]) == NULL)
		return (1);
	return (0);
}
