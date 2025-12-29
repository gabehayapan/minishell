/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 09:28:01 by hanakamu          #+#    #+#             */
/*   Updated: 2025/12/29 14:28:13 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

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

char	**create_exec(t_token **tokens, t_parser *parser)
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
	for (int i = 0; i < size; i++)
	{
		if (i == 0 || i == size - 1)
			printf("%s\n", exec[i]);
		else
			printf("%s", exec[i]);
	}
	return (exec);
}

t_parse	*parser(t_token **tokens)
{
	t_parser	*parser;

	parser = (t_parser *)malloc(sizeof(t_parser));
	if (parser == NULL)
		return (NULL);
	init_parser(parser);
	parser->exec_tree = (t_exec *)malloc(sizeof(t_exec));
	if (parser->exec_tree == NULL)
	{
		free(parser);
		return (NULL);
	}
	(parser->exec_tree)->exec = create_exec(tokens, parser);
	if ((parser->exec_tree)->exec == NULL)
	{
		free(parser);
		return (NULL);
	}
	return (parser);
}

//int	main(void)
//{
//	t_token	*tokens;
//	t_token	*tmp;
//	char	*line;
//	void	*ptr;
//
//	line = readline("prompt> ");
//	printf("line:%s\n", line);
//	tokens = tokenizer(line);
//	if (tokens == NULL)
//	{
//		printf("error at tokenizer\n");
//		return (1);
//	}
//	tmp = tokens;
//	while (tmp != NULL)
//	{
//		printf("word:%s, token type:%d\n", tmp->word, tmp->tk_type);
//		tmp = tmp->next;
//	}
//	ptr = parser(&tokens);
////	printf("%s\n", (char *)ptr);
//	free(line);
////	exit(1);
//	free_token(tokens);
//	return (0);
//}
