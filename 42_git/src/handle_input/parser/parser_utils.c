/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 14:23:21 by hanakamu          #+#    #+#             */
/*   Updated: 2026/01/14 14:21:24 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	init_node_exec(t_exec *node_exec)
{
	node_exec->left = NULL;
	node_exec->right = NULL;
	node_exec->exec = NULL;
	node_exec->size_exec = 0;
	node_exec->num_heredoc = 0;
	node_exec->num_infile = 0;
	node_exec->num_command = 0;
	node_exec->num_outfile = 0;
	node_exec->is_append = 0;
	node_exec->is_subshell = 0;
}

void	free_strs(char **strs, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		free(strs[i]);
		i++;
	}
	free(strs);
}

void	free_null_term_strs(char **strs)
{
	char	**ptr_strs;

	ptr_strs = strs;
	while (*strs != NULL)
	{
		free(*strs);
		strs++;
	}
	free(ptr_strs);
}

void	free_node_exec(t_exec *node_exec)
{
	if (node_exec == NULL)
		return ;
	free_node_exec(node_exec->left);
	free_node_exec(node_exec->right);
	free_strs(node_exec->exec, node_exec->size_exec);
	free(node_exec);
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
