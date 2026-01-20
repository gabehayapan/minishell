/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitotak <keitotak@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 17:14:01 by keitotak          #+#    #+#             */
/*   Updated: 2026/01/20 17:49:51 by keitotak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"

int	*init_procid(int count)
{
	int	*procid;
	int	i;

	procid = (int *)malloc(count * sizeof(int));
	if (procid == NULL)
		return (NULL);
	i = 0;
	while (i < count)
		procid[i++] = -1;
	return (procid);
}

void	free_pipefd(int **pipefd)
{
	int	**tmp;

	tmp = pipefd;
	while (*pipefd)
		free(*pipefd++);
	free(tmp);
}

int	**init_pipefd(int count)
{
	int	**pipefd;
	int	i;

	pipefd = (int **)malloc((count + 1) * sizeof(int *));
	if (pipefd == NULL)
		return (NULL);
	i = 0;
	while (i < count)
	{
		pipefd[i] = (int *)malloc(2 * sizeof(int));
		if (pipefd[i] == NULL)
			return (free_pipefd(pipefd), NULL);
		pipefd[i][0] = -1;
		pipefd[i][1] = -1;
		i++;
	}
	pipefd[i] = NULL;
	return (pipefd);
}

int	init_pipe(t_pipe *p, int count)
{
	p->procid = init_procid(count);
	if (p->procid == NULL)
		return (FAILURE);
	p->pipefd = init_pipefd(count - 1);
	if (p->pipefd == NULL)
		return (free(p->procid), FAILURE);
	return (SUCCESS);
}

void	close_pipes(int	**pipefd, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		close(pipefd[i][0]);
		close(pipefd[i][1]);
		i++;
	}
}

int	pipex(t_command *command, char **ev, int proc_count)
{
	t_pipe	p;
	int	i;

	if (init_pipe(&p, proc_count) == FAILURE)
		return (FAILURE);
	i = 0;
	while (i + 1 < proc_count)
	{
		if (pipe(p.pipefd[i]) == error)
		{
			perror("pipe");
			return (EXIT_FAILURE);
		}
		p.procid[i] = fork_process(&p, command, ev, i);
		command = command->next;
		i++;
	}
	p.procid[i] = fork_process(&p, command, ev, i);
	close_pipes(p.pipefd, proc_count - 1);
	return (wait_for_children(&p, proc_count));
}
