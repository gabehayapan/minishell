/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 08:20:41 by hanakamu          #+#    #+#             */
/*   Updated: 2026/01/31 17:05:10 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_exec	*add_exec_tree_branch(t_exec **top, t_exec *current, t_exec **target,
			int subshell);

t_exec	*exec_tree_term(t_exec *top, t_exec *term, t_exec **target)
{
	*target = NULL;
	if (term == NULL)
		return (top);
	else
		return (term);
}

void	handle_same_layer(t_exec **top, t_exec *current, t_exec **target,
			int subshell)
{
	current->left = *top;
	*top = current;
	current->right = current->next;
	add_exec_tree_branch(top, (current->next)->next, target,
		subshell);
	while (*target != NULL && (*target)->next != NULL)
		add_exec_tree_branch(top, *target, target,
			(((*target)->next)->command)->is_subshell);
}

t_exec	*add_exec_tree_branch(t_exec **top, t_exec *current, t_exec **target,
			int subshell)
{
	t_exec	*top_sub;

	if (current == NULL || current->next == NULL)
		return (exec_tree_term(*top, current, target));
	if (((current->next)->command)->is_subshell == subshell)
	{
		handle_same_layer(top, current, target, subshell);
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
