/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 11:06:32 by hanakamu          #+#    #+#             */
/*   Updated: 2026/02/01 08:20:31 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

unsigned char	execute_command(t_exec *exec_node, t_env **env_lst,
					t_to_free *to_free);

unsigned char	handle_ctrl_op(t_exec *exec_node, t_env **env_lst,
					t_to_free *to_free)
{
	int	ret;

	if (exec_node->tk_type == AND)
	{
		ret = execute_command(exec_node->left, env_lst, to_free);
		if (ret == 0)
			return (execute_command(exec_node->right, env_lst, to_free));
		return (ret);
	}
	else if (exec_node->tk_type == OR)
	{
		ret = execute_command(exec_node->left, env_lst, to_free);
		if (ret != 0)
			return (execute_command(exec_node->right, env_lst, to_free));
		return (ret);
	}
	else if (exec_node->tk_type == SEMI)
	{
		execute_command(exec_node->left, env_lst, to_free);
		return (execute_command(exec_node->right, env_lst, to_free));
	}
	return (1);
}

unsigned char	execute_command(t_exec *exec_node, t_env **env_lst,
					t_to_free *to_free)
{
	if (exec_node == NULL)
		return (0);
	if (exec_node->tk_type == END || exec_node->tk_type == WORD)
		return (execute(exec_node->command, env_lst, to_free));
	else
		return (handle_ctrl_op(exec_node, env_lst, to_free));
}
