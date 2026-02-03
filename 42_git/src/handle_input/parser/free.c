/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 19:08:02 by hanakamu          #+#    #+#             */
/*   Updated: 2026/02/03 11:42:08 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

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

	if (strs == NULL)
		return ;
	ptr_strs = strs;
	while (*strs != NULL)
	{
		free(*strs);
		strs++;
	}
	free(ptr_strs);
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

void	free_node_exec(t_exec *node_exec)
{
	if (node_exec == NULL)
		return ;
	free_node_exec(node_exec->left);
	free_node_exec(node_exec->right);
	free_command(node_exec->command);
	free(node_exec);
}

void	free_his(t_his *his)
{
	t_his	*next;

	while (his != NULL)
	{
		next = his->next;
		free(his->line);
		free(his);
		his = next;
	}
}
