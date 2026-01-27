/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_nodes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 08:24:51 by hanakamu          #+#    #+#             */
/*   Updated: 2026/01/26 17:48:45 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

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
