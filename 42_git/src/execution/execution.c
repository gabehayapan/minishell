/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 11:06:32 by hanakamu          #+#    #+#             */
/*   Updated: 2026/01/08 19:22:36 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	execute_command(t_exec *exec_node, t_env *env_lst, char **envp)
{
	int	ret;

	if (exec_node == NULL)
		return (0);
	if (exec_node->tk_type == END || exec_node->tk_type == WORD)
		return (execute(exec_node->size_exec, exec_node->exec, envp));
	else if (exec_node->tk_type == AND)
	{
		ret = execute_command(exec_node->left, env_lst, envp);
		if (ret == 0)
			return (execute_command(exec_node->right, env_lst, envp));
		return (ret);
	}
	else if (exec_node->tk_type == OR)
	{
		ret = execute_command(exec_node->left, env_lst, envp);
		if (ret != 0)
			return (execute_command(exec_node->right, env_lst, envp));
		return (ret);
	}
	else if (exec_node->tk_type == SEMICOLON)
	{
		execute_command(exec_node->left,env_lst, envp);
		execute_command(exec_node->right, env_lst, envp);
		return (0);
	}
	return (1);
}

int	check_execution_success(t_exec *exec_tree, t_env *env_lst, char **envp)
{
	execute_command(exec_tree, env_lst, envp);
	return (SUCCESS);
}

//int	execute_command(t_exec *exec_node, t_env *env_lst)
//{
//	int	ret;
//
//	if (exec_node == NULL)
//		return (0);
//	if (exec_node->tk_type == END || exec_node->tk_type == WORD)
//		return (execute(exec_node, env_lst));
//	else if (exec_node->tk_type == AND)
//	{
//		ret = execute_command(exec_node->left);
//		if (ret == 0)
//			return (execute_command(exec_node->right));
//		return (ret);
//	}
//	else if (exec_node->tk_type == OR)
//	{
//		ret = execute_command(exec_node->left);
//		if (ret != 0)
//			return (execute_command(exec_node->right));
//		return (ret);
//	}
//	else if (exec_node->tk_type == SEMICOLON)
//	{
//		execute_command(exec_node->left);
//		execute_command(exec_node->right);
//		return (0);
//	}
//	return (1);
//}
//
//int	check_execution_success(t_exec *exec_tree, t_env *env_lst)
//{
//	execute_command(exec_tree, env_lst);
//	return (SUCCESS);
//}
