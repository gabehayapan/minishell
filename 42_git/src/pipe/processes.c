/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitotak <keitotak@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 16:20:31 by keitotak          #+#    #+#             */
/*   Updated: 2026/01/16 16:20:33 by keitotak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

#define NORMAL 0
#define INRDT 1
#define OUTRDT 2

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
		if (proctype(command) == NORMAL)
			nordt_child(p, command, ev, p_nbr);
		else if (proctype(command) == INRDT)
			inrdt_child();
		else if (proctype(command) == OUTRDT)
			outrdt_child();
		else
			iordt_child();
	}
	return (pid);
}
