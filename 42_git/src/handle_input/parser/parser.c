/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 09:28:01 by hanakamu          #+#    #+#             */
/*   Updated: 2026/01/25 08:17:40 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <stdbool.h>

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
		if (join_command(tokens, current, command, &next) == FAILURE)
		{
			free_strs(ret, command - ret);
			return (NULL);
		}
		command++;
		current = next;
	}
	*command = NULL;
	return (ret);
}

int	new_command(t_token **tokens, t_command *command, t_env *env_lst)
{
	int			is_success;

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

int	check_opening_parenthesis(t_token **tokens, int *subshell)
{
	t_token	*current;

	while (*tokens != NULL && (*tokens)->tk_type == O_PAREN)
	{
		*subshell = *subshell + 1;
		clear_token (tokens, *tokens, free);
	}
	current = *tokens;
	while (current != NULL && current->tk_type != AND && current->tk_type != OR
		&& current->tk_type != SEMI && current->tk_type != PIPE)
	{
		if (current->tk_type == O_PAREN
			|| (current->tk_type == C_PAREN && *subshell == 0))
		{
			if (current->tk_type == O_PAREN)
				ft_dprintf(2, "minishell: syntax error near `('\n");
			else
				ft_dprintf(2, "minishell: syntax error near `)'\n");
			return (FAILURE);
		}
		current = current->next;
	}
	return (SUCCESS);
}

void	check_closing_parenthesis(t_token **tokens, int *subshell)
{
	t_token	*current;

	current = *tokens;
	while (current != NULL && current->tk_type != AND && current->tk_type != OR
		&& current->tk_type != SEMI && current->tk_type != PIPE)
	{
		if (current->tk_type == C_PAREN)
		{
			*subshell = *subshell - 1;
			clear_token(tokens, current, free);
		}
		current = current->next;
	}
}

int	initialize_command(t_token **tokens, t_command *current, int *subshell)
{
	int	is_success;

	is_success = check_opening_parenthesis(tokens, subshell);
	if (is_success == FAILURE)
		return (FAILURE);
	init_command(current, *subshell);
	check_closing_parenthesis(tokens, subshell);
	return (SUCCESS);
}

int	get_piped_command(t_token **tokens, t_command **command, t_env *env_lst)
{
	t_command	*current;
	t_command	*last;
	static int	subshell;

	last = NULL;
	while (*tokens != NULL
		&& (*tokens)->tk_type != AND && (*tokens)->tk_type != OR
		&& (*tokens)->tk_type != SEMI)
	{
		current = (t_command *)malloc(sizeof(t_command));
		if (current == NULL)
			return (FAILURE);
		if (initialize_command(tokens, current, &subshell) == FAILURE)
			return (FORMAT_ERROR);
		if (new_command(tokens, current, env_lst) == FAILURE)
		{
			free_command(*command);
			return (FAILURE);
		}
		add_new_command(command, current, &last);
		if (*tokens != NULL && (*tokens)->tk_type == PIPE)
			clear_token(tokens, *tokens, free);
	}
	return (SUCCESS);
}

void	add_back_node(t_exec **head, t_exec *node_exec)
{
	t_exec	*last;

	if (*head == NULL)
		*head = node_exec;
	else
	{
		last = *head;
		while (last != NULL && last->next != NULL)
			last = last->next;
		last->next = node_exec;
	}
}

t_exec	*new_ctrl_node(t_token *token)
{
	t_exec	*ctrl_node;

	ctrl_node = (t_exec *)malloc(sizeof(t_exec));
	if (ctrl_node == NULL)
		return (NULL);
	ctrl_node->tk_type = token->tk_type;
	ctrl_node->left = NULL;
	ctrl_node->right = NULL;
	ctrl_node->command = NULL;
	ctrl_node->next = NULL;
	return (ctrl_node);
}

int	add_exec_node(t_token **tokens, t_exec **head, t_exec *node_exec)
{
	t_exec	*new_ctrl;

	add_back_node(head, node_exec);
	if (*tokens != NULL)
	{
		new_ctrl = new_ctrl_node(*tokens);
		if (new_ctrl == NULL)
			return (FAILURE);
		clear_token(tokens, *tokens, free);
		node_exec->next = new_ctrl;
	}
	return (SUCCESS);
}

int	new_exec_tree(t_token **tokens, t_exec **head, t_env *env_lst)
{
	t_exec	*node_exec;
	int		ret;

	node_exec = (t_exec *)malloc(sizeof(t_exec));
	if (node_exec == NULL)
		return (FAILURE);
	init_node_exec(node_exec);
	ret = get_piped_command(tokens, &node_exec->command, env_lst);
	if (ret == FAILURE || ret == FORMAT_ERROR)
	{
		free(node_exec);
		return (ret);
	}
	ret = add_exec_node(tokens, head, node_exec);
	return (ret);
}

t_exec	*add_exec_tree_branch(t_exec **top, t_exec *current, t_exec **target,
			int subshell)
{
	t_exec	*top_sub;

	if (current == NULL)
	{
		*target = NULL;
		return (*top);
	}
	else if (current->next == NULL)
	{
		*target = NULL;
		return (current);
	}
	if (((current->next)->command)->is_subshell == subshell)
	{
		current->left = *top;
		*top = current;
		current->right = current->next;
		add_exec_tree_branch(top, (current->next)->next, target,
				subshell);
		while (*target != NULL && (*target)->next != NULL)
			add_exec_tree_branch(top, *target, target,
				(((*target)->next)->command)->is_subshell);
		return (*top);
	}
	else if (((current->next)->command)->is_subshell > subshell)
	{
		current->left = *top;
		*top = current;
		top_sub = current->next;
		current->right = add_exec_tree_branch(&top_sub, (current->next)->next,
				target, (((*top)->next)->command)->is_subshell);
		return (add_exec_tree_branch(top, *target, target, subshell));
	}
	else
	{
		*target = current;
		return (*top);
	}
}

t_exec	*create_exec_ast(t_exec *head)
{
	t_exec	*top;
	t_exec	*target;

	top = head;
	target = head;
	if (head != NULL)
		add_exec_tree_branch(&top, head->next, &target,
			(head->command)->is_subshell);
	return (top);
}

int	parser(t_token **tokens, t_env *env_lst, t_exec **exec_tree,
			long exit_status)
{
	t_exec	*head;
	int		is_success;

	while (*tokens != NULL && (*tokens)->tk_type == SPACES)
		clear_token(tokens, *tokens, free);
	if (*tokens == NULL)
		return (NO_COMMAND);
	head = NULL;
	is_success = check_assignment(tokens, env_lst);
	if (is_success == FAILURE)
		return (FAILURE);
	is_success = expand_specials(tokens, env_lst, exit_status);
	if (is_success == FAILURE)
		return (FAILURE);
	remove_tk_spaces(tokens);
	while (*tokens != NULL)
	{
		is_success = new_exec_tree(tokens, &head, env_lst);
		if (is_success == FAILURE || is_success == FORMAT_ERROR)
			return (is_success);
	}
	*exec_tree = create_exec_ast(head);
	return (SUCCESS);
}
