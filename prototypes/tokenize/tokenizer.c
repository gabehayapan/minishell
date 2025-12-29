/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 11:54:45 by hanakamu          #+#    #+#             */
/*   Updated: 2025/12/28 18:40:28 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenize.h"

#include <stdio.h>

void	*ft_realloc(void *ptr, size_t size)
{
	void			*new_ptr;
	unsigned char	*cp_ptr;
	unsigned char	*cp_str;

	new_ptr = malloc(sizeof(unsigned char) * size);
	if (new_ptr == NULL)
	{
		free(ptr);
		return (NULL);
	}
	cp_ptr = (unsigned char *)new_ptr;
	cp_str = (unsigned char *)ptr;
	while (*cp_str != '\0')
	{
		*cp_ptr = *cp_str;
		cp_ptr++;
		cp_str++;
	}
	*cp_ptr = '\0';
	free(ptr);
	return (new_ptr);
}

char	get_missing_char(t_tk_type tk_type)
{
	if (tk_type == SINGLE_QUOTE)
		return ('\'');
	else if (tk_type == DOUBLE_QUOTE)
		return ('"');
	else if (tk_type == PARENTHESIS)
		return (')');
	else
		return ('\0');
}

void	*error_unexpected_eof(void)
{
	ft_putstr_fd("Unexpected EOF\n", 2);
	return (NULL);
}

char	*get_new_input(char *input, char **new_input)
{
	*new_input = readline("> ");
	if (*new_input == NULL)
		return (error_unexpected_eof());
	if (input == NULL)
		input = (char *)ft_calloc(ft_strlen(*new_input) + 1, sizeof(char));
	else
		input = ft_realloc(input, ft_strlen(input) + ft_strlen(*new_input) + 1);
	if (input == NULL)
	{
		free(*new_input);
		return (NULL);
	}
	ft_strlcat(input, *new_input, ft_strlen(input) + ft_strlen(*new_input) + 1);
	return (input);
}

char	*syntax_error(char *start, t_tk_type tk_type)
{
	t_syntax_err	syn_err;

	syn_err.c = get_missing_char(tk_type);
	ft_putchar_fd(syn_err.c, 2);
	ft_putstr_fd(" is missing\n", 2);
	syn_err.input = NULL;
	syn_err.new_input = NULL;
	syn_err.input = get_new_input(syn_err.input, &syn_err.new_input);
	if (syn_err.input == NULL)
		return (NULL);
	while (ft_strchr(syn_err.new_input, syn_err.c) == NULL)
	{
		free(syn_err.new_input);
		syn_err.input = get_new_input(syn_err.input, &syn_err.new_input);
		if (syn_err.input == NULL)
			return (NULL);
	}
	syn_err.new_str = ft_strjoin(start, syn_err.input);
	free(syn_err.input);
	free(syn_err.new_input);
	if (syn_err.new_str == NULL)
		return (NULL);
	return (syn_err.new_str);
}

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
	if (ft_strncmp(str, "&&", 2) == 0 || ft_strncmp(str, "||", 2) == 0)
		return (LOGICAL_OPERATOR);
	if (*str == '|')
		return (PIPE);
	return (get_token_type_util(str));
}

int	get_word(char **str, t_token *new_token, t_tk_type tk_type)
{
	int		len;
	char	*tmp;

	tmp = *str;
	if (tk_type == DOUBLE_REDIRECTION || tk_type == DOUBLE_HISTORY
		|| tk_type == LOGICAL_OPERATOR)
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

//int	main(void)
//{
//	t_token	*tokens;
//	t_token	*tmp;
//	char	*line;
//
//	line = readline("prompt> ");
//	printf("line:%s\n", line);
//	tokens = tokenizer(line);
//	if (tokens == NULL)
//		return (1);
//	tmp = tokens;
//	while (tmp != NULL)
//	{
//		ft_printf("word:%s, token type:%d\n", tmp->word, tmp->tk_type);
//		tmp = tmp->next;
//	}
//	free(line);
//	free_token(tokens);
//	return (0);
//}
