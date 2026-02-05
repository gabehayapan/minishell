/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 11:06:32 by hanakamu          #+#    #+#             */
/*   Updated: 2026/02/05 14:41:31 by keitotak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

unsigned char	execute_command(t_exec *exec_node, t_env **env_lst,
					t_to_free *to_free);

int	count_proc(t_command *command)
{
	int	count;

	count = 0;
	while (command)
	{
		count++;
		command = command->next;
	}
	return (count);
}

int	execute(t_command *command, t_env **env_lst, t_to_free *to_free)
{
	int		proc_count;
	int		ret;

	command->stdfd[0] = dup(STDIN_FILENO);
	command->stdfd[1] = dup(STDOUT_FILENO);
	proc_count = count_proc(command);
	if (proc_count == 1)
		ret = nopipe_execute(command, env_lst, to_free);
	else
		ret = pipeline(command, env_lst, proc_count, to_free);
	close(command->stdfd[0]);
	close(command->stdfd[1]);
	return (ret);
}

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
