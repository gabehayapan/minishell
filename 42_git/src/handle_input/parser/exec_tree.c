/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 18:27:01 by hanakamu          #+#    #+#             */
/*   Updated: 2026/01/14 18:25:02 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_exec	*set_last_node(t_exec *top, t_exec *node_exec)
{
	node_exec->tk_type = END;
	node_exec->left = NULL;
	node_exec->right = NULL;
	if (top != NULL)
	{
		top->right = node_exec;
		return (top);
	}
	else
		return (node_exec);
}

t_exec	*set_new_node(t_exec *node_exec, t_exec *ctrl_op_node)
{
	ctrl_op_node->left = node_exec;
	node_exec->tk_type = WORD;
	node_exec->left = NULL;
	node_exec->right = NULL;
	return (ctrl_op_node);
}

t_exec	*new_ctrl_op_node(t_token *token, t_exec *top)
{
	t_exec	*ctrl_op_node;

	ctrl_op_node = (t_exec *)malloc(sizeof(t_exec));
	if (ctrl_op_node == NULL)
		return (NULL);
	ctrl_op_node->tk_type = token->tk_type;
	ctrl_op_node->left = NULL;
	ctrl_op_node->right = NULL;
	if (top != NULL)
		top->right = ctrl_op_node;
	return (ctrl_op_node);
}

t_exec	*set_exec_elem(t_token **tokens, t_exec *top, t_exec *node_exec)
{
	t_exec	*ctrl_op_node;

	ctrl_op_node = NULL;
	if (*tokens != NULL)
	{
		ctrl_op_node = new_ctrl_op_node(*tokens, top);
		if (ctrl_op_node == NULL)
			return (NULL);
		clear_token(tokens, *tokens, free);
	}
	if (ctrl_op_node == NULL)
		return (set_last_node(top, node_exec));
	else
		return (set_new_node(node_exec, ctrl_op_node));
}
