/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipeline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitotak <keitotak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 14:56:57 by keitotak          #+#    #+#             */
/*   Updated: 2026/01/25 07:25:21 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"
#include "builtin.h"

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

int	nopipe_execute(t_command *command, t_env *env_lst, t_exec *top)
{
	pid_t	pid;

	if (is_builtin(command->command[0]) != ELSE)
	{
		redirect_fd(command);
		return (pass_to_builtin(command, env_lst, top));
	}
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		return (-1);
	}
	if (pid == 0)
	{
		redirect_fd(command);
		exec_command(command, env_lst, top);
	}
	return (wait_for_children(&pid, 1));
}

int	execute(t_command *command, t_env *env_lst, t_exec *top)
{
	int		proc_count;
	int		ret;

	proc_count = count_proc(command);
	if (proc_count == 1)
		ret = nopipe_execute(command, env_lst, top);
	else
		ret = pipeline(command, env_lst, proc_count, top);
	return (ret);
}
