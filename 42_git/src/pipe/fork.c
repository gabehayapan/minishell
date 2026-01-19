/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitotak <keitotak@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 16:20:31 by keitotak          #+#    #+#             */
/*   Updated: 2026/01/19 19:47:29 by keitotak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"

int	pipe_connect(t_pipe *p, t_command *command, int p_nbr)
{
	int	infd;
	int	outfd;

	infd = STDIN_FILENO;
	outfd = STDOUT_FILENO;
	if (p_nbr)
		close(p->pipefd[p_nbr - 1][1]);
	close(p->pipefd[p_nbr][0]);
	if (command->infd)
		infd = command->infd;
	else if (p_nbr)
		infd = p->pipefd[p_nbr - 1][0];
	if (infd > 2)
		dup2(infd, STDIN_FILENO);
	if (command->outfd)
		outfd = command->outfd;
	else if(command->next)
		outfd = p->pipefd[p_nbr][1];
	if (outfd > 2)
		dup2(outfd, STDOUT_FILENO);
	return (SUCCESS);
}

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
		redirect_fd(command);
		if (command->next)
			pipe_connect(p, command, p_nbr);
		exec_command(command->command, ev);
	}
	return (pid);
}
