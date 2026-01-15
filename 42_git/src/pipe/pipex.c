/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitotak <keitotak@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 12:07:47 by keitotak          #+#    #+#             */
/*   Updated: 2026/01/15 19:34:50 by keitotak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	init_pipex(t_pipex *p, t_command *command)
{
	p->infile = (command->inrdt)->rdt;
	p->cmd1 = command->command;
	p->cmd2 = (command->next)->command;
	p->outfile = ((command->next)->outrdt)->rdt;
	p->i_fd = -1;
	p->o_fd = -1;
	p->p_fd[0] = -1;
	p->p_fd[1] = -1;
	p->pid1 = -1;
	p->pid2 = -1;
}

int	pipex(t_command *command, char **ev, int count)
{
	t_pipex	p;

	(void) count;
	init_pipex(&p, command);
	if (pipe(p.p_fd) == error)
	{
		perror("pipe");
		return (EXIT_FAILURE);
	}
	p.pid1 = fork_process(&p, ev, 1);
	p.pid2 = fork_process(&p, ev, 2);
	close(p.p_fd[0]);
	close(p.p_fd[1]);
	return (wait_for_children(&p));
}

/*
int	pipex(t_command *command, char **ev, int count)
{
	int	pfd[count - 1][2];
	int	i;

	i = 0;
	while (i < count)
	{
		if (i - 1 < count)
		{
			if (pipe(pfd[i]) == error)
			{
				perror("pipe");
				return (EXIT_FAILURE);
			}
		}

	}
}
*/
