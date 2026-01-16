/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitotak <keitotak@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 17:14:01 by keitotak          #+#    #+#             */
/*   Updated: 2026/01/16 17:14:10 by keitotak         ###   ########.fr       */
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

int	pipex(t_command *command, char **ev, int count)
{
	t_pipe	p;
	int	i;

	if (init_pipe(&p, count) == FAILURE)
		return (FAILURE);
	i = 0;
	while (i < count)
	{
		if (i + 1 < count)
		{
			if (pipe(p.pipefd[i]) == error)
			{
				perror("pipe");
				return (EXIT_FAILURE);
			}
		}
		p.procid[i] = fork_process(p, command, ev, i);
		command = command->next;
		i++;
	}
	return (SUCCESS);
}
