/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 09:28:01 by hanakamu          #+#    #+#             */
/*   Updated: 2025/12/29 10:09:05 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	syntax_error_redirection(void)
{
	ft_putstr_fd("syntax error for redirection", 2);
}

void	clear_token(t_token **tokens, t_token *target, void (*del)(void *))
{
	t_token	*tmp;

	if (tokens == NULL || *tokens == NULL || target == NULL)
		return ;
	tmp = *tokens;
	while (tmp->next != target && tmp != target && tmp != NULL)
		tmp = tmp->next;
	tmp->next = target->next;
	if (*tokens == target)
		*tokens = target->next;
	if (del != NULL)
		(*del)(target->word);
	free(target);
}

size_t	count_array_size(t_token *tokens)
{
	size_t	counter;

	counter = 3;
	while (tokens != NULL && tokens->tk_type != LOGICAL_OPERATOR
		&& tokens->tk_type != SEMICOLON)
	{
		if (tokens->tk_type == PIPE)
			counter = counter + 1;
		tokens = tokens->next;
	}
	return (counter);
}

t_token	*get_token_infile(t_token *tokens)
{
	while (tokens != NULL && tokens->tk_type != LOGICAL_OPERATOR
		&& tokens->tk_type != SEMICOLON)
	{
		if (*(tokens->word) == '<' && tokens->tk_type == SINGLE_REDIRECTION)
			return (tokens);
		tokens = tokens->next;
	}
	return (NULL);
}

int	get_infile(t_token *tokens, char **exec)
{
	t_token	*token_infile;

	token_infile = get_token_infile(tokens);
	if (token_infile != NULL && token_infile->next == NULL)
	{
		syntax_error_redirection();
		return (FAILURE);
	}
	else if (token_infile != NULL && token_infile != NULL)
		*exec = (token_infile->next)->word;
	else
		*exec = NULL;
	return (SUCCESS);
}

t_token	*get_token_outfile(t_token *tokens)
{
	while (tokens != NULL && tokens->tk_type != LOGICAL_OPERATOR
		&& tokens->tk_type != SEMICOLON)
	{
		if (*(tokens->word) == '<' && tokens->tk_type == SINGLE_REDIRECTION)
			return (tokens);
		tokens = tokens->next;
	}
	return (NULL);
}

int	get_outfile(t_token *tokens, char **exec)
{
	t_token	*token_outfile;

	token_outfile = get_token_outfile(tokens);
	if (token_outfile != NULL && token_outfile->next == NULL)
	{
		syntax_error_redirection();
		return (FAILURE);
	}
	else if (token_outfile != NULL && token_outfile != NULL)
		*exec = (token_outfile->next)->word;
	else
		*exec = NULL;
	return (SUCCESS);
}

int	get_infile_outfile(t_token **tokens, char **exec, size_t size)
{
	int		is_success;
	t_token	*tmp_token;

	is_success = get_infile(*tokens, exec);
	if (is_success == FAILURE)
		return (FAILURE);
	tmp_token = get_token_infile(*tokens);
	if (tmp_token != NULL)
	{
		clear_token(tokens, tmp_token->next, NULL);
		clear_token(tokens, tmp_token, free);
	}
	is_success = get_outfile(*tokens, exec + size - 1);
	if (is_success == FAILURE)
		return (FAILURE);
	tmp_token = get_token_outfile(*tokens);
	if (tmp_token != NULL)
	{
		clear_token(tokens, tmp_token->next, NULL);
		clear_token(tokens, tmp_token, free);
	}
	return (SUCCESS);
}

t_parser	*parser(t_token **tokens)
{
	t_parser	*parser;
	size_t		size;
	char		**exec;
	int			is_success;

	parser = (t_parser *)malloc(sizeof(t_parser));
	if (parser == NULL)
		return (NULL);
	size = count_array_size(*tokens);
	exec = (char **)malloc(sizeof(char *) * (size + 1));
	if (exec == NULL)
		return (NULL);
	is_success = get_infile_outfile(tokens, exec, size);
	if (is_success == FAILURE)
	{
		free(exec);
		return (NULL);
	}
	return (parser);
}

int	main(void)
{
	t_token	*tokens;
	t_token	*tmp;
	char	*line;
	void	*ptr;

	line = readline("prompt> ");
	printf("line:%s\n", line);
	tokens = tokenizer(line);
	if (tokens == NULL)
	{
		printf("error at tokenizer\n");
		return (1);
	}
	tmp = tokens;
	while (tmp != NULL)
	{
		printf("word:%s, token type:%d\n", tmp->word, tmp->tk_type);
		tmp = tmp->next;
	}
	ptr = parser(&tokens);
//	printf("%s\n", (char *)ptr);
	free(line);
//	exit(1);
	free_token(tokens);
	return (0);
}
