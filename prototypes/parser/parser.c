/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 09:28:01 by hanakamu          #+#    #+#             */
/*   Updated: 2026/01/05 15:42:40 by hanakamu         ###   ########.fr       */
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

void	add_space(char *exec, size_t *len_exec)
{
	ft_strlcat(exec + *len_exec, " ", *len_exec + 2);
	*len_exec = *len_exec + 1;
}

void	set_end_of_exec(char *exec, size_t len_exec)
{
	if (len_exec > 0)
		exec[len_exec] = '\0';
	ft_strlcat(exec + len_exec, "\n", len_exec + 2);
}

void	get_quoted_command(char *exec, t_token **token, size_t *len_exec,
			int is_space)
{
	size_t		len_word;

	if (is_space == 1)
		add_space(exec, len_exec);
	*token = (*token)->next;
	if ((*token)->tk_type == SINGLE_QUOTE || (*token)->tk_type == DOUBLE_QUOTE)
		return ;
	while ((*token)->tk_type != SINGLE_QUOTE
		&& (*token)->tk_type != DOUBLE_QUOTE)
	{
		len_word = ft_strlen((*token)->word);
		ft_strlcat(exec + *len_exec, (*token)->word, *len_exec + len_word + 1);
		*len_exec = *len_exec + len_word;
		if ((*token)->tk_type != DOLLAR
			&& ((*token)->next)->tk_type != DOUBLE_QUOTE)
			add_space(exec, len_exec);
		*token = (*token)->next;
	}
	*token = (*token)->next;
}

void	get_command(char *exec, t_token *tokens)
{
	size_t	len_exec;
	size_t	len_word;
	int		is_space;

	len_exec = 0;
	len_word = 0;
	is_space = 0;
	while (tokens != NULL && tokens->tk_type != LOGICAL_OPERATOR
		&& tokens->tk_type != SEMICOLON && tokens->tk_type != PIPE)
	{
		if (tokens->tk_type == SINGLE_QUOTE || tokens->tk_type == DOUBLE_QUOTE)
		{
			get_quoted_command(exec, &tokens, &len_exec, is_space);
			is_space = 1;
			continue ;
		}
		len_word = ft_strlen(tokens->word);
		ft_strlcat(exec + len_exec, tokens->word, len_exec + len_word + 1);
		len_exec = len_exec + len_word;
		if (tokens->tk_type != OPTION && tokens->tk_type != TILDE
			&& tokens->next != NULL)
			add_space(exec, &len_exec);
		tokens = tokens->next;
	}
	set_end_of_exec(exec, len_exec);
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

int	expand_dollar(t_token **tokens, t_token *current, t_env *env_lst)
{
	t_token	*next;
	char	*env_var;

	next = current->next;
	env_var = ft_getenv(env_lst, next->word);
	free(current->word);
	clear_token(tokens, next, free);
	if (env_var == NULL)
		current->word = ft_strdup("");
	else
		current->word = ft_strdup(env_var);
	if (current->word == NULL)
		return (FAILURE);
	return (SUCCESS);
}

int	expand_tilde(t_token *current, t_env *env_lst)
{
	char	*path_home;

	path_home = ft_getenv(env_lst, "HOME");
	free(current->word);
	if (path_home == NULL)
		current->word = ft_strdup("");
	else
		current->word = ft_strdup(path_home);
	if (current->word == NULL)
		return (FAILURE);
	return (SUCCESS);
}

int	expand_specials(t_token **tokens, t_env *env_lst)
{
	t_token	*current;
	int		is_success;

	current = *tokens;
	is_success = SUCCESS;
	while (current != NULL)
	{
		if (current->tk_type == DOLLAR)
			is_success = expand_dollar(tokens, current, env_lst);
		else if (current->tk_type == TILDE)
			is_success = expand_tilde(current, env_lst);
		if (is_success == FAILURE)
			return (FAILURE);
		current = current->next;
	}
	return (SUCCESS);
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

t_parser	*parser(t_token **tokens, t_env *env_lst)
{
	t_parser	*parser;
	char		**exec;

	parser = (t_parser *)malloc(sizeof(t_parser));
	if (parser == NULL)
		return (NULL);
	init_parser(parser);
	expand_specials(tokens, env_lst);
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

int	main(int argc, char **argv, char **envp)
{
	t_token	*tokens;
	t_token	*tmp;
	t_env	*env_lst;
	char	*line;
	void	*ptr;

	(void)argc;
	(void)argv;
	env_lst = init_env_list(envp);
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
	ptr = parser(&tokens, env_lst);
//	printf("%s\n", (char *)ptr);
	free(line);
//	exit(1);
	free_token(tokens);
	return (0);
}
