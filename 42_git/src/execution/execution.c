/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 11:06:32 by hanakamu          #+#    #+#             */
/*   Updated: 2026/01/14 09:49:58 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	execute_command(t_exec *exec_node, t_env *env_lst);

int	handle_ctrl_op(t_exec *exec_node, t_env *env_lst)
{
	int	ret;

	if (exec_node->tk_type == AND)
	{
		ret = execute_command(exec_node, env_lst);
		if (ret == 0)
			return (execute_command(exec_node, env_lst));
		return (ret);
	}
	else if (exec_node->tk_type == OR)
	{
		ret = execute_command(exec_node, env_lst);
		if (ret != 0)
			return (execute_command(exec_node, env_lst));
		return (ret);
	}
	else if (exec_node->tk_type == SEMI)
	{
		execute_command(exec_node, env_lst);
		execute_command(exec_node, env_lst);
		return (0);
	}
	return (1);
}

int	execute_command(t_exec *exec_node, t_env *env_lst)
{
	if (exec_node == NULL)
		return (0);
	if (exec_node->tk_type == END || exec_node->tk_type == WORD)
		return (execute(exec_node, env_lst));
	else
		return (handle_ctrl_op(exec_node, env_lst));
}

int	check_execution_success(t_exec *exec_tree, t_env *env_lst)
{
	execute_command(exec_tree, env_lst);
	return (SUCCESS);
}
