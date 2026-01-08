/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitotak <keitotak@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 12:07:47 by keitotak          #+#    #+#             */
/*   Updated: 2025/12/06 16:39:52 by keitotak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	init_pipex(t_pipex *p, char **av)
{
	p->infile = av[0];
	p->cmd1 = av[1];
	p->cmd2 = av[2];
	p->outfile = av[3];
	p->i_fd = -1;
	p->o_fd = -1;
	p->p_fd[0] = -1;
	p->p_fd[1] = -1;
	p->pid1 = -1;
	p->pid2 = -1;
}

int	pipex(char **av, char **ev)
{
	t_pipex	p;

	init_pipex(&p, av);
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
