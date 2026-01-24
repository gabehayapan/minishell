/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 14:23:21 by hanakamu          #+#    #+#             */
/*   Updated: 2026/01/24 18:33:27 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	init_node_exec(t_exec *node_exec)
{
	node_exec->left = NULL;
	node_exec->right = NULL;
	node_exec->command = NULL;
	node_exec->next = NULL;
}

void	init_command(t_command *command, int subshell)
{
	command->inrdt = NULL;
	command->outrdt = NULL;
	command->command = NULL;
	command->is_subshell = subshell;
	command->next = NULL;
}
