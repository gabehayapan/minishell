/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 09:28:01 by hanakamu          #+#    #+#             */
/*   Updated: 2026/01/14 18:00:34 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	free_command(t_command *command)
{
	t_command	*next;

	while (command != NULL)
	{
		next = command->next;
		free_rdt(command->inrdt);
		free_rdt(command->outrdt);
		free_null_term_strs(command->command);
		free(command);
		command = next;
	}
}

void	get_remaining_tokens(t_token **tokens)
{
	while (*tokens != NULL
		&& (*tokens)->tk_type != AND && (*tokens)->tk_type != OR
		&& (*tokens)->tk_type != SEMI && (*tokens)->tk_type != PIPE)
		clear_token(tokens, *tokens, free);
	if (*tokens != NULL && (*tokens)->tk_type == PIPE)
		clear_token(tokens, *tokens, free);
}

size_t	get_size_command(t_token *tokens)
{
	size_t	counter;

	counter = 0;
	while (tokens != NULL && tokens->tk_type != AND && tokens->tk_type != OR
		&& tokens->tk_type != SEMI && tokens->tk_type != PIPE)
	{
		counter = counter + 1;
		tokens = tokens->next;
	}
	return (counter);
}

char	**get_execution(t_token **tokens)
{
	size_t	size_cmd;
	char	**command;
	char	**ret;
	t_token	*current;
	t_token	*next;

	size_cmd = get_size_command(*tokens);
	command = (char **)malloc(sizeof(char *) * (size_cmd + 1));
	if (command == NULL)
		return (NULL);
	ret = command;
	current = *tokens;
	while (current != NULL && current->tk_type != AND && current->tk_type != OR
		&& current->tk_type != SEMI && current->tk_type != PIPE)
	{
		next = current->next;
		*command = current->word;
		clear_token(tokens, current, NULL);
		command++;
		current = next;
	}
	return (ret);
}

int	new_command(t_token **tokens, t_command *command, t_env *env_lst)
{
	int			is_success;

	command->size = count_size_exec(*tokens);
	is_success = get_in_out_rdt(tokens, command);
	if (is_success == FAILURE)
		return (FAILURE);
	is_success = add_path_to_command(*tokens, env_lst);
	if (is_success == FAILURE)
		return (FAILURE);
	command->command = get_execution(tokens);
	if (command->command == NULL)
		return (FAILURE);
	return (SUCCESS);
}

void	init_command(t_command *command)
{
	command->inrdt = NULL;
	command->outrdt = NULL;
	command->command = NULL;
	command->is_subshell = 0;
	command->next = NULL;
}

t_command	*get_piped_command(t_token **tokens, t_env *env_lst)
{
	t_command	head;
	t_command	*current;
	t_command	*last;

	head.next = NULL;
	last = NULL;
	while (*tokens != NULL
		&& (*tokens)->tk_type != AND && (*tokens)->tk_type != OR
		&& (*tokens)->tk_type != SEMI)
	{
		current = (t_command *)malloc(sizeof(t_command));
		if (current == NULL)
			return (NULL);
		init_command(current);
		if (new_command(tokens, current, env_lst) == FAILURE)
		{
			free_command(head.next);
			return (NULL);
		}
		if (head.next == NULL)
			head.next = current;
		else
			last->next = current;
		last = current;
		if (*tokens != NULL && (*tokens)->tk_type == PIPE)
			clear_token(tokens, *tokens, free);
	}
	return (head.next);
}

int	new_exec_tree(t_token **tokens, t_exec **top, t_env *env_lst)
{
	t_exec	*node_exec;

	node_exec = (t_exec *)malloc(sizeof(t_exec));
	if (node_exec == NULL)
		return (FAILURE);
	init_node_exec(node_exec);
	node_exec->command = get_piped_command(tokens, env_lst);
	if (node_exec->command == NULL)
		return (FAILURE);
	*top = set_exec_elem(tokens, *top, node_exec);
	if (*top == NULL)
		return (FAILURE);
	return (SUCCESS);
}

t_exec	*parser(t_token **tokens, t_env *env_lst)
{
	t_exec	*top;
	int		is_success;

	top = NULL;
	expand_specials(tokens, env_lst);
	while (*tokens != NULL)
	{
		is_success = new_exec_tree(tokens, &top, env_lst);
		if (is_success == FAILURE)
			return (NULL);
	}
	return (top);
}
