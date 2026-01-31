/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitotak <keitotak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 14:56:57 by keitotak          #+#    #+#             */
/*   Updated: 2026/01/31 19:27:57 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"
#include "builtin.h"

int	default_signal(void);

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

int	nopipe_builtin(t_command *command, t_env **env_lst, t_exec *top, t_his *his)
{
	int	stdin_fd;
	int	stdout_fd;
	int	exit_code;

	stdin_fd = dup(STDIN_FILENO);
	stdout_fd = dup(STDOUT_FILENO);
	if (redirect_fd(command) == FAILURE)
		return (FAILURE);
	exit_code = pass_to_builtin(command, env_lst, top, his);
	dup2(stdin_fd, STDIN_FILENO);
	dup2(stdout_fd, STDOUT_FILENO);
	close(stdin_fd);
	close(stdout_fd);
	return (exit_code);
}

int	nopipe_execute(t_command *command, t_env **env_lst, t_exec *top, t_his *his)
{
	pid_t	pid;

	if (is_builtin(command->command[0]) != ELSE)
		return (nopipe_builtin(command, env_lst, top, his));
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		return (-1);
	}
	if (pid == 0)
	{
		if (default_signal() == EXIT_FAILURE)
			exit(EXIT_FAILURE);
		if (redirect_fd(command) == EXIT_FAILURE)
			exit(EXIT_FAILURE);
		exec_command(command, env_lst, top, his);
	}
	return (wait_for_children(&pid, 1));
}

int	execute(t_command *command, t_env **env_lst, t_exec *top, t_his *his)
{
	int		proc_count;
	int		ret;

	proc_count = count_proc(command);
	if (proc_count == 1)
		ret = nopipe_execute(command, env_lst, top, his);
	else
		ret = pipeline(command, env_lst, proc_count, top, his);
	return (ret);
}
