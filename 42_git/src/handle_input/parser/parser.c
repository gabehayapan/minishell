/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 09:28:01 by hanakamu          #+#    #+#             */
/*   Updated: 2026/01/08 20:21:22 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

size_t	get_len_command(t_token *tokens)
{
	size_t	len_command;
	size_t	i;

	len_command = 0;
	while (tokens != NULL && tokens->tk_type != AND && tokens->tk_type != OR
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

int	get_execution(char **exec, size_t size, t_token **tokens)
{
	size_t	len_command;
	size_t	i;

	len_command = get_len_command(*tokens);
	i = 1;
	while (*tokens != NULL
		&& (*tokens)->tk_type != AND && (*tokens)->tk_type != OR
		&& (*tokens)->tk_type != SEMICOLON && (*tokens)->tk_type != PIPE)
	{
		*(exec + i) = (char *)ft_calloc(len_command + 2, sizeof(char));
		if (*(exec + i) == NULL)
		{
			while (i--)
				free(*(exec + i));
			free(*(exec + size - 1));
			return (FAILURE);
		}
		get_command(*(exec + i), *tokens);
		while (*tokens != NULL
			&& (*tokens)->tk_type != AND && (*tokens)->tk_type != OR
			&& (*tokens)->tk_type != SEMICOLON && (*tokens)->tk_type != PIPE)
			clear_token(tokens, *tokens, free);
		if (*tokens != NULL && (*tokens)->tk_type == PIPE)
			clear_token(tokens, *tokens, free);
		i++;
	}
	return (SUCCESS);
}

char	**new_exec(t_token **tokens, t_exec *node_exec)
{
	char	**exec;
	size_t	size;
	int		is_success;

	size = count_array_size(*tokens, node_exec);
	exec = (char **)malloc(sizeof(char *) * size);
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
	node_exec->size_exec = size;
	return (exec);
}

t_exec	*parser(t_token **tokens, t_env *env_lst)
{
	t_exec	*top;
	int		is_success;

	top = NULL;
	expand_specials(tokens, env_lst);
	while(*tokens != NULL)
	{
		is_success = new_exec_tree(tokens, &top);
		if (is_success == FAILURE)
			return (NULL);
	}
	return (top);
}
