/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 09:28:01 by hanakamu          #+#    #+#             */
/*   Updated: 2026/01/14 16:38:06 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	get_remaining_tokens(t_token **tokens)
{
	while (*tokens != NULL
		&& (*tokens)->tk_type != AND && (*tokens)->tk_type != OR
		&& (*tokens)->tk_type != SEMI && (*tokens)->tk_type != PIPE)
		clear_token(tokens, *tokens, free);
	if (*tokens != NULL && (*tokens)->tk_type == PIPE)
		clear_token(tokens, *tokens, free);
}

//int	get_execution(t_token **tokens, char **exec, size_t size)
//{
//	size_t	len_command;
//	size_t	i;
//
//	len_command = get_len_command(*tokens);
//	i = 1;
//	while (*tokens != NULL
//		&& (*tokens)->tk_type != AND && (*tokens)->tk_type != OR
//		&& (*tokens)->tk_type != SEMI && (*tokens)->tk_type != PIPE)
//	{
//		*(exec + i) = (char *)ft_calloc(len_command, sizeof(char));
//		if (*(exec + i) == NULL)
//		{
//			while (i--)
//				free(*(exec + i));
//			free(*(exec + size - 1));
//			return (FAILURE);
//		}
//		get_command(*(exec + i), *tokens);
//		get_remaining_tokens(tokens);
//		i++;
//	}
//	return (SUCCESS);
//}
//
//char	**new_exec(t_token **tokens, t_exec *node_exec, t_env *env_lst)
//{
//	char		**exec;
//	t_size_exec	size;
//	int			is_success;
//
//	size = count_array_size(*tokens, node_exec);
//	exec = (char **)malloc(sizeof(char *) * size);
//	if (exec == NULL)
//		return (NULL);
//	is_success = get_redirect_file(tokens, exec, size);
//	if (is_success == FAILURE)
//	{
//		free(exec);
//		return (NULL);
//	}
//	is_success = add_path_to_command(*tokens, env_lst);
//	if (is_success == FAILURE)
//	{
//		free(exec); // need to free infile and outfile
//		return (NULL);
//	}
//	is_success = get_execution(tokens, exec, size);
//	if (is_success == FAILURE)
//	{
//		free(exec); // need to free infile and outfile
//		return (NULL);
//	}
//	node_exec->size_exec = size;
//	return (exec);
//}

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

t_size_exec	count_size_exec(t_token *tokens)
{
	t_size_exec	size;

	size.inrdt = 0;
	size.outrdt = 0;
	while (tokens != NULL && tokens->tk_type != AND && tokens->tk_type != OR
		&& tokens->tk_type != SEMI && tokens->tk_type != PIPE)
	{
		if (tokens->tk_type == SGL_INRDT || tokens->tk_type == DBL_INRDT)
			size.inrdt = size.inrdt + 1;
		else if (tokens->tk_type == SGL_OUTRDT || tokens->tk_type == DBL_OUTRDT)
			size.outrdt = size.outrdt + 1;
		tokens = tokens->next;
	}
	return (size);
}

t_rdt_type	get_rdt_type(t_token *token)
{
	if (token->tk_type == SGL_INRDT)
		return (INFILE);
	else if (token->tk_type == SGL_OUTRDT)
		return (OUTFILE);
	else if (token->tk_type == DBL_INRDT)
		return (HEREDOC);
	else
		return (APPEND);
}

void	add_last(t_rdt **head, t_rdt *new_rdt)
{
	t_rdt	*last;

	last = *head;
	while (last != NULL && last->next != NULL)
		last = last->next;
	last->next = new_rdt;
}

void	no_rdt_file(t_token *token)
{
	char	*missing_rdt;

	if (token->tk_type == SGL_INRDT)
		missing_rdt = "<";
	else if (token->tk_type == SGL_OUTRDT)
		missing_rdt = ">";
	else if (token->tk_type == DBL_INRDT)
		missing_rdt = "<<";
	else
		missing_rdt = ">>";
	ft_dprintf(2, "minishell: syntax error after \'%s\'\n", missing_rdt);
}

int	new_rdt_node(t_token *current, t_rdt **head)
{
	t_rdt	*new_rdt;

	if (current->next == NULL)
	{
		no_rdt_file(current);
		return (SUCCESS);
	}
	new_rdt = (t_rdt *)malloc(sizeof(t_rdt));
	if (new_rdt == NULL)
		return (FAILURE);
	new_rdt->rdt = (current->next)->word;
	new_rdt->type = get_rdt_type(current);
	new_rdt->next = NULL;
	if (*head == NULL)
		*head = new_rdt;
	else
		add_last(head, new_rdt);
	return (SUCCESS);
}

void	free_rdt(t_rdt *rdt)
{
	t_rdt	*next;

	while (rdt != NULL)
	{
		next = rdt->next;
		free(rdt->rdt);
		free(rdt);
		rdt = next;
	}
}

int	get_in_out_rdt(t_token **tokens, t_command *command)
{
	t_rdt	*head_in;
	t_rdt	*head_out;
	t_token	*current;

	head_in = NULL;
	head_out = NULL;
	current = *tokens;
	while (current != NULL && current->tk_type != AND && current->tk_type != OR
		&& current->tk_type != SEMI && current->tk_type != PIPE)
	{
		if (current->tk_type == SGL_INRDT || current->tk_type == DBL_INRDT)
		{
			if (new_rdt_node(current, &head_in) == FAILURE)
			{
				free_rdt(head_in);
				return (FAILURE);
			}
			clear_token(tokens, current->next, NULL);
			clear_token(tokens, current, free);
		}
		if (current->tk_type == SGL_OUTRDT || current->tk_type == DBL_OUTRDT)
		{
			if (new_rdt_node(current, &head_out) == FAILURE)
			{
				free_rdt(head_in);
				return (FAILURE);
			}
			clear_token(tokens, current->next, NULL);
			clear_token(tokens, current, free);
		}
		current = current->next;
	}
	command->inrdt = head_in;
	command->outrdt = head_out;
	return (SUCCESS);
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
	command->next = NULL;
}

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

//int	new_exec_tree(t_token **tokens, t_exec **top, t_env *env_lst)
//{
//	t_exec	*node_exec;
//
//	node_exec = (t_exec *)malloc(sizeof(t_exec));
//	if (node_exec == NULL)
//		return (FAILURE);
//	init_node_exec(node_exec);
//	node_exec->exec = new_exec(tokens, node_exec, env_lst);
//	if (node_exec->exec == NULL)
//		return (FAILURE);
//	*top = set_exec_elem(tokens, *top, node_exec);
//	if (*top == NULL)
//		return (FAILURE);
//	return (SUCCESS);
//}

t_exec	*parser(t_token **tokens, t_env *env_lst)
{
	t_exec	*top;
	int		is_success;

	top = NULL;
	expand_specials(tokens, env_lst);
//	is_success = add_path_command(*tokens, env_lst);
//	if (is_success == FAILURE)
//		return (NULL);
	while (*tokens != NULL)
	{
		is_success = new_exec_tree(tokens, &top, env_lst);
		if (is_success == FAILURE)
			return (NULL);
	}
	return (top);
}
