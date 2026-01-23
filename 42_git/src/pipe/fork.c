/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitotak <keitotak@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 16:20:31 by keitotak          #+#    #+#             */
/*   Updated: 2026/01/24 01:16:02 by keitotak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"

int	redirect_pipe(t_pipe *p, t_command *command, int p_nbr)
{
	if (command->next)
	{
		if (dup2(p->pipefd[2 * p_nbr + 1], STDOUT_FILENO) < 0)
		{
			perror("dup2");
			return (EXIT_FAILURE);
		}
	}
	if (p_nbr)
	{
		if (dup2(p->pipefd[2 * (p_nbr - 1)], STDIN_FILENO) < 0)
		{
			perror("dup2");
			return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}

int	fork_process(t_pipe *p, t_command *command, t_env *env_lst, int p_nbr, t_exec *top)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		close_pipes(p->pipefd, p_nbr);
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		if (redirect_pipe(p, command, p_nbr) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		redirect_fd(command);
		close_pipes(p->pipefd, p_nbr);
		exec_command(command, env_lst, top);
	}
	return (pid);
}
