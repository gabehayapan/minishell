/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 09:28:01 by hanakamu          #+#    #+#             */
/*   Updated: 2026/01/01 14:24:44 by hanakamu         ###   ########.fr       */
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

size_t	count_array_size(t_token *tokens, t_parser *parser)
{
	size_t	counter;

	counter = 3;
	while (tokens != NULL && tokens->tk_type != LOGICAL_OPERATOR
		&& tokens->tk_type != SEMICOLON)
	{
		if (tokens->tk_type == SINGLE_REDIRECTION && *(tokens->word) == '<')
			parser->num_infile += 1;
		if (tokens->tk_type == SINGLE_REDIRECTION && *(tokens->word) == '>')
			parser->num_outfile += 1;
		if (tokens->tk_type == PIPE)
			counter = counter + 1;
		tokens = tokens->next;
	}
	parser->num_command = counter - parser->num_infile - parser->num_outfile;
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
		if (*(tokens->word) == '>' && tokens->tk_type == SINGLE_REDIRECTION)
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

int	get_redirect_file(t_token **tokens, char **exec, size_t size)
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

size_t	get_len_command(t_token *tokens)
{
	size_t	len_command;
	size_t	i;

	len_command = 0;
	while (tokens != NULL && tokens->tk_type != LOGICAL_OPERATOR
		 && tokens->tk_type != SEMICOLON && tokens->tk_type != PIPE)
	{
		i = 0;
		while ((tokens->word)[i] != '\0')
		{
			len_command = len_command + 1;
			i++;
		}
		len_command = len_command + 1;
		tokens = tokens->next;
	}
	return (len_command);
}

void	get_command(char *exec, t_token *tokens)
{
	size_t	len_exec;
	size_t	len_word;

	len_exec = 0;
	len_word = 0;
	while (tokens != NULL && tokens->tk_type != LOGICAL_OPERATOR
		&& tokens->tk_type != SEMICOLON && tokens->tk_type != PIPE)
	{
		len_word = ft_strlen(tokens->word);
		ft_strlcat(exec, tokens->word, len_exec + len_word + 1);
		len_exec = len_exec + len_word;
		if (tokens->tk_type != OPTION)
		{
			ft_strlcat(exec, " ", len_exec + 2);
			len_exec = len_exec + 1;
		}
		tokens = tokens->next;
	}
	if (len_exec > 0)
		exec[len_exec - 1] = '\0';
	ft_strlcat(exec, "\n", len_exec + 2);
}

int	get_execution(char **exec, size_t size, t_token **tokens)
{
	size_t	len_command;
	size_t	i;

	len_command = get_len_command(*tokens);
	i = 1;
	while (*tokens != NULL && (*tokens)->tk_type != LOGICAL_OPERATOR
		&& (*tokens)->tk_type != SEMICOLON && (*tokens)->tk_type != PIPE)
	{
		*(exec + i) = (char *)ft_calloc(len_command + 1, sizeof(char));
		if (*(exec + i) == NULL)
		{
			while (i--)
				free(*(exec + i));
			free(*(exec + size - 1));
			return (FAILURE);
		}
		get_command(*(exec + i), *tokens);
		while (*tokens != NULL && (*tokens)->tk_type != LOGICAL_OPERATOR
			&& (*tokens)->tk_type != SEMICOLON && (*tokens)->tk_type != PIPE)
			clear_token(tokens, *tokens, free);
		if (*tokens != NULL && (*tokens)->tk_type == PIPE)
			clear_token(tokens, *tokens, free);
		i++;
	}
	return (SUCCESS);
}

int	expand_specials()
{
}

char	**new_exec(t_token **tokens, t_parser *parser)
{
	char	**exec;
	size_t	size;
	int		is_success;

	size = count_array_size(*tokens, parser);
	exec = (char **)malloc(sizeof(char *) * (size + 1));
	if (exec == NULL)
		return (NULL);
	is_success = get_redirect_file(tokens, exec, size);
	if (is_success == FAILURE)
	{
		free(exec);
		return (NULL);
	}
//	expand_specials();
	is_success = get_execution(exec, size, tokens);
	if (is_success == FAILURE)
	{
		free(exec);
		return (NULL);
	}
//	display exec
	for (size_t i = 0; i < size; i++)
	{
		if (i == 0 || i == size - 1)
			printf("%s\n", exec[i]);
		else
			printf("%s", exec[i]);
	}
	return (exec);
}

void	init_parser(t_parser *parser)
{
	parser->num_infile = 0;
	parser->num_outfile = 0;
	parser->is_heredoc = 0;
	parser->num_command = 0;
	parser->exec_tree = NULL;
}

t_exec	*set_last_node(t_parser *parser, char **exec, t_exec *node_exec)
{
	node_exec->tk_type = END;
	node_exec->left = NULL;
	node_exec->right = NULL;
	node_exec->exec = exec;
	if (parser->exec_tree != NULL)
	{
		(parser->exec_tree)->right = node_exec;
		return (parser->exec_tree);
	}
	else
		return (node_exec);
}

t_exec	*set_new_node(char **exec, t_exec *node_exec, t_exec *ctrl_op_node)
{
	ctrl_op_node->left = node_exec;
	node_exec->tk_type = WORD;
	node_exec->left = NULL;
	node_exec->right = NULL;
	node_exec->exec = exec;
	return (ctrl_op_node);
}

t_exec	*new_ctrl_op_node(t_parser *parser, t_token *token)
{
	t_exec	*ctrl_op_node;

	ctrl_op_node = (t_exec *)malloc(sizeof(t_exec));
	if (ctrl_op_node == NULL)
		return (NULL);
	ctrl_op_node->tk_type = token->tk_type;
	ctrl_op_node->left = NULL;
	ctrl_op_node->right = NULL;
	ctrl_op_node->exec = NULL;
	if (parser->exec_tree != NULL)
		(parser->exec_tree)->right = ctrl_op_node;
	return (ctrl_op_node);
}

t_exec	*new_exec_tree(t_parser *parser, t_token **tokens, char **exec)
{
	t_exec	*node_exec;
	t_exec	*ctrl_op_node;

	ctrl_op_node = NULL;
	if (*tokens != NULL)
	{
		ctrl_op_node = new_ctrl_op_node(parser, *tokens);
		if (ctrl_op_node == NULL)
			return (NULL);
		clear_token(tokens, *tokens, free);
	}
	node_exec = (t_exec *)malloc(sizeof(t_exec));
	if (node_exec == NULL)
		return (NULL);
	if (ctrl_op_node == NULL)
		return (set_last_node(parser, exec, node_exec));
	else
		return (set_new_node(exec, node_exec, ctrl_op_node));
}

t_parser	*parser(t_token **tokens)
{
	t_parser	*parser;
	char		**exec;

	parser = (t_parser *)malloc(sizeof(t_parser));
	if (parser == NULL)
		return (NULL);
	init_parser(parser);
	while (*tokens != NULL)
	{
		exec = new_exec(tokens, parser);
		if (exec == NULL)
		{
			free(parser);
			return (NULL);
		}
		parser->exec_tree = new_exec_tree(parser, tokens, exec);
		if (exec == NULL)
		{
			free(parser);
			return (NULL);
		}
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
