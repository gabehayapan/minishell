/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitotak <keitotak@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 16:20:31 by keitotak          #+#    #+#             */
/*   Updated: 2026/01/19 17:50:13 by keitotak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

#define IORDT 0
#define INRDT 1
#define OUTRDT 2
#define NORMAL 3

int	proctype(t_command *command)
{
	if (command->inrdt && command->outrdt)
		return (IORDT);
	else if (command->inrdt)
		return (INRDT);
	else if (command->outrdt)
		return (OUTRDT);
	else
		return (NORMAL);
}

int	nordt_child(t_pipe *p, t_command *command, char **ev, int p_nbr)
{
	if (p_nbr == 0)
		close(p->pipefd[p_nbr][])

}

int	fork_process(t_pipe *p, t_command *command, char **ev, int p_nbr)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		close(p->pipefd[p_nbr][0]);
		close(p->pipefd[p_nbr][1]);
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		redirect_fd(command);
	}
	return (pid);
}
