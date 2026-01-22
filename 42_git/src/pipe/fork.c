/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitotak <keitotak@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 16:20:31 by keitotak          #+#    #+#             */
/*   Updated: 2026/01/22 20:22:40 by keitotak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"

int	fork_process(t_pipe *p, t_command *command, char **ev, int p_nbr)
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
		redirect_fd(command);
		close_pipes(p->pipefd, p_nbr);
		exec_command(command->command, ev);
	}
	else if (pid < 0)
	{
		perror("error");
		return (EXIT_FAILURE);
	}
	return (pid);
}
