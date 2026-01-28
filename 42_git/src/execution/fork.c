/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitotak <keitotak@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 16:20:31 by keitotak          #+#    #+#             */
/*   Updated: 2026/01/29 07:42:35 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"

int	default_signal(void);

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

int	fork_process(t_pipe *p, t_command *command, int p_nbr)
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
		if (default_signal() == EXIT_FAILURE)
			exit(EXIT_FAILURE);
		if (redirect_pipe(p, command, p_nbr) == EXIT_FAILURE)
			exit(EXIT_FAILURE);
		if (redirect_fd(command) == EXIT_FAILURE)
			exit(EXIT_FAILURE);
		close_pipes(p->pipefd, p_nbr);
		exec_command(command, p->env_lst, p->top);
	}
	return (pid);
}
